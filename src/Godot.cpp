#include <Godot.hpp>
#include <Node.hpp>
#include <steam/steam_api.h>
#include <memory>
#include <set>

namespace godot 
{
class SteamAPI : public Reference
{
    GODOT_CLASS(SteamAPI, Reference)

public:
    static void _register_methods()
    {
        register_method("restart_app_if_necessary",  &SteamAPI::restart_app_if_necessary);
        register_method("init",                      &SteamAPI::init);
        register_method("run_callbacks",             &SteamAPI::run_callbacks);
    }

    void _init()
    {
    }

    bool restart_app_if_necessary(int app_id)
    {
       return SteamAPI_RestartAppIfNecessary(app_id);
    }
    

    bool init()
    {
       return SteamAPI_Init();
    }

    void run_callbacks()
    {
        SteamAPI_RunCallbacks();
    }
};

class SteamID : public Reference
{
    GODOT_CLASS(SteamID, Reference)

    CSteamID steam_id_;

public:
    static auto make(CSteamID const& steam_id)
    {
        auto res = Ref{SteamID::_new()};
        res->steam_id_ = steam_id;
        return res;
    }

    static void _register_methods()
    {
    }

    void _init()
    {
    }

    auto const& get() const
    {
        return steam_id_;
    }

};

template<typename T, typename TT>
struct SteamBase : public Reference
{
    GODOT_CLASS(SteamBase, Reference)

protected:
    T data{};

public:
    static auto make(T const* t)
    {
        auto res = Ref{TT::_new()};
        res->data = *t;
        return res;
    }

    T const& get() const
    {
        return data;
    }

    T& get()
    {
        return data;
    }
};

struct SteamLeaderboard : public SteamBase<SteamLeaderboard_t, SteamLeaderboard>
{
    GODOT_CLASS(SteamLeaderboard, SteamBase)

public:
    static void _register_methods()
    {
    }

    void _init()
    {
    }
};

struct SteamLeaderboardFindResult : public SteamBase<LeaderboardFindResult_t, SteamLeaderboardFindResult>
{
    GODOT_CLASS(SteamLeaderboardFindResult, Reference)

    bool get_leaderboard_found() const
    {
        return data.m_bLeaderboardFound;
    }

    Ref<SteamLeaderboard> get_leaderboard() const
    {
        return SteamLeaderboard::make(&data.m_hSteamLeaderboard);
    }

public:
    static void _register_methods()
    {
        register_method("get_leaderboard_found", &SteamLeaderboardFindResult::get_leaderboard_found);
        register_method("get_leaderboard",       &SteamLeaderboardFindResult::get_leaderboard);
    }

    void _init()
    {
    }
};

struct SteamLeaderboardScoreUploaded : public SteamBase<LeaderboardScoreUploaded_t, SteamLeaderboardScoreUploaded>
{
    GODOT_CLASS(SteamLeaderboardScoreUploaded, Reference)

    bool get_success() const
    {
        return data.m_bSuccess;
    }

public:
    static void _register_methods()
    {
        register_method("get_success", &SteamLeaderboardScoreUploaded::get_success);
    }

    void _init()
    {
    }
};

struct SteamLeaderboardEntry : public SteamBase<LeaderboardEntry_t, SteamLeaderboardEntry>
{
    GODOT_CLASS(SteamLeaderboardEntry, Reference)

    Ref<SteamID> get_steam_id_user() const
    {
        return SteamID::make(data.m_steamIDUser);
    }

    int get_global_rank() const
    {
        return data.m_nGlobalRank;
    }

    int get_score() const
    {
        return data.m_nScore;
    }

public:
    static void _register_methods()
    {
        register_method("get_steam_id_user", &SteamLeaderboardEntry::get_steam_id_user);
        register_method("get_global_rank",   &SteamLeaderboardEntry::get_global_rank);
        register_method("get_score",         &SteamLeaderboardEntry::get_score);
    }

    void _init()
    {
    }
};

struct SteamLeaderboardEntries : public SteamBase<SteamLeaderboardEntries_t, SteamLeaderboardEntries>
{
    GODOT_CLASS(SteamLeaderboardEntries, Reference)

public:
    static void _register_methods()
    {
    }

    void _init()
    {
    }
};

struct SteamLeaderboardScoresDownloaded : public SteamBase<LeaderboardScoresDownloaded_t, SteamLeaderboardScoresDownloaded>
{
    GODOT_CLASS(SteamLeaderboardScoresDownloaded, Reference)

    int get_entry_count() const
    {
        return data.m_cEntryCount;
    }

    auto get_entries() const
    {
        return SteamLeaderboardEntries::make(&data.m_hSteamLeaderboardEntries);
    }

public:
    static void _register_methods()
    {
        register_method("get_entry_count", &SteamLeaderboardScoresDownloaded::get_entry_count);
        register_method("get_entries",     &SteamLeaderboardScoresDownloaded::get_entries);
    }

    void _init()
    {
    }
};

struct SteamCallback : public Reference
{
    GODOT_CLASS(SteamCallback, Reference)

    std::unique_ptr<CCallbackBase> callback_;

    // we pass callbacks to steam by raw pointer so we need to ensure we keep this memory alive
    static auto& keep_alive()
    {
        static std::set<Ref<SteamCallback>> set;
        return set;
    }

    void erase_self_from_keep_alive()
    {
        keep_alive().erase(Ref<SteamCallback>{this});
    }

    void operator()(LeaderboardFindResult_t* t, bool)
    {
        emit_signal("done", SteamLeaderboardFindResult::make(t));
        erase_self_from_keep_alive();
    }

    void operator()(LeaderboardScoreUploaded_t* t, bool)
    {
        emit_signal("done", SteamLeaderboardScoreUploaded::make(t));
        erase_self_from_keep_alive();
    }

    void operator()(LeaderboardScoresDownloaded_t* t, bool)
    {
        emit_signal("done", SteamLeaderboardScoresDownloaded::make(t));
        erase_self_from_keep_alive();
    }

public:
    static void _register_methods()
    {
        register_signal<SteamCallback>(String{"done"});
    }

    template<typename T>
    static Ref<SteamCallback> make(SteamAPICall_t steam_api_call)
    {
        auto res = Ref{SteamCallback::_new()};
        res->callback_.reset(reinterpret_cast<CCallbackBase*>(new CCallResult<SteamCallback, T>));

        auto lol = reinterpret_cast<CCallResult<SteamCallback, T>*>(res->callback_.get());

        lol->Set(steam_api_call, *res, &SteamCallback::operator());

        keep_alive().insert(res);

        return res;
    }

    void _init()
    {
    }
};

class SteamUserStats : public Reference
{
    GODOT_CLASS(SteamUserStats, Reference)

    ISteamUserStats* m_steam_user_stats_{};

public:
    static void _register_methods()
    {
        register_method("set_achievement",                  &SteamUserStats::set_achievement);
        register_method("clear_achievement",                &SteamUserStats::clear_achievement);
        register_method("get_achievement",                  &SteamUserStats::get_achievement);
        register_method("request_current_stats",            &SteamUserStats::request_current_stats);
        register_method("store_stats",                      &SteamUserStats::store_stats);
        register_method("find_leaderboard",                 &SteamUserStats::find_leaderboard);
        register_method("upload_leaderboard_score",         &SteamUserStats::upload_leaderboard_score);
        register_method("download_leaderboard_entries",     &SteamUserStats::download_leaderboard_entries);
        register_method("get_downloaded_leaderboard_entry", &SteamUserStats::get_downloaded_leaderboard_entry);
    }

    void _init()
    {
        m_steam_user_stats_ = ::SteamUserStats();
    }
    
    
    bool set_achievement(String achievement_api_name)
    {
        if(m_steam_user_stats_)
        {
            return m_steam_user_stats_->SetAchievement(achievement_api_name.utf8().get_data());
        }
        
        return false;
    }

    bool clear_achievement(String achievement_api_name)
    {
        if(m_steam_user_stats_)
        {
            return m_steam_user_stats_->ClearAchievement(achievement_api_name.utf8().get_data());
        }

        return false;
    }

    bool get_achievement(String achievement_api_name)
    {
        if(m_steam_user_stats_)
        {
            bool unlocked{};
            if(m_steam_user_stats_->GetAchievement(achievement_api_name.utf8().get_data(), &unlocked))
            {
                return unlocked;
            }
        }
 
        return false;
    }

    bool request_current_stats()
    {
        return m_steam_user_stats_->RequestCurrentStats();
    }

    bool store_stats()
    {
        return m_steam_user_stats_->StoreStats();
    }

    Ref<SteamCallback> find_leaderboard(String leaderboard_name)
    {
        if(!m_steam_user_stats_)
        {
            return {};
        }
        
        auto call = m_steam_user_stats_->FindLeaderboard(leaderboard_name.utf8().get_data());
        return SteamCallback::make<LeaderboardFindResult_t>(call);
    }

    Ref<SteamCallback> upload_leaderboard_score(Ref<SteamLeaderboard> leaderboard, int method, int score)
    {
        if(!m_steam_user_stats_)
        {
            return {};
        }

        if(leaderboard.is_null())
        {
            return {};
        }

        auto call = m_steam_user_stats_->UploadLeaderboardScore(leaderboard->get(), static_cast<ELeaderboardUploadScoreMethod>(method), score, nullptr, 0);
        return SteamCallback::make<LeaderboardScoreUploaded_t>(call);
    }

    Ref<SteamCallback> download_leaderboard_entries(Ref<SteamLeaderboard> leaderboard, int data_request, int begin, int end)
    {
        if(!m_steam_user_stats_)
        {
            return {};
        }

        if(leaderboard.is_null())
        {
            return {};
        }

        auto call = m_steam_user_stats_->DownloadLeaderboardEntries(leaderboard->get(), static_cast<ELeaderboardDataRequest>(data_request), begin, end);
        return SteamCallback::make<LeaderboardScoresDownloaded_t>(call);
    }

    Ref<SteamLeaderboardEntry> get_downloaded_leaderboard_entry(Ref<SteamLeaderboardEntries> leaderboard, int index)
    {
        if(!m_steam_user_stats_)
        {
            return {};
        }

        if(leaderboard.is_null())
        {
            return {};
        }

        auto res = Ref{SteamLeaderboardEntry::_new()};
        if(!m_steam_user_stats_->GetDownloadedLeaderboardEntry(leaderboard->get(), index, &res->get(), nullptr, 0))
        {
            return {};
        }

        return res;
    }
};

class SteamFriends : public Reference
{
    GODOT_CLASS(SteamFriends, Reference)

    ISteamFriends* steam_friends_{};

    bool request_user_information(Ref<SteamID> steam_id_user, bool require_name_only)
    {
        if(!steam_friends_)
        {
            return {};
        }

        if(steam_id_user.is_null())
        {
            return {};
        }
    
        return steam_friends_->RequestUserInformation(steam_id_user->get(), require_name_only);
    }

    String get_friend_persona_name(Ref<SteamID> steam_id_user) const
    {
        if(!steam_friends_)
        {
            return {};
        }

        if(steam_id_user.is_null())
        {
            return {};
        }
    
        return steam_friends_->GetFriendPersonaName(steam_id_user->get());
    }

public:
    static void _register_methods()
    {
        register_method("request_user_information", &SteamFriends::request_user_information);
        register_method("get_friend_persona_name",  &SteamFriends::get_friend_persona_name);
    }

    void _init()
    {
        steam_friends_ = ::SteamFriends();
    }
    
};


extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) 
{
    godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) 
{
    godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) 
{
    godot::Godot::nativescript_init(handle);
    godot::register_class<godot::SteamAPI>();
    godot::register_class<godot::SteamLeaderboardFindResult>();
    godot::register_class<godot::SteamLeaderboard>();
    godot::register_class<godot::SteamLeaderboardScoreUploaded>();
    godot::register_class<godot::SteamLeaderboardScoresDownloaded>();
    godot::register_class<godot::SteamLeaderboardEntry>();
    godot::register_class<godot::SteamLeaderboardEntries>();
    godot::register_class<godot::SteamID>();
    godot::register_class<godot::SteamCallback>();
    godot::register_class<godot::SteamUserStats>();
    godot::register_class<godot::SteamFriends>();
}
}
