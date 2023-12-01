#include "pre.cpp"
namespace godot {
/* ignore handwritten: SteamAPI */
class EUniverse_box;
class AccountID_t_box;
class bool_box;
class EAccountType_box;
class ENotificationPosition_box;
class int_const_pointer_box;
class ESteamAPICallFailure_box;
class bool_pointer_box;
class ELeaderboardDataRequest_box;
class ESteamIPv6ConnectivityState_box;
class CSteamID_pointer_box;
class uint64_box;
class ELeaderboardDisplayType_box;
class unsigned_longlong_box;
class unsigned_char_pointer_box;
class LeaderboardEntry_t_pointer_box;
class int_pointer_box;
class ELeaderboardSortMethod_box;
class char_const_pointer_box;
class ISteamUtils_box;
class float_box;
class uint8_box;
class float_pointer_box;
class ESteamIPv6ConnectivityProtocol_box;
class longlong_pointer_box;
class uint32_box;
class char_pointer_box;
class ETextFilteringContext_box;
class double_box;
class EFloatingGamepadTextInputMode_box;
class EGamepadTextInputLineMode_box;
class EGamepadTextInputMode_box;
class double_pointer_box;
class unsigned_int_pointer_box;
class CSteamID_box;
class unsigned_int_box;
class int_box;
class ISteamUserStats_box;
class ELeaderboardUploadScoreMethod_box;
/* ignore handwritten: SteamAPICall_t */

class EUniverse_box : public SteamBase<EUniverse, EUniverse_box> {
  GODOT_CLASS(EUniverse_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class AccountID_t_box : public SteamBase<AccountID_t, AccountID_t_box> {
  GODOT_CLASS(AccountID_t_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class bool_box : public SteamBase<bool, bool_box> {
  GODOT_CLASS(bool_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class EAccountType_box : public SteamBase<EAccountType, EAccountType_box> {
  GODOT_CLASS(EAccountType_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class ENotificationPosition_box
    : public SteamBase<ENotificationPosition, ENotificationPosition_box> {
  GODOT_CLASS(ENotificationPosition_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class int_const_pointer_box
    : public SteamBase<const int *, int_const_pointer_box> {
  GODOT_CLASS(int_const_pointer_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class ESteamAPICallFailure_box
    : public SteamBase<ESteamAPICallFailure, ESteamAPICallFailure_box> {
  GODOT_CLASS(ESteamAPICallFailure_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class bool_pointer_box : public SteamBase<bool *, bool_pointer_box> {
  GODOT_CLASS(bool_pointer_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class ELeaderboardDataRequest_box
    : public SteamBase<ELeaderboardDataRequest, ELeaderboardDataRequest_box> {
  GODOT_CLASS(ELeaderboardDataRequest_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class ESteamIPv6ConnectivityState_box
    : public SteamBase<ESteamIPv6ConnectivityState,
                       ESteamIPv6ConnectivityState_box> {
  GODOT_CLASS(ESteamIPv6ConnectivityState_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class CSteamID_pointer_box
    : public SteamBase<CSteamID *, CSteamID_pointer_box> {
  GODOT_CLASS(CSteamID_pointer_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class uint64_box : public SteamBase<uint64, uint64_box> {
  GODOT_CLASS(uint64_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class ELeaderboardDisplayType_box
    : public SteamBase<ELeaderboardDisplayType, ELeaderboardDisplayType_box> {
  GODOT_CLASS(ELeaderboardDisplayType_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class unsigned_longlong_box
    : public SteamBase<unsigned long long, unsigned_longlong_box> {
  GODOT_CLASS(unsigned_longlong_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class unsigned_char_pointer_box
    : public SteamBase<unsigned char *, unsigned_char_pointer_box> {
  GODOT_CLASS(unsigned_char_pointer_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class LeaderboardEntry_t_pointer_box
    : public SteamBase<LeaderboardEntry_t *, LeaderboardEntry_t_pointer_box> {
  GODOT_CLASS(LeaderboardEntry_t_pointer_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class int_pointer_box : public SteamBase<int *, int_pointer_box> {
  GODOT_CLASS(int_pointer_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class ELeaderboardSortMethod_box
    : public SteamBase<ELeaderboardSortMethod, ELeaderboardSortMethod_box> {
  GODOT_CLASS(ELeaderboardSortMethod_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class char_const_pointer_box
    : public SteamBase<const char *, char_const_pointer_box> {
  GODOT_CLASS(char_const_pointer_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class ISteamUtils_box : public SteamBase<ISteamUtils, ISteamUtils_box> {
  GODOT_CLASS(ISteamUtils_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
  auto /*uint32*/ GetSecondsSinceAppActive();
  auto /*uint32*/ GetSecondsSinceComputerActive();
  auto /*EUniverse*/ GetConnectedUniverse();
  auto /*uint32*/ GetServerRealTime();
  auto /*const char **/ GetIPCountry();
  auto /*bool*/ GetImageSize(int /* int Type.INTEGER */ iImage);
  auto /*bool*/ GetImageRGBA(int /* int Type.INTEGER */ iImage,
                             int /* int Type.INTEGER */ nDestBufferSize);
  auto /*uint8*/ GetCurrentBatteryPower();
  auto /*uint32*/ GetAppID();
  auto /*void*/ SetOverlayNotificationPosition(
      int /* ENotificationPosition Type.ENUM */ eNotificationPosition);
  auto /*bool*/
  IsAPICallCompleted(int /* unsigned long long Type.INTEGER */ hSteamAPICall);
  auto /*ESteamAPICallFailure*/ GetAPICallFailureReason(
      int /* unsigned long long Type.INTEGER */ hSteamAPICall);
  auto /*uint32*/ GetIPCCallCount();
  auto /*bool*/ IsOverlayEnabled();
  auto /*bool*/ BOverlayNeedsPresent();
  auto /*SteamAPICall_t*/
  CheckFileSignature(String /* const char * */ szFileName);
  auto /*bool*/ ShowGamepadTextInput(
      int /* EGamepadTextInputMode Type.ENUM */ eInputMode,
      int /* EGamepadTextInputLineMode Type.ENUM */ eLineInputMode,
      String /* const char * */ pchDescription,
      int /* unsigned int Type.INTEGER */ unCharMax,
      String /* const char * */ pchExistingText);
  auto /*uint32*/ GetEnteredGamepadTextLength();
  auto /*bool*/
  GetEnteredGamepadTextInput(int /* unsigned int Type.INTEGER */ cchText);
  auto /*const char **/ GetSteamUILanguage();
  auto /*bool*/ IsSteamRunningInVR();
  auto /*void*/
  SetOverlayNotificationInset(int /* int Type.INTEGER */ nHorizontalInset,
                              int /* int Type.INTEGER */ nVerticalInset);
  auto /*bool*/ IsSteamInBigPictureMode();
  auto /*void*/ StartVRDashboard();
  auto /*bool*/ IsVRHeadsetStreamingEnabled();
  auto /*void*/
  SetVRHeadsetStreamingEnabled(bool /* bool Type.BOOL */ bEnabled);
  auto /*bool*/ IsSteamChinaLauncher();
  auto /*bool*/
  InitFilterText(int /* unsigned int Type.INTEGER */ unFilterOptions);
  auto /*int*/
  FilterText(int /* ETextFilteringContext Type.ENUM */ eContext,
             Ref<CSteamID_box> /* CSteamID Type.OBJECT */ sourceSteamID,
             String /* const char * */ pchInputMessage,
             int /* unsigned int Type.INTEGER */ nByteSizeOutFilteredText);
  auto /*ESteamIPv6ConnectivityState*/ GetIPv6ConnectivityState(
      int /* ESteamIPv6ConnectivityProtocol Type.ENUM */ eProtocol);
  auto /*bool*/ IsSteamRunningOnSteamDeck();
  auto /*bool*/ ShowFloatingGamepadTextInput(
      int /* EFloatingGamepadTextInputMode Type.ENUM */ eKeyboardMode,
      int /* int Type.INTEGER */ nTextFieldXPosition,
      int /* int Type.INTEGER */ nTextFieldYPosition,
      int /* int Type.INTEGER */ nTextFieldWidth,
      int /* int Type.INTEGER */ nTextFieldHeight);
  auto /*void*/ SetGameLauncherMode(bool /* bool Type.BOOL */ bLauncherMode);
};

class float_box : public SteamBase<float, float_box> {
  GODOT_CLASS(float_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class uint8_box : public SteamBase<uint8, uint8_box> {
  GODOT_CLASS(uint8_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class float_pointer_box : public SteamBase<float *, float_pointer_box> {
  GODOT_CLASS(float_pointer_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class ESteamIPv6ConnectivityProtocol_box
    : public SteamBase<ESteamIPv6ConnectivityProtocol,
                       ESteamIPv6ConnectivityProtocol_box> {
  GODOT_CLASS(ESteamIPv6ConnectivityProtocol_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class longlong_pointer_box
    : public SteamBase<long long *, longlong_pointer_box> {
  GODOT_CLASS(longlong_pointer_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class uint32_box : public SteamBase<uint32, uint32_box> {
  GODOT_CLASS(uint32_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class char_pointer_box : public SteamBase<char *, char_pointer_box> {
  GODOT_CLASS(char_pointer_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class ETextFilteringContext_box
    : public SteamBase<ETextFilteringContext, ETextFilteringContext_box> {
  GODOT_CLASS(ETextFilteringContext_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class double_box : public SteamBase<double, double_box> {
  GODOT_CLASS(double_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class EFloatingGamepadTextInputMode_box
    : public SteamBase<EFloatingGamepadTextInputMode,
                       EFloatingGamepadTextInputMode_box> {
  GODOT_CLASS(EFloatingGamepadTextInputMode_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class EGamepadTextInputLineMode_box
    : public SteamBase<EGamepadTextInputLineMode,
                       EGamepadTextInputLineMode_box> {
  GODOT_CLASS(EGamepadTextInputLineMode_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class EGamepadTextInputMode_box
    : public SteamBase<EGamepadTextInputMode, EGamepadTextInputMode_box> {
  GODOT_CLASS(EGamepadTextInputMode_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class double_pointer_box : public SteamBase<double *, double_pointer_box> {
  GODOT_CLASS(double_pointer_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class unsigned_int_pointer_box
    : public SteamBase<unsigned int *, unsigned_int_pointer_box> {
  GODOT_CLASS(unsigned_int_pointer_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class CSteamID_box : public SteamBase<CSteamID, CSteamID_box> {
  GODOT_CLASS(CSteamID_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
  auto /*void*/ Set(int /* unsigned int Type.INTEGER */ unAccountID,
                    int /* EUniverse Type.ENUM */ eUniverse,
                    int /* EAccountType Type.ENUM */ eAccountType);
  auto /*void*/ InstancedSet(int /* unsigned int Type.INTEGER */ unAccountID,
                             int /* unsigned int Type.INTEGER */ unInstance,
                             int /* EUniverse Type.ENUM */ eUniverse,
                             int /* EAccountType Type.ENUM */ eAccountType);
  auto /*void*/ FullSet(int /* unsigned long long Type.INTEGER */ ulIdentifier,
                        int /* EUniverse Type.ENUM */ eUniverse,
                        int /* EAccountType Type.ENUM */ eAccountType);
  auto /*void*/
  SetFromUint64(int /* unsigned long long Type.INTEGER */ ulSteamID);
  auto /*void*/ Clear();
  auto /*uint64*/ ConvertToUint64();
  auto /*uint64*/ GetStaticAccountKey();
  auto /*void*/ CreateBlankAnonLogon(int /* EUniverse Type.ENUM */ eUniverse);
  auto /*void*/
  CreateBlankAnonUserLogon(int /* EUniverse Type.ENUM */ eUniverse);
  auto /*bool*/ BBlankAnonAccount();
  auto /*bool*/ BGameServerAccount();
  auto /*bool*/ BPersistentGameServerAccount();
  auto /*bool*/ BAnonGameServerAccount();
  auto /*bool*/ BContentServerAccount();
  auto /*bool*/ BClanAccount();
  auto /*bool*/ BChatAccount();
  auto /*bool*/ IsLobby();
  auto /*bool*/ BIndividualAccount();
  auto /*bool*/ BAnonAccount();
  auto /*bool*/ BAnonUserAccount();
  auto /*bool*/ BConsoleUserAccount();
  auto /*void*/ SetAccountID(int /* unsigned int Type.INTEGER */ unAccountID);
  auto /*void*/
  SetAccountInstance(int /* unsigned int Type.INTEGER */ unInstance);
  auto /*AccountID_t*/ GetAccountID();
  auto /*uint32*/ GetUnAccountInstance();
  auto /*EAccountType*/ GetEAccountType();
  auto /*EUniverse*/ GetEUniverse();
  auto /*void*/ SetEUniverse(int /* EUniverse Type.ENUM */ eUniverse);
  auto /*bool*/ IsValid();
};

class unsigned_int_box : public SteamBase<unsigned int, unsigned_int_box> {
  GODOT_CLASS(unsigned_int_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class int_box : public SteamBase<int, int_box> {
  GODOT_CLASS(int_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

class ISteamUserStats_box
    : public SteamBase<ISteamUserStats, ISteamUserStats_box> {
  GODOT_CLASS(ISteamUserStats_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
  auto /*bool*/ RequestCurrentStats();
  auto /*bool*/ GetStati(String /* const char * */ pchName);
  auto /*bool*/ GetStatf(String /* const char * */ pchName);
  auto /*bool*/ SetStati(String /* const char * */ pchName,
                         int /* int Type.INTEGER */ nData);
  auto /*bool*/ SetStatf(String /* const char * */ pchName,
                         Ref<float_box> /* float Type.REAL */ fData);
  auto /*bool*/
  UpdateAvgRateStat(String /* const char * */ pchName,
                    Ref<float_box> /* float Type.REAL */ flCountThisSession,
                    Ref<double_box> /* double Type.REAL */ dSessionLength);
  auto /*bool*/ GetAchievement(String /* const char * */ pchName);
  auto /*bool*/ SetAchievement(String /* const char * */ pchName);
  auto /*bool*/ ClearAchievement(String /* const char * */ pchName);
  auto /*bool*/ GetAchievementAndUnlockTime(String /* const char * */ pchName);
  auto /*bool*/ StoreStats();
  auto /*int*/ GetAchievementIcon(String /* const char * */ pchName);
  auto /*const char **/
  GetAchievementDisplayAttribute(String /* const char * */ pchName,
                                 String /* const char * */ pchKey);
  auto /*bool*/
  IndicateAchievementProgress(String /* const char * */ pchName,
                              int /* unsigned int Type.INTEGER */ nCurProgress,
                              int /* unsigned int Type.INTEGER */ nMaxProgress);
  auto /*uint32*/ GetNumAchievements();
  auto /*const char **/
  GetAchievementName(int /* unsigned int Type.INTEGER */ iAchievement);
  auto /*SteamAPICall_t*/
  RequestUserStats(Ref<CSteamID_box> /* CSteamID Type.OBJECT */ steamIDUser);
  auto /*bool*/
  GetUserStati(Ref<CSteamID_box> /* CSteamID Type.OBJECT */ steamIDUser,
               String /* const char * */ pchName);
  auto /*bool*/
  GetUserStatf(Ref<CSteamID_box> /* CSteamID Type.OBJECT */ steamIDUser,
               String /* const char * */ pchName);
  auto /*bool*/
  GetUserAchievement(Ref<CSteamID_box> /* CSteamID Type.OBJECT */ steamIDUser,
                     String /* const char * */ pchName);
  auto /*bool*/ GetUserAchievementAndUnlockTime(
      Ref<CSteamID_box> /* CSteamID Type.OBJECT */ steamIDUser,
      String /* const char * */ pchName);
  auto /*bool*/ ResetAllStats(bool /* bool Type.BOOL */ bAchievementsToo);
  auto /*SteamAPICall_t*/ FindOrCreateLeaderboard(
      String /* const char * */ pchLeaderboardName,
      int /* ELeaderboardSortMethod Type.ENUM */ eLeaderboardSortMethod,
      int /* ELeaderboardDisplayType Type.ENUM */ eLeaderboardDisplayType);
  auto /*SteamAPICall_t*/
  FindLeaderboard(String /* const char * */ pchLeaderboardName);
  auto /*const char **/ GetLeaderboardName(
      int /* unsigned long long Type.INTEGER */ hSteamLeaderboard);
  auto /*int*/ GetLeaderboardEntryCount(
      int /* unsigned long long Type.INTEGER */ hSteamLeaderboard);
  auto /*ELeaderboardSortMethod*/ GetLeaderboardSortMethod(
      int /* unsigned long long Type.INTEGER */ hSteamLeaderboard);
  auto /*ELeaderboardDisplayType*/ GetLeaderboardDisplayType(
      int /* unsigned long long Type.INTEGER */ hSteamLeaderboard);
  auto /*SteamAPICall_t*/ DownloadLeaderboardEntries(
      int /* unsigned long long Type.INTEGER */ hSteamLeaderboard,
      int /* ELeaderboardDataRequest Type.ENUM */ eLeaderboardDataRequest,
      int /* int Type.INTEGER */ nRangeStart,
      int /* int Type.INTEGER */ nRangeEnd);
  auto /*SteamAPICall_t*/ DownloadLeaderboardEntriesForUsers(
      int /* unsigned long long Type.INTEGER */ hSteamLeaderboard,
      int /* int Type.INTEGER */ cUsers);
  auto /*bool*/ GetDownloadedLeaderboardEntry(
      int /* unsigned long long Type.INTEGER */ hSteamLeaderboardEntries,
      int /* int Type.INTEGER */ index, int /* int Type.INTEGER */ cDetailsMax);
  auto /*SteamAPICall_t*/ UploadLeaderboardScore(
      int /* unsigned long long Type.INTEGER */ hSteamLeaderboard,
      int /* ELeaderboardUploadScoreMethod Type.ENUM */
          eLeaderboardUploadScoreMethod,
      int /* int Type.INTEGER */ nScore,
      PoolByteArray /* const int * */ pScoreDetails);
  auto /*SteamAPICall_t*/ AttachLeaderboardUGC(
      int /* unsigned long long Type.INTEGER */ hSteamLeaderboard,
      int /* unsigned long long Type.INTEGER */ hUGC);
  auto /*SteamAPICall_t*/ GetNumberOfCurrentPlayers();
  auto /*SteamAPICall_t*/ RequestGlobalAchievementPercentages();
  auto /*int*/ GetMostAchievedAchievementInfo(
      int /* unsigned int Type.INTEGER */ unNameBufLen);
  auto /*int*/ GetNextMostAchievedAchievementInfo(
      int /* int Type.INTEGER */ iIteratorPrevious,
      int /* unsigned int Type.INTEGER */ unNameBufLen);
  auto /*bool*/
  GetAchievementAchievedPercent(String /* const char * */ pchName);
  auto /*SteamAPICall_t*/
  RequestGlobalStats(int /* int Type.INTEGER */ nHistoryDays);
  auto /*bool*/ GetGlobalStatl(String /* const char * */ pchStatName);
  auto /*bool*/ GetGlobalStatd(String /* const char * */ pchStatName);
};

class ELeaderboardUploadScoreMethod_box
    : public SteamBase<ELeaderboardUploadScoreMethod,
                       ELeaderboardUploadScoreMethod_box> {
  GODOT_CLASS(ELeaderboardUploadScoreMethod_box, Reference)
public:
  static void _register_methods();
  void _init() {}

  /* fields */
};

void EUniverse_box::_register_methods() {}

void AccountID_t_box::_register_methods() {}

void bool_box::_register_methods() {}

void EAccountType_box::_register_methods() {}

void ENotificationPosition_box::_register_methods() {}

void int_const_pointer_box::_register_methods() {}

void ESteamAPICallFailure_box::_register_methods() {}

void bool_pointer_box::_register_methods() {}

void ELeaderboardDataRequest_box::_register_methods() {}

void ESteamIPv6ConnectivityState_box::_register_methods() {}

void CSteamID_pointer_box::_register_methods() {}

void uint64_box::_register_methods() {}

void ELeaderboardDisplayType_box::_register_methods() {}

void unsigned_longlong_box::_register_methods() {}

void unsigned_char_pointer_box::_register_methods() {}

void LeaderboardEntry_t_pointer_box::_register_methods() {}

void int_pointer_box::_register_methods() {}

void ELeaderboardSortMethod_box::_register_methods() {}

void char_const_pointer_box::_register_methods() {}

auto /* uint32, Type.INTEGER */ ISteamUtils_box::GetSecondsSinceAppActive() {
  return call<uint32_box>(
      [&](auto data__) { return data__->GetSecondsSinceAppActive(); });
}

auto /* uint32, Type.INTEGER */
ISteamUtils_box::GetSecondsSinceComputerActive() {
  return call<uint32_box>(
      [&](auto data__) { return data__->GetSecondsSinceComputerActive(); });
}

auto /* EUniverse, Type.ENUM */ ISteamUtils_box::GetConnectedUniverse() {
  return call<EUniverse_box>(
      [&](auto data__) { return data__->GetConnectedUniverse(); });
}

auto /* uint32, Type.INTEGER */ ISteamUtils_box::GetServerRealTime() {
  return call<uint32_box>(
      [&](auto data__) { return data__->GetServerRealTime(); });
}

auto /* const char *, Type.STRING */ ISteamUtils_box::GetIPCountry() {
  return call<char_const_pointer_box>(
      [&](auto data__) { return data__->GetIPCountry(); });
}

auto /* bool, Type.BOOL */
ISteamUtils_box::GetImageSize(int /* int Type.INTEGER */ iImage) {
  unsigned int /* unsigned int *, Type.INTEGER */ pnWidth{};
  unsigned int /* unsigned int *, Type.INTEGER */ pnHeight{};
  return call<bool_box>([&](auto data__) {
    return data__->GetImageSize(iImage, &pnWidth, &pnHeight);
  });
}

auto /* bool, Type.BOOL */
ISteamUtils_box::GetImageRGBA(int /* int Type.INTEGER */ iImage,
                              int /* int Type.INTEGER */ nDestBufferSize) {
  PoolByteArray /* unsigned char *, Type.INTEGER */ pubDest{};
  pubDest.resize(nDestBufferSize);
  return call<bool_box>([&](auto data__) {
    return data__->GetImageRGBA(
        iImage, reinterpret_cast<unsigned char *>(pubDest.write().ptr()),
        pubDest.size());
  });
}

auto /* uint8, Type.INTEGER */ ISteamUtils_box::GetCurrentBatteryPower() {
  return call<uint8_box>(
      [&](auto data__) { return data__->GetCurrentBatteryPower(); });
}

auto /* uint32, Type.INTEGER */ ISteamUtils_box::GetAppID() {
  return call<uint32_box>([&](auto data__) { return data__->GetAppID(); });
}

auto /* void, Type.VOID */ ISteamUtils_box::SetOverlayNotificationPosition(
    int /* ENotificationPosition Type.ENUM */ eNotificationPosition) {
  return call<void_box>([&](auto data__) {
    return data__->SetOverlayNotificationPosition(
        static_cast<ENotificationPosition>(eNotificationPosition));
  });
}

auto /* bool, Type.BOOL */ ISteamUtils_box::IsAPICallCompleted(
    int /* unsigned long long Type.INTEGER */ hSteamAPICall) {
  bool /* bool *, Type.BOOL */ pbFailed{};
  return call<bool_box>([&](auto data__) {
    return data__->IsAPICallCompleted(hSteamAPICall, &pbFailed);
  });
}

auto /* ESteamAPICallFailure, Type.ENUM */
ISteamUtils_box::GetAPICallFailureReason(
    int /* unsigned long long Type.INTEGER */ hSteamAPICall) {
  return call<ESteamAPICallFailure_box>([&](auto data__) {
    return data__->GetAPICallFailureReason(hSteamAPICall);
  });
}

auto /* uint32, Type.INTEGER */ ISteamUtils_box::GetIPCCallCount() {
  return call<uint32_box>(
      [&](auto data__) { return data__->GetIPCCallCount(); });
}

auto /* bool, Type.BOOL */ ISteamUtils_box::IsOverlayEnabled() {
  return call<bool_box>(
      [&](auto data__) { return data__->IsOverlayEnabled(); });
}

auto /* bool, Type.BOOL */ ISteamUtils_box::BOverlayNeedsPresent() {
  return call<bool_box>(
      [&](auto data__) { return data__->BOverlayNeedsPresent(); });
}

auto /* SteamAPICall_t, Type.OBJECT */
ISteamUtils_box::CheckFileSignature(String /* const char * */ szFileName) {
  return call<SteamAPICall_t_box>([&](auto data__) {
    return data__->CheckFileSignature(szFileName.utf8().get_data());
  });
}

auto /* bool, Type.BOOL */ ISteamUtils_box::ShowGamepadTextInput(
    int /* EGamepadTextInputMode Type.ENUM */ eInputMode,
    int /* EGamepadTextInputLineMode Type.ENUM */ eLineInputMode,
    String /* const char * */ pchDescription,
    int /* unsigned int Type.INTEGER */ unCharMax,
    String /* const char * */ pchExistingText) {
  return call<bool_box>([&](auto data__) {
    return data__->ShowGamepadTextInput(
        static_cast<EGamepadTextInputMode>(eInputMode),
        static_cast<EGamepadTextInputLineMode>(eLineInputMode),
        pchDescription.utf8().get_data(), unCharMax,
        pchExistingText.utf8().get_data());
  });
}

auto /* uint32, Type.INTEGER */ ISteamUtils_box::GetEnteredGamepadTextLength() {
  return call<uint32_box>(
      [&](auto data__) { return data__->GetEnteredGamepadTextLength(); });
}

auto /* bool, Type.BOOL */ ISteamUtils_box::GetEnteredGamepadTextInput(
    int /* unsigned int Type.INTEGER */ cchText) {
  PoolByteArray /* char *, Type.INTEGER */ pchText{};
  pchText.resize(cchText);
  return call<bool_box>([&](auto data__) {
    return data__->GetEnteredGamepadTextInput(
        reinterpret_cast<char *>(pchText.write().ptr()), pchText.size());
  });
}

auto /* const char *, Type.STRING */ ISteamUtils_box::GetSteamUILanguage() {
  return call<char_const_pointer_box>(
      [&](auto data__) { return data__->GetSteamUILanguage(); });
}

auto /* bool, Type.BOOL */ ISteamUtils_box::IsSteamRunningInVR() {
  return call<bool_box>(
      [&](auto data__) { return data__->IsSteamRunningInVR(); });
}

auto /* void, Type.VOID */ ISteamUtils_box::SetOverlayNotificationInset(
    int /* int Type.INTEGER */ nHorizontalInset,
    int /* int Type.INTEGER */ nVerticalInset) {
  return call<void_box>([&](auto data__) {
    return data__->SetOverlayNotificationInset(nHorizontalInset,
                                               nVerticalInset);
  });
}

auto /* bool, Type.BOOL */ ISteamUtils_box::IsSteamInBigPictureMode() {
  return call<bool_box>(
      [&](auto data__) { return data__->IsSteamInBigPictureMode(); });
}

auto /* void, Type.VOID */ ISteamUtils_box::StartVRDashboard() {
  return call<void_box>(
      [&](auto data__) { return data__->StartVRDashboard(); });
}

auto /* bool, Type.BOOL */ ISteamUtils_box::IsVRHeadsetStreamingEnabled() {
  return call<bool_box>(
      [&](auto data__) { return data__->IsVRHeadsetStreamingEnabled(); });
}

auto /* void, Type.VOID */ ISteamUtils_box::SetVRHeadsetStreamingEnabled(
    bool /* bool Type.BOOL */ bEnabled) {
  return call<void_box>([&](auto data__) {
    return data__->SetVRHeadsetStreamingEnabled(bEnabled);
  });
}

auto /* bool, Type.BOOL */ ISteamUtils_box::IsSteamChinaLauncher() {
  return call<bool_box>(
      [&](auto data__) { return data__->IsSteamChinaLauncher(); });
}

auto /* bool, Type.BOOL */ ISteamUtils_box::InitFilterText(
    int /* unsigned int Type.INTEGER */ unFilterOptions) {
  return call<bool_box>(
      [&](auto data__) { return data__->InitFilterText(unFilterOptions); });
}

auto /* int, Type.INTEGER */ ISteamUtils_box::FilterText(
    int /* ETextFilteringContext Type.ENUM */ eContext,
    Ref<CSteamID_box> /* CSteamID Type.OBJECT */ sourceSteamID,
    String /* const char * */ pchInputMessage,
    int /* unsigned int Type.INTEGER */ nByteSizeOutFilteredText) {
  PoolByteArray /* char *, Type.INTEGER */ pchOutFilteredText{};
  pchOutFilteredText.resize(nByteSizeOutFilteredText);
  return call<int_box>([&](auto data__) {
    return data__->FilterText(
        static_cast<ETextFilteringContext>(eContext), sourceSteamID->get(),
        pchInputMessage.utf8().get_data(),
        reinterpret_cast<char *>(pchOutFilteredText.write().ptr()),
        pchOutFilteredText.size());
  });
}

auto /* ESteamIPv6ConnectivityState, Type.ENUM */
ISteamUtils_box::GetIPv6ConnectivityState(
    int /* ESteamIPv6ConnectivityProtocol Type.ENUM */ eProtocol) {
  return call<ESteamIPv6ConnectivityState_box>([&](auto data__) {
    return data__->GetIPv6ConnectivityState(
        static_cast<ESteamIPv6ConnectivityProtocol>(eProtocol));
  });
}

auto /* bool, Type.BOOL */ ISteamUtils_box::IsSteamRunningOnSteamDeck() {
  return call<bool_box>(
      [&](auto data__) { return data__->IsSteamRunningOnSteamDeck(); });
}

auto /* bool, Type.BOOL */ ISteamUtils_box::ShowFloatingGamepadTextInput(
    int /* EFloatingGamepadTextInputMode Type.ENUM */ eKeyboardMode,
    int /* int Type.INTEGER */ nTextFieldXPosition,
    int /* int Type.INTEGER */ nTextFieldYPosition,
    int /* int Type.INTEGER */ nTextFieldWidth,
    int /* int Type.INTEGER */ nTextFieldHeight) {
  return call<bool_box>([&](auto data__) {
    return data__->ShowFloatingGamepadTextInput(
        static_cast<EFloatingGamepadTextInputMode>(eKeyboardMode),
        nTextFieldXPosition, nTextFieldYPosition, nTextFieldWidth,
        nTextFieldHeight);
  });
}

auto /* void, Type.VOID */
ISteamUtils_box::SetGameLauncherMode(bool /* bool Type.BOOL */ bLauncherMode) {
  return call<void_box>(
      [&](auto data__) { return data__->SetGameLauncherMode(bLauncherMode); });
}

void ISteamUtils_box::_register_methods() {
  register_method("GetSecondsSinceAppActive",
                  &ISteamUtils_box::GetSecondsSinceAppActive);
  register_method("GetSecondsSinceComputerActive",
                  &ISteamUtils_box::GetSecondsSinceComputerActive);
  register_method("GetConnectedUniverse",
                  &ISteamUtils_box::GetConnectedUniverse);
  register_method("GetServerRealTime", &ISteamUtils_box::GetServerRealTime);
  register_method("GetIPCountry", &ISteamUtils_box::GetIPCountry);
  register_method("GetImageSize", &ISteamUtils_box::GetImageSize);
  register_method("GetImageRGBA", &ISteamUtils_box::GetImageRGBA);
  register_method("GetCurrentBatteryPower",
                  &ISteamUtils_box::GetCurrentBatteryPower);
  register_method("GetAppID", &ISteamUtils_box::GetAppID);
  register_method("SetOverlayNotificationPosition",
                  &ISteamUtils_box::SetOverlayNotificationPosition);
  register_method("IsAPICallCompleted", &ISteamUtils_box::IsAPICallCompleted);
  register_method("GetAPICallFailureReason",
                  &ISteamUtils_box::GetAPICallFailureReason);
  register_method("GetIPCCallCount", &ISteamUtils_box::GetIPCCallCount);
  register_method("IsOverlayEnabled", &ISteamUtils_box::IsOverlayEnabled);
  register_method("BOverlayNeedsPresent",
                  &ISteamUtils_box::BOverlayNeedsPresent);
  register_method("CheckFileSignature", &ISteamUtils_box::CheckFileSignature);
  register_method("ShowGamepadTextInput",
                  &ISteamUtils_box::ShowGamepadTextInput);
  register_method("GetEnteredGamepadTextLength",
                  &ISteamUtils_box::GetEnteredGamepadTextLength);
  register_method("GetEnteredGamepadTextInput",
                  &ISteamUtils_box::GetEnteredGamepadTextInput);
  register_method("GetSteamUILanguage", &ISteamUtils_box::GetSteamUILanguage);
  register_method("IsSteamRunningInVR", &ISteamUtils_box::IsSteamRunningInVR);
  register_method("SetOverlayNotificationInset",
                  &ISteamUtils_box::SetOverlayNotificationInset);
  register_method("IsSteamInBigPictureMode",
                  &ISteamUtils_box::IsSteamInBigPictureMode);
  register_method("StartVRDashboard", &ISteamUtils_box::StartVRDashboard);
  register_method("IsVRHeadsetStreamingEnabled",
                  &ISteamUtils_box::IsVRHeadsetStreamingEnabled);
  register_method("SetVRHeadsetStreamingEnabled",
                  &ISteamUtils_box::SetVRHeadsetStreamingEnabled);
  register_method("IsSteamChinaLauncher",
                  &ISteamUtils_box::IsSteamChinaLauncher);
  register_method("InitFilterText", &ISteamUtils_box::InitFilterText);
  register_method("FilterText", &ISteamUtils_box::FilterText);
  register_method("GetIPv6ConnectivityState",
                  &ISteamUtils_box::GetIPv6ConnectivityState);
  register_method("IsSteamRunningOnSteamDeck",
                  &ISteamUtils_box::IsSteamRunningOnSteamDeck);
  register_method("ShowFloatingGamepadTextInput",
                  &ISteamUtils_box::ShowFloatingGamepadTextInput);
  register_method("SetGameLauncherMode", &ISteamUtils_box::SetGameLauncherMode);
}

void float_box::_register_methods() {}

void uint8_box::_register_methods() {}

void float_pointer_box::_register_methods() {}

void ESteamIPv6ConnectivityProtocol_box::_register_methods() {}

void longlong_pointer_box::_register_methods() {}

void uint32_box::_register_methods() {}

void char_pointer_box::_register_methods() {}

void ETextFilteringContext_box::_register_methods() {}

void double_box::_register_methods() {}

void EFloatingGamepadTextInputMode_box::_register_methods() {}

void EGamepadTextInputLineMode_box::_register_methods() {}

void EGamepadTextInputMode_box::_register_methods() {}

void double_pointer_box::_register_methods() {}

void unsigned_int_pointer_box::_register_methods() {}

auto /* void, Type.VOID */
CSteamID_box::Set(int /* unsigned int Type.INTEGER */ unAccountID,
                  int /* EUniverse Type.ENUM */ eUniverse,
                  int /* EAccountType Type.ENUM */ eAccountType) {
  return call<void_box>([&](auto data__) {
    return data__->Set(unAccountID, static_cast<EUniverse>(eUniverse),
                       static_cast<EAccountType>(eAccountType));
  });
}

auto /* void, Type.VOID */
CSteamID_box::InstancedSet(int /* unsigned int Type.INTEGER */ unAccountID,
                           int /* unsigned int Type.INTEGER */ unInstance,
                           int /* EUniverse Type.ENUM */ eUniverse,
                           int /* EAccountType Type.ENUM */ eAccountType) {
  return call<void_box>([&](auto data__) {
    return data__->InstancedSet(unAccountID, unInstance,
                                static_cast<EUniverse>(eUniverse),
                                static_cast<EAccountType>(eAccountType));
  });
}

auto /* void, Type.VOID */
CSteamID_box::FullSet(int /* unsigned long long Type.INTEGER */ ulIdentifier,
                      int /* EUniverse Type.ENUM */ eUniverse,
                      int /* EAccountType Type.ENUM */ eAccountType) {
  return call<void_box>([&](auto data__) {
    return data__->FullSet(ulIdentifier, static_cast<EUniverse>(eUniverse),
                           static_cast<EAccountType>(eAccountType));
  });
}

auto /* void, Type.VOID */ CSteamID_box::SetFromUint64(
    int /* unsigned long long Type.INTEGER */ ulSteamID) {
  return call<void_box>(
      [&](auto data__) { return data__->SetFromUint64(ulSteamID); });
}

auto /* void, Type.VOID */ CSteamID_box::Clear() {
  return call<void_box>([&](auto data__) { return data__->Clear(); });
}

auto /* uint64, Type.INTEGER */ CSteamID_box::ConvertToUint64() {
  return call<uint64_box>(
      [&](auto data__) { return data__->ConvertToUint64(); });
}

auto /* uint64, Type.INTEGER */ CSteamID_box::GetStaticAccountKey() {
  return call<uint64_box>(
      [&](auto data__) { return data__->GetStaticAccountKey(); });
}

auto /* void, Type.VOID */
CSteamID_box::CreateBlankAnonLogon(int /* EUniverse Type.ENUM */ eUniverse) {
  return call<void_box>([&](auto data__) {
    return data__->CreateBlankAnonLogon(static_cast<EUniverse>(eUniverse));
  });
}

auto /* void, Type.VOID */ CSteamID_box::CreateBlankAnonUserLogon(
    int /* EUniverse Type.ENUM */ eUniverse) {
  return call<void_box>([&](auto data__) {
    return data__->CreateBlankAnonUserLogon(static_cast<EUniverse>(eUniverse));
  });
}

auto /* bool, Type.BOOL */ CSteamID_box::BBlankAnonAccount() {
  return call<bool_box>(
      [&](auto data__) { return data__->BBlankAnonAccount(); });
}

auto /* bool, Type.BOOL */ CSteamID_box::BGameServerAccount() {
  return call<bool_box>(
      [&](auto data__) { return data__->BGameServerAccount(); });
}

auto /* bool, Type.BOOL */ CSteamID_box::BPersistentGameServerAccount() {
  return call<bool_box>(
      [&](auto data__) { return data__->BPersistentGameServerAccount(); });
}

auto /* bool, Type.BOOL */ CSteamID_box::BAnonGameServerAccount() {
  return call<bool_box>(
      [&](auto data__) { return data__->BAnonGameServerAccount(); });
}

auto /* bool, Type.BOOL */ CSteamID_box::BContentServerAccount() {
  return call<bool_box>(
      [&](auto data__) { return data__->BContentServerAccount(); });
}

auto /* bool, Type.BOOL */ CSteamID_box::BClanAccount() {
  return call<bool_box>([&](auto data__) { return data__->BClanAccount(); });
}

auto /* bool, Type.BOOL */ CSteamID_box::BChatAccount() {
  return call<bool_box>([&](auto data__) { return data__->BChatAccount(); });
}

auto /* bool, Type.BOOL */ CSteamID_box::IsLobby() {
  return call<bool_box>([&](auto data__) { return data__->IsLobby(); });
}

auto /* bool, Type.BOOL */ CSteamID_box::BIndividualAccount() {
  return call<bool_box>(
      [&](auto data__) { return data__->BIndividualAccount(); });
}

auto /* bool, Type.BOOL */ CSteamID_box::BAnonAccount() {
  return call<bool_box>([&](auto data__) { return data__->BAnonAccount(); });
}

auto /* bool, Type.BOOL */ CSteamID_box::BAnonUserAccount() {
  return call<bool_box>(
      [&](auto data__) { return data__->BAnonUserAccount(); });
}

auto /* bool, Type.BOOL */ CSteamID_box::BConsoleUserAccount() {
  return call<bool_box>(
      [&](auto data__) { return data__->BConsoleUserAccount(); });
}

auto /* void, Type.VOID */
CSteamID_box::SetAccountID(int /* unsigned int Type.INTEGER */ unAccountID) {
  return call<void_box>(
      [&](auto data__) { return data__->SetAccountID(unAccountID); });
}

auto /* void, Type.VOID */ CSteamID_box::SetAccountInstance(
    int /* unsigned int Type.INTEGER */ unInstance) {
  return call<void_box>(
      [&](auto data__) { return data__->SetAccountInstance(unInstance); });
}

auto /* AccountID_t, Type.INTEGER */ CSteamID_box::GetAccountID() {
  return call<AccountID_t_box>(
      [&](auto data__) { return data__->GetAccountID(); });
}

auto /* uint32, Type.INTEGER */ CSteamID_box::GetUnAccountInstance() {
  return call<uint32_box>(
      [&](auto data__) { return data__->GetUnAccountInstance(); });
}

auto /* EAccountType, Type.ENUM */ CSteamID_box::GetEAccountType() {
  return call<EAccountType_box>(
      [&](auto data__) { return data__->GetEAccountType(); });
}

auto /* EUniverse, Type.ENUM */ CSteamID_box::GetEUniverse() {
  return call<EUniverse_box>(
      [&](auto data__) { return data__->GetEUniverse(); });
}

auto /* void, Type.VOID */
CSteamID_box::SetEUniverse(int /* EUniverse Type.ENUM */ eUniverse) {
  return call<void_box>([&](auto data__) {
    return data__->SetEUniverse(static_cast<EUniverse>(eUniverse));
  });
}

auto /* bool, Type.BOOL */ CSteamID_box::IsValid() {
  return call<bool_box>([&](auto data__) { return data__->IsValid(); });
}

void CSteamID_box::_register_methods() {
  register_method("Set", &CSteamID_box::Set);
  register_method("InstancedSet", &CSteamID_box::InstancedSet);
  register_method("FullSet", &CSteamID_box::FullSet);
  register_method("SetFromUint64", &CSteamID_box::SetFromUint64);
  register_method("Clear", &CSteamID_box::Clear);
  register_method("ConvertToUint64", &CSteamID_box::ConvertToUint64);
  register_method("GetStaticAccountKey", &CSteamID_box::GetStaticAccountKey);
  register_method("CreateBlankAnonLogon", &CSteamID_box::CreateBlankAnonLogon);
  register_method("CreateBlankAnonUserLogon",
                  &CSteamID_box::CreateBlankAnonUserLogon);
  register_method("BBlankAnonAccount", &CSteamID_box::BBlankAnonAccount);
  register_method("BGameServerAccount", &CSteamID_box::BGameServerAccount);
  register_method("BPersistentGameServerAccount",
                  &CSteamID_box::BPersistentGameServerAccount);
  register_method("BAnonGameServerAccount",
                  &CSteamID_box::BAnonGameServerAccount);
  register_method("BContentServerAccount",
                  &CSteamID_box::BContentServerAccount);
  register_method("BClanAccount", &CSteamID_box::BClanAccount);
  register_method("BChatAccount", &CSteamID_box::BChatAccount);
  register_method("IsLobby", &CSteamID_box::IsLobby);
  register_method("BIndividualAccount", &CSteamID_box::BIndividualAccount);
  register_method("BAnonAccount", &CSteamID_box::BAnonAccount);
  register_method("BAnonUserAccount", &CSteamID_box::BAnonUserAccount);
  register_method("BConsoleUserAccount", &CSteamID_box::BConsoleUserAccount);
  register_method("SetAccountID", &CSteamID_box::SetAccountID);
  register_method("SetAccountInstance", &CSteamID_box::SetAccountInstance);
  register_method("GetAccountID", &CSteamID_box::GetAccountID);
  register_method("GetUnAccountInstance", &CSteamID_box::GetUnAccountInstance);
  register_method("GetEAccountType", &CSteamID_box::GetEAccountType);
  register_method("GetEUniverse", &CSteamID_box::GetEUniverse);
  register_method("SetEUniverse", &CSteamID_box::SetEUniverse);
  register_method("IsValid", &CSteamID_box::IsValid);
}

void unsigned_int_box::_register_methods() {}

void int_box::_register_methods() {}

auto /* bool, Type.BOOL */ ISteamUserStats_box::RequestCurrentStats() {
  return call<bool_box>(
      [&](auto data__) { return data__->RequestCurrentStats(); });
}

auto /* bool, Type.BOOL */
ISteamUserStats_box::GetStati(String /* const char * */ pchName) {
  int /* int *, Type.INTEGER */ pData{};
  return call<bool_box>([&](auto data__) {
    return data__->GetStat(pchName.utf8().get_data(), &pData);
  });
}

auto /* bool, Type.BOOL */
ISteamUserStats_box::GetStatf(String /* const char * */ pchName) {
  float /* float *, Type.REAL */ pData{};
  return call<bool_box>([&](auto data__) {
    return data__->GetStat(pchName.utf8().get_data(), &pData);
  });
}

auto /* bool, Type.BOOL */
ISteamUserStats_box::SetStati(String /* const char * */ pchName,
                              int /* int Type.INTEGER */ nData) {
  return call<bool_box>([&](auto data__) {
    return data__->SetStat(pchName.utf8().get_data(), nData);
  });
}

auto /* bool, Type.BOOL */
ISteamUserStats_box::SetStatf(String /* const char * */ pchName,
                              Ref<float_box> /* float Type.REAL */ fData) {
  return call<bool_box>([&](auto data__) {
    return data__->SetStat(pchName.utf8().get_data(), fData->get());
  });
}

auto /* bool, Type.BOOL */ ISteamUserStats_box::UpdateAvgRateStat(
    String /* const char * */ pchName,
    Ref<float_box> /* float Type.REAL */ flCountThisSession,
    Ref<double_box> /* double Type.REAL */ dSessionLength) {
  return call<bool_box>([&](auto data__) {
    return data__->UpdateAvgRateStat(pchName.utf8().get_data(),
                                     flCountThisSession->get(),
                                     dSessionLength->get());
  });
}

auto /* bool, Type.BOOL */
ISteamUserStats_box::GetAchievement(String /* const char * */ pchName) {
  bool /* bool *, Type.BOOL */ pbAchieved{};
  return call<bool_box>([&](auto data__) {
    return data__->GetAchievement(pchName.utf8().get_data(), &pbAchieved);
  });
}

auto /* bool, Type.BOOL */
ISteamUserStats_box::SetAchievement(String /* const char * */ pchName) {
  return call<bool_box>([&](auto data__) {
    return data__->SetAchievement(pchName.utf8().get_data());
  });
}

auto /* bool, Type.BOOL */
ISteamUserStats_box::ClearAchievement(String /* const char * */ pchName) {
  return call<bool_box>([&](auto data__) {
    return data__->ClearAchievement(pchName.utf8().get_data());
  });
}

auto /* bool, Type.BOOL */ ISteamUserStats_box::GetAchievementAndUnlockTime(
    String /* const char * */ pchName) {
  bool /* bool *, Type.BOOL */ pbAchieved{};
  unsigned int /* unsigned int *, Type.INTEGER */ punUnlockTime{};
  return call<bool_box>([&](auto data__) {
    return data__->GetAchievementAndUnlockTime(pchName.utf8().get_data(),
                                               &pbAchieved, &punUnlockTime);
  });
}

auto /* bool, Type.BOOL */ ISteamUserStats_box::StoreStats() {
  return call<bool_box>([&](auto data__) { return data__->StoreStats(); });
}

auto /* int, Type.INTEGER */
ISteamUserStats_box::GetAchievementIcon(String /* const char * */ pchName) {
  return call<int_box>([&](auto data__) {
    return data__->GetAchievementIcon(pchName.utf8().get_data());
  });
}

auto /* const char *, Type.STRING */
ISteamUserStats_box::GetAchievementDisplayAttribute(
    String /* const char * */ pchName, String /* const char * */ pchKey) {
  return call<char_const_pointer_box>([&](auto data__) {
    return data__->GetAchievementDisplayAttribute(pchName.utf8().get_data(),
                                                  pchKey.utf8().get_data());
  });
}

auto /* bool, Type.BOOL */ ISteamUserStats_box::IndicateAchievementProgress(
    String /* const char * */ pchName,
    int /* unsigned int Type.INTEGER */ nCurProgress,
    int /* unsigned int Type.INTEGER */ nMaxProgress) {
  return call<bool_box>([&](auto data__) {
    return data__->IndicateAchievementProgress(pchName.utf8().get_data(),
                                               nCurProgress, nMaxProgress);
  });
}

auto /* uint32, Type.INTEGER */ ISteamUserStats_box::GetNumAchievements() {
  return call<uint32_box>(
      [&](auto data__) { return data__->GetNumAchievements(); });
}

auto /* const char *, Type.STRING */ ISteamUserStats_box::GetAchievementName(
    int /* unsigned int Type.INTEGER */ iAchievement) {
  return call<char_const_pointer_box>(
      [&](auto data__) { return data__->GetAchievementName(iAchievement); });
}

auto /* SteamAPICall_t, Type.OBJECT */ ISteamUserStats_box::RequestUserStats(
    Ref<CSteamID_box> /* CSteamID Type.OBJECT */ steamIDUser) {
  return call<SteamAPICall_t_box>([&](auto data__) {
    return data__->RequestUserStats(steamIDUser->get());
  });
}

auto /* bool, Type.BOOL */ ISteamUserStats_box::GetUserStati(
    Ref<CSteamID_box> /* CSteamID Type.OBJECT */ steamIDUser,
    String /* const char * */ pchName) {
  int /* int *, Type.INTEGER */ pData{};
  return call<bool_box>([&](auto data__) {
    return data__->GetUserStat(steamIDUser->get(), pchName.utf8().get_data(),
                               &pData);
  });
}

auto /* bool, Type.BOOL */ ISteamUserStats_box::GetUserStatf(
    Ref<CSteamID_box> /* CSteamID Type.OBJECT */ steamIDUser,
    String /* const char * */ pchName) {
  float /* float *, Type.REAL */ pData{};
  return call<bool_box>([&](auto data__) {
    return data__->GetUserStat(steamIDUser->get(), pchName.utf8().get_data(),
                               &pData);
  });
}

auto /* bool, Type.BOOL */ ISteamUserStats_box::GetUserAchievement(
    Ref<CSteamID_box> /* CSteamID Type.OBJECT */ steamIDUser,
    String /* const char * */ pchName) {
  bool /* bool *, Type.BOOL */ pbAchieved{};
  return call<bool_box>([&](auto data__) {
    return data__->GetUserAchievement(steamIDUser->get(),
                                      pchName.utf8().get_data(), &pbAchieved);
  });
}

auto /* bool, Type.BOOL */ ISteamUserStats_box::GetUserAchievementAndUnlockTime(
    Ref<CSteamID_box> /* CSteamID Type.OBJECT */ steamIDUser,
    String /* const char * */ pchName) {
  bool /* bool *, Type.BOOL */ pbAchieved{};
  unsigned int /* unsigned int *, Type.INTEGER */ punUnlockTime{};
  return call<bool_box>([&](auto data__) {
    return data__->GetUserAchievementAndUnlockTime(steamIDUser->get(),
                                                   pchName.utf8().get_data(),
                                                   &pbAchieved, &punUnlockTime);
  });
}

auto /* bool, Type.BOOL */
ISteamUserStats_box::ResetAllStats(bool /* bool Type.BOOL */ bAchievementsToo) {
  return call<bool_box>(
      [&](auto data__) { return data__->ResetAllStats(bAchievementsToo); });
}

auto /* SteamAPICall_t, Type.OBJECT */
ISteamUserStats_box::FindOrCreateLeaderboard(
    String /* const char * */ pchLeaderboardName,
    int /* ELeaderboardSortMethod Type.ENUM */ eLeaderboardSortMethod,
    int /* ELeaderboardDisplayType Type.ENUM */ eLeaderboardDisplayType) {
  return call<SteamAPICall_t_box>([&](auto data__) {
    return data__->FindOrCreateLeaderboard(
        pchLeaderboardName.utf8().get_data(),
        static_cast<ELeaderboardSortMethod>(eLeaderboardSortMethod),
        static_cast<ELeaderboardDisplayType>(eLeaderboardDisplayType));
  });
}

auto /* SteamAPICall_t, Type.OBJECT */ ISteamUserStats_box::FindLeaderboard(
    String /* const char * */ pchLeaderboardName) {
  return call<SteamAPICall_t_box>([&](auto data__) {
    return data__->FindLeaderboard(pchLeaderboardName.utf8().get_data());
  });
}

auto /* const char *, Type.STRING */ ISteamUserStats_box::GetLeaderboardName(
    int /* unsigned long long Type.INTEGER */ hSteamLeaderboard) {
  return call<char_const_pointer_box>([&](auto data__) {
    return data__->GetLeaderboardName(hSteamLeaderboard);
  });
}

auto /* int, Type.INTEGER */ ISteamUserStats_box::GetLeaderboardEntryCount(
    int /* unsigned long long Type.INTEGER */ hSteamLeaderboard) {
  return call<int_box>([&](auto data__) {
    return data__->GetLeaderboardEntryCount(hSteamLeaderboard);
  });
}

auto /* ELeaderboardSortMethod, Type.ENUM */
ISteamUserStats_box::GetLeaderboardSortMethod(
    int /* unsigned long long Type.INTEGER */ hSteamLeaderboard) {
  return call<ELeaderboardSortMethod_box>([&](auto data__) {
    return data__->GetLeaderboardSortMethod(hSteamLeaderboard);
  });
}

auto /* ELeaderboardDisplayType, Type.ENUM */
ISteamUserStats_box::GetLeaderboardDisplayType(
    int /* unsigned long long Type.INTEGER */ hSteamLeaderboard) {
  return call<ELeaderboardDisplayType_box>([&](auto data__) {
    return data__->GetLeaderboardDisplayType(hSteamLeaderboard);
  });
}

auto /* SteamAPICall_t, Type.OBJECT */
ISteamUserStats_box::DownloadLeaderboardEntries(
    int /* unsigned long long Type.INTEGER */ hSteamLeaderboard,
    int /* ELeaderboardDataRequest Type.ENUM */ eLeaderboardDataRequest,
    int /* int Type.INTEGER */ nRangeStart,
    int /* int Type.INTEGER */ nRangeEnd) {
  return call<SteamAPICall_t_box>([&](auto data__) {
    return data__->DownloadLeaderboardEntries(
        hSteamLeaderboard,
        static_cast<ELeaderboardDataRequest>(eLeaderboardDataRequest),
        nRangeStart, nRangeEnd);
  });
}

auto /* SteamAPICall_t, Type.OBJECT */
ISteamUserStats_box::DownloadLeaderboardEntriesForUsers(
    int /* unsigned long long Type.INTEGER */ hSteamLeaderboard,
    int /* int Type.INTEGER */ cUsers) {
  CSteamID /* CSteamID *, Type.OBJECT */ prgUsers{};
  return call<SteamAPICall_t_box>([&](auto data__) {
    return data__->DownloadLeaderboardEntriesForUsers(hSteamLeaderboard,
                                                      &prgUsers, cUsers);
  });
}

auto /* bool, Type.BOOL */ ISteamUserStats_box::GetDownloadedLeaderboardEntry(
    int /* unsigned long long Type.INTEGER */ hSteamLeaderboardEntries,
    int /* int Type.INTEGER */ index, int /* int Type.INTEGER */ cDetailsMax) {
  LeaderboardEntry_t /* LeaderboardEntry_t *, Type.OBJECT */
      pLeaderboardEntry{};
  PoolByteArray /* int *, Type.INTEGER */ pDetails{};
  pDetails.resize(cDetailsMax);
  return call<bool_box>([&](auto data__) {
    return data__->GetDownloadedLeaderboardEntry(
        hSteamLeaderboardEntries, index, &pLeaderboardEntry,
        reinterpret_cast<int *>(pDetails.write().ptr()), pDetails.size());
  });
}

auto /* SteamAPICall_t, Type.OBJECT */
ISteamUserStats_box::UploadLeaderboardScore(
    int /* unsigned long long Type.INTEGER */ hSteamLeaderboard,
    int /* ELeaderboardUploadScoreMethod Type.ENUM */
        eLeaderboardUploadScoreMethod,
    int /* int Type.INTEGER */ nScore,
    PoolByteArray /* const int * */ pScoreDetails) {
  return call<SteamAPICall_t_box>([&](auto data__) {
    return data__->UploadLeaderboardScore(
        hSteamLeaderboard,
        static_cast<ELeaderboardUploadScoreMethod>(
            eLeaderboardUploadScoreMethod),
        nScore, reinterpret_cast<const int *>(pScoreDetails.read().ptr()),
        pScoreDetails.size());
  });
}

auto /* SteamAPICall_t, Type.OBJECT */
ISteamUserStats_box::AttachLeaderboardUGC(
    int /* unsigned long long Type.INTEGER */ hSteamLeaderboard,
    int /* unsigned long long Type.INTEGER */ hUGC) {
  return call<SteamAPICall_t_box>([&](auto data__) {
    return data__->AttachLeaderboardUGC(hSteamLeaderboard, hUGC);
  });
}

auto /* SteamAPICall_t, Type.OBJECT */
ISteamUserStats_box::GetNumberOfCurrentPlayers() {
  return call<SteamAPICall_t_box>(
      [&](auto data__) { return data__->GetNumberOfCurrentPlayers(); });
}

auto /* SteamAPICall_t, Type.OBJECT */
ISteamUserStats_box::RequestGlobalAchievementPercentages() {
  return call<SteamAPICall_t_box>([&](auto data__) {
    return data__->RequestGlobalAchievementPercentages();
  });
}

auto /* int, Type.INTEGER */
ISteamUserStats_box::GetMostAchievedAchievementInfo(
    int /* unsigned int Type.INTEGER */ unNameBufLen) {
  PoolByteArray /* char *, Type.INTEGER */ pchName{};
  pchName.resize(unNameBufLen);
  float /* float *, Type.REAL */ pflPercent{};
  bool /* bool *, Type.BOOL */ pbAchieved{};
  return call<int_box>([&](auto data__) {
    return data__->GetMostAchievedAchievementInfo(
        reinterpret_cast<char *>(pchName.write().ptr()), pchName.size(),
        &pflPercent, &pbAchieved);
  });
}

auto /* int, Type.INTEGER */
ISteamUserStats_box::GetNextMostAchievedAchievementInfo(
    int /* int Type.INTEGER */ iIteratorPrevious,
    int /* unsigned int Type.INTEGER */ unNameBufLen) {
  PoolByteArray /* char *, Type.INTEGER */ pchName{};
  pchName.resize(unNameBufLen);
  float /* float *, Type.REAL */ pflPercent{};
  bool /* bool *, Type.BOOL */ pbAchieved{};
  return call<int_box>([&](auto data__) {
    return data__->GetNextMostAchievedAchievementInfo(
        iIteratorPrevious, reinterpret_cast<char *>(pchName.write().ptr()),
        pchName.size(), &pflPercent, &pbAchieved);
  });
}

auto /* bool, Type.BOOL */ ISteamUserStats_box::GetAchievementAchievedPercent(
    String /* const char * */ pchName) {
  float /* float *, Type.REAL */ pflPercent{};
  return call<bool_box>([&](auto data__) {
    return data__->GetAchievementAchievedPercent(pchName.utf8().get_data(),
                                                 &pflPercent);
  });
}

auto /* SteamAPICall_t, Type.OBJECT */ ISteamUserStats_box::RequestGlobalStats(
    int /* int Type.INTEGER */ nHistoryDays) {
  return call<SteamAPICall_t_box>(
      [&](auto data__) { return data__->RequestGlobalStats(nHistoryDays); });
}

auto /* bool, Type.BOOL */
ISteamUserStats_box::GetGlobalStatl(String /* const char * */ pchStatName) {
  long long /* long long *, Type.INTEGER */ pData{};
  return call<bool_box>([&](auto data__) {
    return data__->GetGlobalStat(pchStatName.utf8().get_data(), &pData);
  });
}

auto /* bool, Type.BOOL */
ISteamUserStats_box::GetGlobalStatd(String /* const char * */ pchStatName) {
  double /* double *, Type.REAL */ pData{};
  return call<bool_box>([&](auto data__) {
    return data__->GetGlobalStat(pchStatName.utf8().get_data(), &pData);
  });
}

void ISteamUserStats_box::_register_methods() {
  register_method("RequestCurrentStats",
                  &ISteamUserStats_box::RequestCurrentStats);
  register_method("GetStati", &ISteamUserStats_box::GetStati);
  register_method("GetStatf", &ISteamUserStats_box::GetStatf);
  register_method("SetStati", &ISteamUserStats_box::SetStati);
  register_method("SetStatf", &ISteamUserStats_box::SetStatf);
  register_method("UpdateAvgRateStat", &ISteamUserStats_box::UpdateAvgRateStat);
  register_method("GetAchievement", &ISteamUserStats_box::GetAchievement);
  register_method("SetAchievement", &ISteamUserStats_box::SetAchievement);
  register_method("ClearAchievement", &ISteamUserStats_box::ClearAchievement);
  register_method("GetAchievementAndUnlockTime",
                  &ISteamUserStats_box::GetAchievementAndUnlockTime);
  register_method("StoreStats", &ISteamUserStats_box::StoreStats);
  register_method("GetAchievementIcon",
                  &ISteamUserStats_box::GetAchievementIcon);
  register_method("GetAchievementDisplayAttribute",
                  &ISteamUserStats_box::GetAchievementDisplayAttribute);
  register_method("IndicateAchievementProgress",
                  &ISteamUserStats_box::IndicateAchievementProgress);
  register_method("GetNumAchievements",
                  &ISteamUserStats_box::GetNumAchievements);
  register_method("GetAchievementName",
                  &ISteamUserStats_box::GetAchievementName);
  register_method("RequestUserStats", &ISteamUserStats_box::RequestUserStats);
  register_method("GetUserStati", &ISteamUserStats_box::GetUserStati);
  register_method("GetUserStatf", &ISteamUserStats_box::GetUserStatf);
  register_method("GetUserAchievement",
                  &ISteamUserStats_box::GetUserAchievement);
  register_method("GetUserAchievementAndUnlockTime",
                  &ISteamUserStats_box::GetUserAchievementAndUnlockTime);
  register_method("ResetAllStats", &ISteamUserStats_box::ResetAllStats);
  register_method("FindOrCreateLeaderboard",
                  &ISteamUserStats_box::FindOrCreateLeaderboard);
  register_method("FindLeaderboard", &ISteamUserStats_box::FindLeaderboard);
  register_method("GetLeaderboardName",
                  &ISteamUserStats_box::GetLeaderboardName);
  register_method("GetLeaderboardEntryCount",
                  &ISteamUserStats_box::GetLeaderboardEntryCount);
  register_method("GetLeaderboardSortMethod",
                  &ISteamUserStats_box::GetLeaderboardSortMethod);
  register_method("GetLeaderboardDisplayType",
                  &ISteamUserStats_box::GetLeaderboardDisplayType);
  register_method("DownloadLeaderboardEntries",
                  &ISteamUserStats_box::DownloadLeaderboardEntries);
  register_method("DownloadLeaderboardEntriesForUsers",
                  &ISteamUserStats_box::DownloadLeaderboardEntriesForUsers);
  register_method("GetDownloadedLeaderboardEntry",
                  &ISteamUserStats_box::GetDownloadedLeaderboardEntry);
  register_method("UploadLeaderboardScore",
                  &ISteamUserStats_box::UploadLeaderboardScore);
  register_method("AttachLeaderboardUGC",
                  &ISteamUserStats_box::AttachLeaderboardUGC);
  register_method("GetNumberOfCurrentPlayers",
                  &ISteamUserStats_box::GetNumberOfCurrentPlayers);
  register_method("RequestGlobalAchievementPercentages",
                  &ISteamUserStats_box::RequestGlobalAchievementPercentages);
  register_method("GetMostAchievedAchievementInfo",
                  &ISteamUserStats_box::GetMostAchievedAchievementInfo);
  register_method("GetNextMostAchievedAchievementInfo",
                  &ISteamUserStats_box::GetNextMostAchievedAchievementInfo);
  register_method("GetAchievementAchievedPercent",
                  &ISteamUserStats_box::GetAchievementAchievedPercent);
  register_method("RequestGlobalStats",
                  &ISteamUserStats_box::RequestGlobalStats);
  register_method("GetGlobalStatl", &ISteamUserStats_box::GetGlobalStatl);
  register_method("GetGlobalStatd", &ISteamUserStats_box::GetGlobalStatd);
}

void ELeaderboardUploadScoreMethod_box::_register_methods() {}
} // namespace godot
#include "post.cpp"
namespace godot {

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
  godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT
godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
  godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
  godot::Godot::nativescript_init(handle);

  godot::register_class<godot::SteamAPI_box>();
  godot::register_class<godot::EUniverse_box>();
  godot::register_class<godot::AccountID_t_box>();
  godot::register_class<godot::bool_box>();
  godot::register_class<godot::EAccountType_box>();
  godot::register_class<godot::ENotificationPosition_box>();
  godot::register_class<godot::int_const_pointer_box>();
  godot::register_class<godot::ESteamAPICallFailure_box>();
  godot::register_class<godot::bool_pointer_box>();
  godot::register_class<godot::ELeaderboardDataRequest_box>();
  godot::register_class<godot::ESteamIPv6ConnectivityState_box>();
  godot::register_class<godot::CSteamID_pointer_box>();
  godot::register_class<godot::uint64_box>();
  godot::register_class<godot::ELeaderboardDisplayType_box>();
  godot::register_class<godot::unsigned_longlong_box>();
  godot::register_class<godot::unsigned_char_pointer_box>();
  godot::register_class<godot::LeaderboardEntry_t_pointer_box>();
  godot::register_class<godot::int_pointer_box>();
  godot::register_class<godot::ELeaderboardSortMethod_box>();
  godot::register_class<godot::char_const_pointer_box>();
  godot::register_class<godot::ISteamUtils_box>();
  godot::register_class<godot::float_box>();
  godot::register_class<godot::uint8_box>();
  godot::register_class<godot::float_pointer_box>();
  godot::register_class<godot::ESteamIPv6ConnectivityProtocol_box>();
  godot::register_class<godot::longlong_pointer_box>();
  godot::register_class<godot::uint32_box>();
  godot::register_class<godot::char_pointer_box>();
  godot::register_class<godot::ETextFilteringContext_box>();
  godot::register_class<godot::double_box>();
  godot::register_class<godot::EFloatingGamepadTextInputMode_box>();
  godot::register_class<godot::EGamepadTextInputLineMode_box>();
  godot::register_class<godot::EGamepadTextInputMode_box>();
  godot::register_class<godot::double_pointer_box>();
  godot::register_class<godot::unsigned_int_pointer_box>();
  godot::register_class<godot::CSteamID_box>();
  godot::register_class<godot::unsigned_int_box>();
  godot::register_class<godot::int_box>();
  godot::register_class<godot::ISteamUserStats_box>();
  godot::register_class<godot::ELeaderboardUploadScoreMethod_box>();
  godot::register_class<godot::SteamAPICall_t_box>();
}

} // namespace godot
