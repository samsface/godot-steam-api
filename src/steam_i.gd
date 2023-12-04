extends Node
class_name SteamI

class Callback:
    signal done

class Proxy_:
    signal keep_alive_hack_
    
    var object_to_proxy_

    func _init(object_to_proxy) -> void:
        object_to_proxy_ = object_to_proxy

    func call_(func_name, args := []):
        if not object_to_proxy_:
            return
        
        return object_to_proxy_.callv(func_name, args)
        
    func callback_(func_name, args := []):
        if not object_to_proxy_:
            var result = Callback.new()
            result.call_deferred("emit_signal", "done", null)
            call_deferred("emit_signal", "keep_alive_hack_", result)
            return result

        return object_to_proxy_.callv(func_name, args)

enum EFloatingGamepadTextInputMode {
    mode_single_line = 0,
    mode_multiple_lines = 1,
    mode_email = 2,
    mode_numeric = 3,
}

enum ELeaderboardUploadScoreMethod {
    none = 0,
    keep_best = 1,
    force_update = 2,
}

enum EGamepadTextInputMode {
    normal = 0,
    password = 1,
}

enum EUniverse {
    invalid = 0,
    public = 1,
    beta = 2,
    internal = 3,
    dev = 4,
    max_ = 5,
}

enum ELeaderboardSortMethod {
    none = 0,
    ascending = 1,
    descending = 2,
}

enum EAccountType {
    invalid = 0,
    individual = 1,
    multiseat = 2,
    game_server = 3,
    anon_game_server = 4,
    pending = 5,
    content_server = 6,
    clan = 7,
    chat = 8,
    console_user = 9,
    anon_user = 10,
    max_ = 11,
}

enum ESteamIPv6ConnectivityState {
    unknown = 0,
    good = 1,
    bad = 2,
}

enum EGamepadTextInputLineMode {
    single_line = 0,
    multiple_lines = 1,
}

enum ESteamAPICallFailure {
    none = -1,
    steam_gone = 0,
    network_failure = 1,
    invalid_handle = 2,
    mismatched_callback = 3,
}

enum ELeaderboardDisplayType {
    none = 0,
    numeric = 1,
    time_seconds = 2,
    time_milli_seconds = 3,
}

enum ESteamIPv6ConnectivityProtocol {
    invalid = 0,
    http = 1,
    udp = 2,
}

enum ETextFilteringContext {
    unknown = 0,
    game_content = 1,
    chat = 2,
    name = 3,
}

enum ELeaderboardDataRequest {
    global = 0,
    global_around_user = 1,
    friends = 2,
    users = 3,
}

enum ENotificationPosition {
    position_top_left = 0,
    position_top_right = 1,
    position_bottom_left = 2,
    position_bottom_right = 3,
}

class SteamAPI extends Proxy_:
    func _init(o).(o) -> void:
        pass

class FloatPointer extends Proxy_:
    func _init(o).(o) -> void:
        pass

class Bool extends Proxy_:
    func _init(o).(o) -> void:
        pass

class ISteamUtils extends Proxy_:
    func _init(o).(o) -> void:
        pass

    func get_seconds_since_app_active() -> int:
        return call_("GetSecondsSinceAppActive", [])

    func get_seconds_since_computer_active() -> int:
        return call_("GetSecondsSinceComputerActive", [])

    func get_connected_universe() -> int:
        return call_("GetConnectedUniverse", [])

    func get_server_real_time() -> int:
        return call_("GetServerRealTime", [])

    func get_ip_country() -> String:
        return call_("GetIPCountry", [])

    class GetImageSizeResult:
        error:bool
        width:int
        height:int

    func get_image_size(image:int) -> GetImageSizeResult:
        return call_("GetImageSize", [image, GetImageSizeResult.new()])

    class GetImageRGBAResult:
        error:bool
        dest:PoolIntArray

    func get_image_rgba(image:int) -> GetImageRGBAResult:
        return call_("GetImageRGBA", [image, GetImageRGBAResult.new()])

    func get_current_battery_power() -> int:
        return call_("GetCurrentBatteryPower", [])

    func get_app_id() -> int:
        return call_("GetAppID", [])

    func set_overlay_notification_position(notification_position:int) -> void:
        call_("SetOverlayNotificationPosition", [notification_position])

    class IsAPICallCompletedResult:
        error:bool
        failed:bool

    func is_api_call_completed(steam_api_call:int) -> IsAPICallCompletedResult:
        return call_("IsAPICallCompleted", [steam_api_call, IsAPICallCompletedResult.new()])

    func get_api_call_failure_reason(steam_api_call:int) -> int:
        return call_("GetAPICallFailureReason", [steam_api_call])

    func get_ipc_call_count() -> int:
        return call_("GetIPCCallCount", [])

    func is_overlay_enabled() -> bool:
        return call_("IsOverlayEnabled", [])

    func overlay_needs_present() -> bool:
        return call_("BOverlayNeedsPresent", [])

    func check_file_signature(file_name:String) -> SteamAPICallT:
        return call_("CheckFileSignature", [file_name])

    func show_gamepad_text_input(input_mode:int, line_input_mode:int, description:String, char_max:int, existing_text:String) -> bool:
        return call_("ShowGamepadTextInput", [input_mode, line_input_mode, description, char_max, existing_text])

    func get_entered_gamepad_text_length() -> int:
        return call_("GetEnteredGamepadTextLength", [])

    class GetEnteredGamepadTextInputResult:
        error:bool
        text:String

    func get_entered_gamepad_text_input(text:int) -> GetEnteredGamepadTextInputResult:
        return call_("GetEnteredGamepadTextInput", [text, GetEnteredGamepadTextInputResult.new()])

    func get_steam_ui_language() -> String:
        return call_("GetSteamUILanguage", [])

    func is_steam_running_in_vr() -> bool:
        return call_("IsSteamRunningInVR", [])

    func set_overlay_notification_inset(horizontal_inset:int, vertical_inset:int) -> void:
        call_("SetOverlayNotificationInset", [horizontal_inset, vertical_inset])

    func is_steam_in_big_picture_mode() -> bool:
        return call_("IsSteamInBigPictureMode", [])

    func start_vr_dashboard() -> void:
        call_("StartVRDashboard", [])

    func is_vr_headset_streaming_enabled() -> bool:
        return call_("IsVRHeadsetStreamingEnabled", [])

    func set_vr_headset_streaming_enabled(enabled:bool) -> void:
        call_("SetVRHeadsetStreamingEnabled", [enabled])

    func is_steam_china_launcher() -> bool:
        return call_("IsSteamChinaLauncher", [])

    func init_filter_text(filter_options:int) -> bool:
        return call_("InitFilterText", [filter_options])

    class FilterTextResult:
        error:int
        filtered_text:String

    func filter_text(context:int, source_steam_id:CSteamID, input_message:String, byte_size_out_filtered_text:int) -> FilterTextResult:
        return call_("FilterText", [context, source_steam_id, input_message, byte_size_out_filtered_text, FilterTextResult.new()])

    func get_i_pv6_connectivity_state(protocol:int) -> int:
        return call_("GetIPv6ConnectivityState", [protocol])

    func is_steam_running_on_steam_deck() -> bool:
        return call_("IsSteamRunningOnSteamDeck", [])

    func show_floating_gamepad_text_input(keyboard_mode:int, text_field_x_position:int, text_field_y_position:int, text_field_width:int, text_field_height:int) -> bool:
        return call_("ShowFloatingGamepadTextInput", [keyboard_mode, text_field_x_position, text_field_y_position, text_field_width, text_field_height])

    func set_game_launcher_mode(launcher_mode:bool) -> void:
        call_("SetGameLauncherMode", [launcher_mode])

class UnsignedCharPointer extends Proxy_:
    func _init(o).(o) -> void:
        pass

class IntConstPointer extends Proxy_:
    func _init(o).(o) -> void:
        pass

class UnsignedLonglong extends Proxy_:
    func _init(o).(o) -> void:
        pass

class LeaderboardEntryTPointer extends Proxy_:
    func _init(o).(o) -> void:
        pass

class ISteamUserStats extends Proxy_:
    func _init(o).(o) -> void:
        pass

    func request_current_stats() -> bool:
        return call_("RequestCurrentStats", [])

    class GetStatiResult:
        error:bool
        data:int

    func get_stati(name:String) -> GetStatiResult:
        return call_("GetStati", [name, GetStatiResult.new()])

    class GetStatfResult:
        error:bool
        data:float

    func get_statf(name:String) -> GetStatfResult:
        return call_("GetStatf", [name, GetStatfResult.new()])

    func set_stati(name:String, data:int) -> bool:
        return call_("SetStati", [name, data])

    func set_statf(name:String, data:float) -> bool:
        return call_("SetStatf", [name, data])

    func update_avg_rate_stat(name:String, count_this_session:float, session_length:float) -> bool:
        return call_("UpdateAvgRateStat", [name, count_this_session, session_length])

    class GetAchievementResult:
        error:bool
        achieved:bool

    func get_achievement(name:String) -> GetAchievementResult:
        return call_("GetAchievement", [name, GetAchievementResult.new()])

    func set_achievement(name:String) -> bool:
        return call_("SetAchievement", [name])

    func clear_achievement(name:String) -> bool:
        return call_("ClearAchievement", [name])

    class GetAchievementAndUnlockTimeResult:
        error:bool
        achieved:bool
        unlock_time:int

    func get_achievement_and_unlock_time(name:String) -> GetAchievementAndUnlockTimeResult:
        return call_("GetAchievementAndUnlockTime", [name, GetAchievementAndUnlockTimeResult.new()])

    func store_stats() -> bool:
        return call_("StoreStats", [])

    func get_achievement_icon(name:String) -> int:
        return call_("GetAchievementIcon", [name])

    func get_achievement_display_attribute(name:String, key:String) -> String:
        return call_("GetAchievementDisplayAttribute", [name, key])

    func indicate_achievement_progress(name:String, cur_progress:int, max_progress:int) -> bool:
        return call_("IndicateAchievementProgress", [name, cur_progress, max_progress])

    func get_num_achievements() -> int:
        return call_("GetNumAchievements", [])

    func get_achievement_name(achievement:int) -> String:
        return call_("GetAchievementName", [achievement])

    func request_user_stats(steam_id_user:CSteamID) -> SteamAPICallT:
        return call_("RequestUserStats", [steam_id_user])

    class GetUserStatiResult:
        error:bool
        data:int

    func get_user_stati(steam_id_user:CSteamID, name:String) -> GetUserStatiResult:
        return call_("GetUserStati", [steam_id_user, name, GetUserStatiResult.new()])

    class GetUserStatfResult:
        error:bool
        data:float

    func get_user_statf(steam_id_user:CSteamID, name:String) -> GetUserStatfResult:
        return call_("GetUserStatf", [steam_id_user, name, GetUserStatfResult.new()])

    class GetUserAchievementResult:
        error:bool
        achieved:bool

    func get_user_achievement(steam_id_user:CSteamID, name:String) -> GetUserAchievementResult:
        return call_("GetUserAchievement", [steam_id_user, name, GetUserAchievementResult.new()])

    class GetUserAchievementAndUnlockTimeResult:
        error:bool
        achieved:bool
        unlock_time:int

    func get_user_achievement_and_unlock_time(steam_id_user:CSteamID, name:String) -> GetUserAchievementAndUnlockTimeResult:
        return call_("GetUserAchievementAndUnlockTime", [steam_id_user, name, GetUserAchievementAndUnlockTimeResult.new()])

    func reset_all_stats(achievements_too:bool) -> bool:
        return call_("ResetAllStats", [achievements_too])

    func find_or_create_leaderboard(leaderboard_name:String, leaderboard_sort_method:int, leaderboard_display_type:int) -> SteamAPICallT:
        return call_("FindOrCreateLeaderboard", [leaderboard_name, leaderboard_sort_method, leaderboard_display_type])

    func find_leaderboard(leaderboard_name:String) -> SteamAPICallT:
        return call_("FindLeaderboard", [leaderboard_name])

    func get_leaderboard_name(steam_leaderboard:int) -> String:
        return call_("GetLeaderboardName", [steam_leaderboard])

    func get_leaderboard_entry_count(steam_leaderboard:int) -> int:
        return call_("GetLeaderboardEntryCount", [steam_leaderboard])

    func get_leaderboard_sort_method(steam_leaderboard:int) -> int:
        return call_("GetLeaderboardSortMethod", [steam_leaderboard])

    func get_leaderboard_display_type(steam_leaderboard:int) -> int:
        return call_("GetLeaderboardDisplayType", [steam_leaderboard])

    func download_leaderboard_entries(steam_leaderboard:int, leaderboard_data_request:int, range_start:int, range_end:int) -> SteamAPICallT:
        return call_("DownloadLeaderboardEntries", [steam_leaderboard, leaderboard_data_request, range_start, range_end])

    class DownloadLeaderboardEntriesForUsersResult:
        error:SteamAPICallT
        users:CSteamIDPointer

    func download_leaderboard_entries_for_users(steam_leaderboard:int, users:int) -> DownloadLeaderboardEntriesForUsersResult:
        return call_("DownloadLeaderboardEntriesForUsers", [steam_leaderboard, users, DownloadLeaderboardEntriesForUsersResult.new()])

    class GetDownloadedLeaderboardEntryResult:
        error:bool
        leaderboard_entry:LeaderboardEntryTPointer
        details:PoolIntArray

    func get_downloaded_leaderboard_entry(steam_leaderboard_entries:int, index:int) -> GetDownloadedLeaderboardEntryResult:
        return call_("GetDownloadedLeaderboardEntry", [steam_leaderboard_entries, index, GetDownloadedLeaderboardEntryResult.new()])

    func upload_leaderboard_score(steam_leaderboard:int, leaderboard_upload_score_method:int, score:int, score_details:PoolIntArray) -> SteamAPICallT:
        return call_("UploadLeaderboardScore", [steam_leaderboard, leaderboard_upload_score_method, score, score_details])

    func attach_leaderboard_ugc(steam_leaderboard:int, ugc:int) -> SteamAPICallT:
        return call_("AttachLeaderboardUGC", [steam_leaderboard, ugc])

    func get_number_of_current_players() -> SteamAPICallT:
        return call_("GetNumberOfCurrentPlayers", [])

    func request_global_achievement_percentages() -> SteamAPICallT:
        return call_("RequestGlobalAchievementPercentages", [])

    class GetMostAchievedAchievementInfoResult:
        error:int
        name:String
        percent:float
        achieved:bool

    func get_most_achieved_achievement_info() -> GetMostAchievedAchievementInfoResult:
        return call_("GetMostAchievedAchievementInfo", [GetMostAchievedAchievementInfoResult.new()])

    class GetNextMostAchievedAchievementInfoResult:
        error:int
        name:String
        percent:float
        achieved:bool

    func get_next_most_achieved_achievement_info(iterator_previous:int) -> GetNextMostAchievedAchievementInfoResult:
        return call_("GetNextMostAchievedAchievementInfo", [iterator_previous, GetNextMostAchievedAchievementInfoResult.new()])

    class GetAchievementAchievedPercentResult:
        error:bool
        percent:float

    func get_achievement_achieved_percent(name:String) -> GetAchievementAchievedPercentResult:
        return call_("GetAchievementAchievedPercent", [name, GetAchievementAchievedPercentResult.new()])

    func request_global_stats(history_days:int) -> SteamAPICallT:
        return call_("RequestGlobalStats", [history_days])

    class GetGlobalStatlResult:
        error:bool
        data:int

    func get_global_statl(stat_name:String) -> GetGlobalStatlResult:
        return call_("GetGlobalStatl", [stat_name, GetGlobalStatlResult.new()])

    class GetGlobalStatdResult:
        error:bool
        data:float

    func get_global_statd(stat_name:String) -> GetGlobalStatdResult:
        return call_("GetGlobalStatd", [stat_name, GetGlobalStatdResult.new()])

class DoublePointer extends Proxy_:
    func _init(o).(o) -> void:
        pass

class BoolPointer extends Proxy_:
    func _init(o).(o) -> void:
        pass

class LonglongPointer extends Proxy_:
    func _init(o).(o) -> void:
        pass

class Double extends Proxy_:
    func _init(o).(o) -> void:
        pass

class CharConstPointer extends Proxy_:
    func _init(o).(o) -> void:
        pass

class Uint32 extends Proxy_:
    func _init(o).(o) -> void:
        pass

class CSteamIDPointer extends Proxy_:
    func _init(o).(o) -> void:
        pass

class Float extends Proxy_:
    func _init(o).(o) -> void:
        pass

class IntPointer extends Proxy_:
    func _init(o).(o) -> void:
        pass

class CharPointer extends Proxy_:
    func _init(o).(o) -> void:
        pass

class CSteamID extends Proxy_:
    func _init(o).(o) -> void:
        pass

    func set_(account_id:int, universe:int, account_type:int) -> void:
        call_("Set", [account_id, universe, account_type])

    func instanced_set(account_id:int, instance:int, universe:int, account_type:int) -> void:
        call_("InstancedSet", [account_id, instance, universe, account_type])

    func full_set(identifier:int, universe:int, account_type:int) -> void:
        call_("FullSet", [identifier, universe, account_type])

    func set_from_uint64(steam_id:int) -> void:
        call_("SetFromUint64", [steam_id])

    func clear() -> void:
        call_("Clear", [])

    func convert_to_uint64() -> int:
        return call_("ConvertToUint64", [])

    func get_static_account_key() -> int:
        return call_("GetStaticAccountKey", [])

    func create_blank_anon_logon(universe:int) -> void:
        call_("CreateBlankAnonLogon", [universe])

    func create_blank_anon_user_logon(universe:int) -> void:
        call_("CreateBlankAnonUserLogon", [universe])

    func blank_anon_account() -> bool:
        return call_("BBlankAnonAccount", [])

    func game_server_account() -> bool:
        return call_("BGameServerAccount", [])

    func persistent_game_server_account() -> bool:
        return call_("BPersistentGameServerAccount", [])

    func anon_game_server_account() -> bool:
        return call_("BAnonGameServerAccount", [])

    func content_server_account() -> bool:
        return call_("BContentServerAccount", [])

    func clan_account() -> bool:
        return call_("BClanAccount", [])

    func chat_account() -> bool:
        return call_("BChatAccount", [])

    func is_lobby() -> bool:
        return call_("IsLobby", [])

    func individual_account() -> bool:
        return call_("BIndividualAccount", [])

    func anon_account() -> bool:
        return call_("BAnonAccount", [])

    func anon_user_account() -> bool:
        return call_("BAnonUserAccount", [])

    func console_user_account() -> bool:
        return call_("BConsoleUserAccount", [])

    func set_account_id(account_id:int) -> void:
        call_("SetAccountID", [account_id])

    func set_account_instance(instance:int) -> void:
        call_("SetAccountInstance", [instance])

    func get_account_id() -> int:
        return call_("GetAccountID", [])

    func get_un_account_instance() -> int:
        return call_("GetUnAccountInstance", [])

    func get_e_account_type() -> int:
        return call_("GetEAccountType", [])

    func get_e_universe() -> int:
        return call_("GetEUniverse", [])

    func set_e_universe(universe:int) -> void:
        call_("SetEUniverse", [universe])

    func is_valid() -> bool:
        return call_("IsValid", [])

class UnsignedInt extends Proxy_:
    func _init(o).(o) -> void:
        pass

class UnsignedIntPointer extends Proxy_:
    func _init(o).(o) -> void:
        pass

class Void extends Proxy_:
    func _init(o).(o) -> void:
        pass

class Int extends Proxy_:
    func _init(o).(o) -> void:
        pass

class Uint64 extends Proxy_:
    func _init(o).(o) -> void:
        pass

class SteamAPICallT extends Proxy_:
    func _init(o).(o) -> void:
        pass

class AccountIDT extends Proxy_:
    func _init(o).(o) -> void:
        pass

class Uint8 extends Proxy_:
    func _init(o).(o) -> void:
        pass

