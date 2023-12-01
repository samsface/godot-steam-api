namespace godot 
{
class SteamAPI_box : public Reference
{
    GODOT_CLASS(SteamAPI_box, Reference)

    bool is_init_{};

public:
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


    auto SteamUtils()
    {
        return ISteamUtils_box::make(::SteamUtils());
    }


    auto SteamUserStats()
    {
        return ISteamUserStats_box::make(::SteamUserStats());
    }

    ~SteamAPI_box()
    {
        if(is_init_) 
        {
            SteamAPI_Shutdown();
        }
    }

    static void _register_methods()
    {
        register_method("restart_app_if_necessary",  &SteamAPI_box::restart_app_if_necessary);
        register_method("init",                      &SteamAPI_box::init);
        register_method("is_init",                   &SteamAPI_box::is_init);
        register_method("run_callbacks",             &SteamAPI_box::run_callbacks);
        register_method("SteamUtils",                &SteamAPI_box::SteamUtils);
        register_method("SteamUserStats",            &SteamAPI_box::SteamUserStats);
    }

};
}
