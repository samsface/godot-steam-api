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

    bool is_init_{};

public:
    static void _register_methods()
    {
        register_method("restart_app_if_necessary",  &SteamAPI::restart_app_if_necessary);
        register_method("init",                      &SteamAPI::init);
        register_method("is_init",                   &SteamAPI::is_init);
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
       is_init_ = SteamAPI_Init();
       return is_init();
    }

    bool is_init()
    {
       return is_init_;
    }

    void run_callbacks()
    {
        SteamAPI_RunCallbacks();
    }

    ~SteamAPI()
    {
        if(is_init_) 
        {
            SteamAPI_Shutdown();
        }
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
class SteamBase : public Reference
{
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

class SteamLeaderboard : public SteamBase<SteamLeaderboard_t, SteamLeaderboard>
{
    GODOT_CLASS(SteamLeaderboard, Reference)

public:
    static void _register_methods()
    {
    }

    void _init()
    {
    }
};

class SteamLeaderboardFindResult : public SteamBase<LeaderboardFindResult_t, SteamLeaderboardFindResult>
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

class SteamLeaderboardScoreUploaded : public SteamBase<LeaderboardScoreUploaded_t, SteamLeaderboardScoreUploaded>
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

class SteamLeaderboardEntry : public SteamBase<LeaderboardEntry_t, SteamLeaderboardEntry>
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

class SteamLeaderboardEntries : public SteamBase<SteamLeaderboardEntries_t, SteamLeaderboardEntries>
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

class SteamLeaderboardScoresDownloaded : public SteamBase<LeaderboardScoresDownloaded_t, SteamLeaderboardScoresDownloaded>
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

class SteamCallback : public Reference
{
    GODOT_CLASS(SteamCallback, Reference)

    // Valve was nice enough to not make CCallResult base class private.
    // Wrapping CCallResult so can properly call it's dtor.
    struct steam_callback_base
    {
        virtual ~steam_callback_base()
        {}
    };

    template<typename steam_type, typename emit_type>
    struct steam_callback : public steam_callback_base
    {
        CCallResult<steam_callback, steam_type> callback;
        SteamCallback* parent{};

        steam_callback(SteamCallback* parent_) : parent{parent_}
        {}

        void operator()(steam_type* t, bool)
        {
            parent->operator()(std::move(emit_type::make(t)));
        }
    };

    std::unique_ptr<steam_callback_base> callback_;

    // We pass callbacks to steam by raw pointer so we need to ensure we keep this memory alive
    // until steam calls us back.
    static auto& keep_alive()
    {
        static std::set<Ref<SteamCallback>> set;
        return set;
    }

public:
    template<typename T>
    void operator()(T t)
    {
        emit_signal("done", t);
        keep_alive().erase(Ref{this});
    }

public:
    static void _register_methods()
    {
        register_signal<SteamCallback>("done", {});
    }

    void _init()
    {
    }

    template<typename steam_type, typename emit_type>
    static auto make(SteamAPICall_t steam_api_call)
    {
        auto res = Ref{SteamCallback::_new()};
        auto ptr = new steam_callback<steam_type, emit_type>{*res};
        res->callback_.reset(ptr);
        ptr->callback.Set(steam_api_call, ptr, &steam_callback<steam_type, emit_type>::operator());

        keep_alive().insert(res);

        return res;
    }
};

class SteamUserStats : public Reference
{
    GODOT_CLASS(SteamUserStats, Reference)

    ISteamUserStats* steam_user_stats_{};

public:
    static void _register_methods()
    {
        register_method("set_achievement",                  &SteamUserStats::set_achievement);
        register_method("get_num_achievements",             &SteamUserStats::get_num_achievements);
        register_method("get_achievement_name",             &SteamUserStats::get_achievement_name);
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
        steam_user_stats_ = ::SteamUserStats();
    }
    
    
    bool set_achievement(String achievement_api_name)
    {
        if(steam_user_stats_)
        {
            return steam_user_stats_->SetAchievement(achievement_api_name.utf8().get_data());
        }
        
        return false;
    }

    int get_num_achievements()
    {
        return steam_user_stats_->GetNumAchievements();
    }

    String get_achievement_name(int idx)
    {
        return steam_user_stats_->GetAchievementName(idx);
    }

    bool clear_achievement(String achievement_api_name)
    {
        if(steam_user_stats_)
        {
            return steam_user_stats_->ClearAchievement(achievement_api_name.utf8().get_data());
        }

        return false;
    }

    bool get_achievement(String achievement_api_name)
    {
        if(steam_user_stats_)
        {
            bool unlocked{};
            if(steam_user_stats_->GetAchievement(achievement_api_name.utf8().get_data(), &unlocked))
            {
                return unlocked;
            }
        }
 
        return false;
    }



    bool request_current_stats()
    {
        return steam_user_stats_->RequestCurrentStats();
    }

    bool store_stats()
    {
        return steam_user_stats_->StoreStats();
    }

    Ref<SteamCallback> find_leaderboard(String leaderboard_name)
    {
        if(!steam_user_stats_)
        {
            return {};
        }
        
        auto call = steam_user_stats_->FindLeaderboard(leaderboard_name.utf8().get_data());
        return SteamCallback::make<LeaderboardFindResult_t, SteamLeaderboardFindResult>(call);
    }


    Ref<SteamCallback> upload_leaderboard_score(Ref<SteamLeaderboard> leaderboard, int method, int score)
    {
        if(!steam_user_stats_)
        {
            return {};
        }

        if(leaderboard.is_null())
        {
            return {};
        }

        auto call = steam_user_stats_->UploadLeaderboardScore(leaderboard->get(), static_cast<ELeaderboardUploadScoreMethod>(method), score, nullptr, 0);
        return SteamCallback::make<LeaderboardScoreUploaded_t, SteamLeaderboardScoreUploaded>(call);
    }
    
    Ref<SteamCallback> download_leaderboard_entries(Ref<SteamLeaderboard> leaderboard, int data_request, int begin, int end)
    {
        if(!steam_user_stats_)
        {
            return {};
        }

        if(leaderboard.is_null())
        {
            return {};
        }

        auto call = steam_user_stats_->DownloadLeaderboardEntries(leaderboard->get(), static_cast<ELeaderboardDataRequest>(data_request), begin, end);
        return SteamCallback::make<LeaderboardScoresDownloaded_t, SteamLeaderboardScoresDownloaded>(call);
    }

    Ref<SteamLeaderboardEntry> get_downloaded_leaderboard_entry(Ref<SteamLeaderboardEntries> leaderboard, int index)
    {
        if(!steam_user_stats_)
        {
            return {};
        }

        if(leaderboard.is_null())
        {
            return {};
        }

        auto res = Ref{SteamLeaderboardEntry::_new()};
        if(!steam_user_stats_->GetDownloadedLeaderboardEntry(leaderboard->get(), index, &res->get(), nullptr, 0))
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

    STEAM_CALLBACK(SteamFriends, OnGameOverlayActivated, GameOverlayActivated_t);

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

    void active_game_overlay_to_web_page(String url)
    {
        if(!steam_friends_)
        {
            return;
        }

        steam_friends_->ActivateGameOverlayToWebPage(url.utf8().get_data());
    }

    void activate_game_overlay_to_store(int app_id, int where)
    {
        if(!steam_friends_)
        {
            return;
        }

        steam_friends_->ActivateGameOverlayToStore(app_id, static_cast<EOverlayToStoreFlag>(where));
    }

public:
    static void _register_methods()
    {
        register_method("request_user_information",        &SteamFriends::request_user_information);
        register_method("get_friend_persona_name",         &SteamFriends::get_friend_persona_name);
        register_method("active_game_overlay_to_web_page", &SteamFriends::active_game_overlay_to_web_page);
        register_method("activate_game_overlay_to_store",  &SteamFriends::activate_game_overlay_to_store);

        register_signal<SteamFriends>("game_overlay_activated", "active", GODOT_VARIANT_TYPE_BOOL);
    }

    void _init()
    {
        steam_friends_ = ::SteamFriends();
    }
    
};

inline void SteamFriends::OnGameOverlayActivated(GameOverlayActivated_t* callback)
{
	if (!callback)
    {
        return;
    }

    emit_signal("game_overlay_activated", static_cast<bool>(callback->m_bActive));
}

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
