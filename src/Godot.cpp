#include <Godot.hpp>
#include <Node.hpp>
#include <steam/steam_api.h>
#include <memory>
#include <vector>
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
        register_method("get_account_id", &SteamID::get_account_id);
        register_method("get_static_account_key", &SteamID::get_static_account_key);
        register_method("convert_to_uint64", &SteamID::convert_to_uint64);
    }

    void _init()
    {
    }

    auto const& get() const
    {
        return steam_id_;
    }

    std::int64_t get_account_id() const
    {
        return steam_id_.GetAccountID();
    }

    std::int64_t get_static_account_key() const
    {
        return steam_id_.GetStaticAccountKey();
    }

    std::int64_t convert_to_uint64() const
    {
        return steam_id_.ConvertToUint64();
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

    PoolIntArray get_details() const
    {
        PoolIntArray res;
        for(auto i : details)
        {
            res.append(i);
        }

        return res;
    }

public:
    std::vector<std::int32_t> details;

    static void _register_methods()
    {
        register_method("get_steam_id_user", &SteamLeaderboardEntry::get_steam_id_user);
        register_method("get_global_rank",   &SteamLeaderboardEntry::get_global_rank);
        register_method("get_score",         &SteamLeaderboardEntry::get_score);
        register_method("get_details",       &SteamLeaderboardEntry::get_details);
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

class SteamUser : public Reference
{
    GODOT_CLASS(SteamUser, Reference)

    ISteamUser* steam_user_{};

public:
    static void _register_methods()
    {
        register_method("get_steam_id", &SteamUser::get_steam_id);
    }

    void _init()
    {
        steam_user_ = ::SteamUser();
    }

    Ref<SteamID> get_steam_id() const
    {
        return SteamID::make(steam_user_->GetSteamID());
    }
};

class SteamUserStats : public Reference
{
    GODOT_CLASS(SteamUserStats, Reference)

    ISteamUserStats* steam_user_stats_{};

public:
    static void _register_methods()
    {
        register_method("set_stati",                        &SteamUserStats::set_stati);
        register_method("get_stati",                        &SteamUserStats::get_stati);
        register_method("set_statf",                        &SteamUserStats::set_statf);
        register_method("get_statf",                        &SteamUserStats::get_statf);
        register_method("set_achievement",                  &SteamUserStats::set_achievement);
        register_method("get_num_achievements",             &SteamUserStats::get_num_achievements);
        register_method("get_achievement_name",             &SteamUserStats::get_achievement_name);
        register_method("clear_achievement",                &SteamUserStats::clear_achievement);
        register_method("indicate_achievement_progress",    &SteamUserStats::indicate_achievement_progress);
        register_method("get_achievement",                  &SteamUserStats::get_achievement);
        register_method("request_current_stats",            &SteamUserStats::request_current_stats);
        register_method("store_stats",                      &SteamUserStats::store_stats);
        register_method("find_leaderboard",                 &SteamUserStats::find_leaderboard);
        register_method("find_or_create_leaderboard",       &SteamUserStats::find_or_create_leaderboard);
        register_method("upload_leaderboard_score",         &SteamUserStats::upload_leaderboard_score);
        register_method("download_leaderboard_entries",     &SteamUserStats::download_leaderboard_entries);
        register_method("get_downloaded_leaderboard_entry", &SteamUserStats::get_downloaded_leaderboard_entry);
    }

    void _init()
    {
        steam_user_stats_ = ::SteamUserStats();
    }

    bool set_statf(String name, float data)
    {
        if(steam_user_stats_)
        {
            return steam_user_stats_->SetStat(name.utf8().get_data(), data);
        }
        
        return false;
    }

    bool set_stati(String name, int data)
    {
        if(steam_user_stats_)
        {
            return steam_user_stats_->SetStat(name.utf8().get_data(), data);
        }
        
        return false;
    }
    
    Array get_statf(String name) const
    {
        Array res;

        if(steam_user_stats_)
        {
            float stat{};
            if(steam_user_stats_->GetStat(name.utf8().get_data(), &stat))
            {
                res.push_back(true);
                res.push_back(stat);
            }
            else
            {
                res.push_back(false);
            }
        }
        
        return res;
    }

    Array get_stati(String name) const
    {
        Array res;
    
        if(steam_user_stats_)
        {
            int stat{};
            if(steam_user_stats_->GetStat(name.utf8().get_data(), &stat))
            {
                res.push_back(true);
                res.push_back(stat);
            }
            else
            {
                res.push_back(false);
            }
        }
        
        return res;
    }

    bool indicate_achievement_progress(String name, int current_progress, int max_progress) const
    {
        if(steam_user_stats_)
        {
            return steam_user_stats_->IndicateAchievementProgress(name.utf8().get_data(), current_progress, max_progress);
        }

        return false;
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

    Ref<SteamCallback> find_or_create_leaderboard(String leaderboard_name, int sort_method, int display_type)
    {
        if(!steam_user_stats_)
        {
            return {};
        }
        
        auto call = steam_user_stats_->FindOrCreateLeaderboard(leaderboard_name.utf8().get_data(), static_cast<ELeaderboardSortMethod>(sort_method), static_cast<ELeaderboardDisplayType>(display_type));
        return SteamCallback::make<LeaderboardFindResult_t, SteamLeaderboardFindResult>(call);
    }

    Ref<SteamCallback> upload_leaderboard_score(Ref<SteamLeaderboard> leaderboard, int method, int score, PoolIntArray score_details)
    {
        if(!steam_user_stats_)
        {
            return {};
        }

        if(leaderboard.is_null())
        {
            return {};
        }

        // score_details_as_int32 is copied during UploadLeaderboardScore so doesn't need to live past fucntion scope
        std::vector<std::int32_t> score_details_as_int32;
        for(std::size_t i{}; i < score_details.size(); i++)
        {
            score_details_as_int32.push_back(static_cast<std::int32_t>(score_details[i]));
        }

        auto call = steam_user_stats_->UploadLeaderboardScore(leaderboard->get(), static_cast<ELeaderboardUploadScoreMethod>(method), score, score_details_as_int32.data(), score_details_as_int32.size());        
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

    Ref<SteamLeaderboardEntry> get_downloaded_leaderboard_entry(Ref<SteamLeaderboardEntries> leaderboard, int index, int detail_max)
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
        res->details.resize(detail_max);
        if(!steam_user_stats_->GetDownloadedLeaderboardEntry(leaderboard->get(), index, &res->get(), res->details.data(), detail_max))
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

    void activate_game_overlay(String dialog)
    {
        if(!steam_friends_)
        {
            return;
        }

        steam_friends_->ActivateGameOverlay(dialog.utf8().get_data());
    }

    void activate_game_overlay_to_web_page(String url)
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

    bool set_rich_presence(String key, String value)
    {
        if(!steam_friends_)
        {
            return false;
        }

        return steam_friends_->SetRichPresence(key.utf8().get_data(), value.utf8().get_data());
    }

    void clear_rich_presence()
    {
        if(!steam_friends_)
        {
            return;
        }

        steam_friends_->ClearRichPresence();
    }

    String get_persona_name() const
    {
        if(!steam_friends_)
        {
            return {};
        }

        return steam_friends_->GetPersonaName();
    }

public:
    static void _register_methods()
    {
        register_method("request_user_information",          &SteamFriends::request_user_information);
        register_method("get_friend_persona_name",           &SteamFriends::get_friend_persona_name);
        register_method("activate_game_overlay",             &SteamFriends::activate_game_overlay);
        register_method("activate_game_overlay_to_web_page", &SteamFriends::activate_game_overlay_to_web_page);
        register_method("activate_game_overlay_to_store",    &SteamFriends::activate_game_overlay_to_store);
        register_method("set_rich_presence",                 &SteamFriends::set_rich_presence);
        register_method("clear_rich_presence",               &SteamFriends::clear_rich_presence);
        register_method("get_persona_name",                  &SteamFriends::get_persona_name);

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

class SteamUtils : public Reference
{
    GODOT_CLASS(SteamUtils, Reference)

    ISteamUtils* steam_utils_{};

    int get_app_id() const
    {
        if(!steam_utils_)
        {
            return {};
        }

        return steam_utils_->GetAppID();
    }

public:
    static void _register_methods()
    {
        register_method("get_app_id", &SteamUtils::get_app_id);
    }

    void _init()
    {
        steam_utils_ = ::SteamUtils();
    }
};

class SteamApps : public Reference
{
    GODOT_CLASS(SteamApps, Reference)

    ISteamApps* steam_apps_{};

    String get_current_game_language() const
    {
        if(!steam_apps_)
        {
            return {};
        }

        return steam_apps_->GetCurrentGameLanguage();
    }

    String get_available_game_languages() const
    {
        if(!steam_apps_)
        {
            return {};
        }

        return steam_apps_->GetAvailableGameLanguages();
    }

public:
    static void _register_methods()
    {
        register_method("get_current_game_language", &SteamApps::get_current_game_language);
        register_method("get_available_game_languages", &SteamApps::get_available_game_languages);
    }

    void _init()
    {
        steam_apps_ = ::SteamApps();
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
    godot::register_class<godot::SteamUser>();
    godot::register_class<godot::SteamUserStats>();
    godot::register_class<godot::SteamFriends>();
    godot::register_class<godot::SteamUtils>();
    godot::register_class<godot::SteamApps>();
}
}
