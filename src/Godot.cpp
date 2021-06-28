#include <Godot.hpp>
#include <Node.hpp>
#include <steam/steam_api.h>

namespace godot 
{
class SteamAPI : public Reference
{
    GODOT_CLASS(SteamAPI, Reference)

public:
    static void _register_methods()
    {
        register_method("init",          &SteamAPI::init);
        register_method("run_callbacks", &SteamAPI::run_callbacks);
    }

    void _init()
    {
    }

    bool init(int app_id)
    {

        //if(SteamAPI_RestartAppIfNecessary(1435470))
        //{
        //    return false;
        //}

        if (!SteamAPI_Init())
        {
            return false;
        }

        return true;
    }

    void run_callbacks()
    {
        SteamGameServer_RunCallbacks();
    }
};

class SteamUserStats : public Reference
{
    GODOT_CLASS(SteamUserStats, Reference)

    ISteamUserStats* m_steam_user_stats_{};

public:
    static void _register_methods()
    {
        register_method("set_achievement",       &SteamUserStats::set_achievement);
        register_method("clear_achievement",     &SteamUserStats::clear_achievement);
        register_method("get_achievement",       &SteamUserStats::get_achievement);
        register_method("request_current_stats", &SteamUserStats::request_current_stats);
        register_method("store_stats",           &SteamUserStats::store_stats);
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
    godot::register_class<godot::SteamUserStats>();
}
}
