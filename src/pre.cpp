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

template<typename box_type, typename cpp_type>
auto cast(cpp_type const& st)
{
    if constexpr (std::is_integral_v<cpp_type>)
    {
        return static_cast<int>(st);
    }
    else if constexpr (std::is_same_v<bool, cpp_type>)
    {
        return st;
    }
    else if constexpr (std::is_same_v<const char*, cpp_type>)
    {
        return String{st};
    }
    else if constexpr (std::is_same_v<void, cpp_type>)
    {
        return;
    }
    else if constexpr (std::is_enum_v<cpp_type>)
    {
        return static_cast<int>(st);
    }
    else
    {
        return box_type::make(st);
    }

    //else return godot_type::make(st);
    /*
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
    */
}


template<typename T, typename TT>
class SteamBase : public Reference
{
public:
    using value_type = typename 
        std::conditional_t<std::is_reference_v<T>, std::remove_const<std::remove_reference_t<T>>,
            std::conditional_t<std::is_arithmetic_v<T>, T,
                std::conditional_t<std::is_abstract_v<T>, std::remove_reference_t<T>*, 
                    T>>>;

    value_type value;

    using cpp_type = T;
    using godot_type = TT;

    template<typename value_type>
    static auto make(value_type const& t)
    {
        auto res = Ref{TT::_new()};

        if constexpr(std::is_array_v<value_type>)
        {
            std::copy(std::begin(t), std::end(t), std::begin(res->value));
        }
        else 
        {
            res->value = t;
        }

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
    
    template<typename box_type, typename Op>
    auto call(Op op)
    {
        using return_type = decltype(op(get_ptr()));
    
        if constexpr(std::is_pointer_v<value_type>)
        {
            if(value == nullptr)
            {
                if constexpr(std::is_void_v<return_type>)
                {
                    return;
                }
                else
                {
                    return cast<box_type>(return_type{});
                }
            }
        }

        if constexpr(std::is_void_v<return_type>)
        {
            op(get_ptr());
        }
        else 
        {
            return cast<box_type>(op(get_ptr()));
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

class SteamAPICall_t_box : public Reference
{
    GODOT_CLASS(SteamAPICall_t_box, Reference)

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
        SteamAPICall_t_box* parent{};

        steam_callback(SteamAPICall_t_box* parent_) : parent{parent_}
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
        static std::set<Ref<SteamAPICall_t_box>> set;
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
        register_signal<SteamAPICall_t_box>("done", {});
    }

    void _init()
    {
    }

    template<typename steam_type, typename emit_type>
    static auto make(SteamAPICall_t steam_api_call)
    {
        auto res = Ref{SteamAPICall_t_box::_new()};
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
