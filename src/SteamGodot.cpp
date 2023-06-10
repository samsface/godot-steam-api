#include <Godot.hpp>
#include <Node.hpp>
#include <steam/steam_api.h>
#include <steam/isteamgameserverstats.h>
#include <steam/isteamgameserver.h>
#include <steam/steam_gameserver.h>
#include <memory>
#include <type_traits>
#include <vector>
#include <functional>
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

template<typename godot_type>
auto to_steam(godot_type& t)
{
    return t;
/*
    using underlying_type = typename std::remove_pointer_t<typename std::remove_reference_t<godot_type>>;

    if constexpr (std::is_same_v<underlying_type, String>)
    {
        return t.utf8().get_data();
    }
    else if constexpr (std::is_enum_v<underlying_type>) 
    {
        return t;
    }
    else if constexpr (std::is_arithmetic_v<underlying_type>) 
    {
        return t;
    }
    else if constexpr (std::is_same_v<underlying_type, bool>) 
    {
        return t;
    }
    else
    {
        return t;
    }
    */
}

template<typename godot_type, typename steam_type>
auto cast(steam_type const& st)
{
    if constexpr (std::is_enum<steam_type>::value)
    {
        return static_cast<int>(st);
    }
    else if constexpr (std::is_array<steam_type>::value)
    {
        return Array();
    }
    else if constexpr (std::is_same_v<steam_type, const char*>)
    {
        return String(st);
    }
    else if constexpr (std::is_invocable_v<steam_type>)
    {
        return 0;
    }
    else if constexpr (std::is_integral<godot_type>::value) 
    {
        return static_cast<int>(st);
    }
    else if constexpr (std::is_floating_point<godot_type>::value) 
    {
        return static_cast<float>(st);
    }
    else if constexpr (std::is_same_v<steam_type, void*>) 
    {
        return 0;
    }
    else if constexpr (std::is_same_v<steam_type, bool>) 
    {
        return st;
    }
    else if constexpr (std::is_same_v<steam_type, CGameID>)
    {
        return static_cast<int>(st.m_ulGameID);
    }
    else
    {
        return godot_type::make(st);
    }
}


template<typename T, typename TT>
class SteamBase : public Reference
{
public:
    using value_type = typename 
        std::conditional_t<std::is_reference_v<T>, std::remove_reference_t<T>,
            std::conditional_t<std::is_arithmetic_v<T>, T,
                std::conditional_t<std::is_abstract_v<T>, std::remove_reference_t<T>*, 
                    T>>>;

    value_type value;

    template<typename value_type>
    static auto make(value_type const& t)
    {
        auto res = Ref{TT::_new()};
        res->value = t;
        return res;
    }

    auto get_ptr()
    {
        if constexpr(std::is_pointer_v<value_type>)
        {
            return get();
        }
        else 
        {
            return &value;
        }
    }

    auto get_ptr() const
    {
        if constexpr(std::is_pointer_v<value_type>)
        {
            return get();
        }
        else 
        {
            return &value;
        }
    }

    auto& get()
    {
        return value;
    }

    auto& get() const
    {
        return value;
    }
    

    template<typename return_type, typename Op, typename ...Args>
    auto call(Op op, Args&& ...args)
    {
        using steam_return_type = decltype(op(get_ptr(), args...));

        if constexpr (std::is_void_v<steam_return_type>)
        {
            op(get_ptr(), args...);
        }
        else if constexpr (std::is_const_v<steam_return_type>)
        {
            op(get_ptr(), args...);
        }
        else
        {
            cast<return_type>(op(get_ptr(), args...));
        }
    }

    template<typename return_type, typename Op, typename ...Args>
    auto call(Op op, Args&& ...args) const
    {
        using steam_return_type = decltype(op(get_ptr(), args...));

        if constexpr (std::is_void_v<steam_return_type>)
        {
            op(get_ptr(), args...);
        }
        else if constexpr (std::is_const_v<steam_return_type>)
        {
            op(get_ptr(), args...);
        }
        else
        {
            cast<return_type>(op(get_ptr(), args...));
        }
    }
};

class void_box
    : public SteamBase<void*, void_box> {
  GODOT_CLASS(void_box, Reference)
public:
  static void _register_methods();
  void _init() {}
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

template<typename godot_type, typename steam_type>
auto make_array(steam_type data[], std::size_t size)
{
    if constexpr (std::is_same_v<godot_type, char>) 
    {
        String res;
        for(std::size_t i = 0; i < size; i++)
        {
            res += data[i];
        }

        return res;
    }
    else 
    {
        Array res;
        for(std::size_t i = 0; i < size; i++)
        {
            if constexpr(std::is_arithmetic<godot_type>::value)
            {
                res.push_back(data[i]);
            }
            else
            {
                res.push_back(godot_type::make(data[i]));
            }
        }

        return res;
    }
}
}

struct SteamDatagramHostedAddress{};
struct SteamDatagramGameCoordinatorServerLogin{};
struct ModalGamepadTextInputDismissed_t{};
struct SteamDatagramRelayAuthTicket{};
struct ISteamNetworkingConnectionSignaling{};
struct ISteamNetworkingSignalingRecvContext{};