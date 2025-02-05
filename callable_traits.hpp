#ifndef NDOF_CALLABLE_DEFINITIONS_HPP
#define NDOF_CALLABLE_DEFINITIONS_HPP
// Example at the bottom.

// Bit of a rework.
// https://godbolt.org/z/veKj617d1

#include "ndof/details/callable_argument_helper.hpp"
#include "ndof/details/callable_qualifiers.hpp"
#include "ndof/details/callable_concepts.hpp"

#include <type_traits>
#include <tuple>
#include <cstdint>
#include <functional>

// TODO: Create custom msvc warning. https://stackoverflow.com/questions/11819240/how-to-write-compile-time-warning-for-user

// TODO: Create qualifier for signature with va_list as last argument.
// TODO: Consider variadic cases where only the first parameters match.   

namespace ndof {
    // Playground: https://godbolt.org/z/MW79Mnsr9



    template<typename R, typename ...A>
    struct CommonCallableTraits {
        using ReturnType   = R;
        using ClassType    = void;   
        using ArgTypes     = ArgumentHelper<A...>;
        using TupleType    = std::tuple<A...>;
        using CombinedType = ArgumentHelper<R,A...>;
        constexpr static std::size_t argument_count = sizeof...(A);
    };

    template<typename R, typename C, typename ...A>
    struct MemFunPtrTraits : CommonCallableTraits<R, A...> {
        using ClassType = C;
    };

    template<typename R, typename ...A>
    struct FunTraits : CommonCallableTraits<R, A...> {
    };

    template<typename R, typename ...A>
    struct FunPtrTraits : CommonCallableTraits<R, A...> {
    };

    template<typename F>
    struct CallableTraits{
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A...)> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers = 
            Qualifier::Unqualified;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A...) const> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers = 
            Qualifier::Const;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A...) volatile> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers = 
            Qualifier::Volatile;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A...) const volatile> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers = 
            Qualifier::Const     | 
            Qualifier::Volatile;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A...) &> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers = 
            Qualifier::LValueRef;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A...) const &> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const      | 
            Qualifier::LValueRef;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A...) volatile &> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile   | 
            Qualifier::LValueRef;    
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A...) const volatile &> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers = 
            Qualifier::Const      | 
            Qualifier::Volatile   | 
            Qualifier::LValueRef;
    };
    
    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A...) &&> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::RValueRef;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A...) const &&> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const      | 
            Qualifier::RValueRef;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A...) volatile &&> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile   | 
            Qualifier::RValueRef;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A...) const volatile &&> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const      | 
            Qualifier::Volatile   | 
            Qualifier::RValueRef;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A...) noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::NoExcept;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A...) const noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const     | 
            Qualifier::NoExcept;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A...) volatile noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile  | 
            Qualifier::NoExcept;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A...) const volatile noexcept> : MemFunPtrTraits<R,C,A...> { 
        constexpr static Qualifier qualifiers =
            Qualifier::Const     | 
            Qualifier::Volatile  | 
            Qualifier::NoExcept;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A...) & noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::LValueRef | 
            Qualifier::NoExcept;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A...) const & noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const     | 
            Qualifier::LValueRef | 
            Qualifier::NoExcept;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A...) volatile & noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =        
            Qualifier::Volatile  | 
            Qualifier::LValueRef | 
            Qualifier::NoExcept;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A...) const volatile & noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const     | 
            Qualifier::Volatile  | 
            Qualifier::LValueRef | 
            Qualifier::NoExcept;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A...) && noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::RValueRef |
            Qualifier::NoExcept;
    };


    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A...) const && noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const     | 
            Qualifier::RValueRef | 
            Qualifier::NoExcept;
    };


    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A...) volatile && noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile  | 
            Qualifier::RValueRef | 
            Qualifier::NoExcept;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A...) const volatile && noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const     | 
            Qualifier::Volatile  | 
            Qualifier::RValueRef | 
            Qualifier::NoExcept;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A..., ...)> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers = 
            Qualifier::Variadic;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A..., ...) const> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const     |
            Qualifier::Variadic;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A..., ...) volatile> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile  |
            Qualifier::Variadic;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A..., ...) const volatile> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const     | 
            Qualifier::Volatile  | 
            Qualifier::Variadic;  
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A..., ...) &> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::LValueRef | 
            Qualifier::Variadic;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A..., ...) const &> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const     | 
            Qualifier::LValueRef | 
            Qualifier::Variadic;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A..., ...) volatile &> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile  | 
            Qualifier::LValueRef | 
            Qualifier::Variadic;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A..., ...) const volatile &> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const     | 
            Qualifier::Volatile  | 
            Qualifier::LValueRef | 
            Qualifier::Variadic;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A..., ...) &&> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::RValueRef | 
            Qualifier::Variadic;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A..., ...) const &&> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const     | 
            Qualifier::RValueRef | 
            Qualifier::Variadic;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A..., ...) volatile &&> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile  | 
            Qualifier::RValueRef | 
            Qualifier::Variadic;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A..., ...) const volatile &&> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const     | 
            Qualifier::Volatile  | 
            Qualifier::RValueRef | 
            Qualifier::Variadic;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A..., ...) noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::NoExcept  | 
            Qualifier::Variadic;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A..., ...) const noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const     | 
            Qualifier::NoExcept  | 
            Qualifier::Variadic;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A..., ...) volatile noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile  | 
            Qualifier::NoExcept  | 
            Qualifier::Variadic;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A..., ...) const volatile noexcept> : MemFunPtrTraits<R,C,A...> { 
        constexpr static Qualifier qualifiers =
            Qualifier::Const     | 
            Qualifier::Volatile  | 
            Qualifier::NoExcept  | 
            Qualifier::Variadic;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A..., ...) & noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::LValueRef | 
            Qualifier::NoExcept  | 
            Qualifier::Variadic;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A..., ...) const & noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const     | 
            Qualifier::LValueRef | 
            Qualifier::NoExcept  | 
            Qualifier::Variadic;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A..., ...) volatile & noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile  | 
            Qualifier::LValueRef | 
            Qualifier::NoExcept  | 
            Qualifier::Variadic;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A..., ...) const volatile & noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const     | 
            Qualifier::Volatile  | 
            Qualifier::LValueRef | 
            Qualifier::NoExcept  | 
            Qualifier::Variadic;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A..., ...) && noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::RValueRef | 
            Qualifier::NoExcept  | 
            Qualifier::Variadic;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A..., ...) const && noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const     | 
            Qualifier::NoExcept  | 
            Qualifier::Variadic; 
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*)(A..., ...) const volatile && noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const     | 
            Qualifier::Volatile  | 
            Qualifier::RValueRef | 
            Qualifier::NoExcept  | 
            Qualifier::Variadic; 
    };
    // -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A...)> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers = 
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A...) const> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers = 
            Qualifier::Const      |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A...) volatile> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers = 
            Qualifier::Volatile   |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A...) const volatile> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers = 
            Qualifier::Const      |
            Qualifier::Volatile   |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A...) &> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers = 
            Qualifier::LValueRef  | 
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A...) const &> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const      |
            Qualifier::LValueRef  |
            Qualifier::Const_Ptr;
    };
    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A...) volatile &> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile   | 
            Qualifier::LValueRef  |
            Qualifier::Const_Ptr;    
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A...) const volatile &> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers = 
            Qualifier::Volatile   | 
            Qualifier::LValueRef  |
            Qualifier::Const      | 
            Qualifier::Const_Ptr;
    };
    
    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A...) &&> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::RValueRef  |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A...) const &&> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::RValueRef  |
            Qualifier::Const      | 
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A...) volatile &&> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::RValueRef  |
            Qualifier::Volatile   | 
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A...) const volatile &&> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const      | 
            Qualifier::Volatile   | 
            Qualifier::RValueRef  |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A...) noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::NoExcept   |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A...) const noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const      | 
            Qualifier::NoExcept   |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A...) volatile noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile   | 
            Qualifier::NoExcept   |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A...) const volatile noexcept> : MemFunPtrTraits<R,C,A...> { 
        constexpr static Qualifier qualifiers =
            Qualifier::Const      | 
            Qualifier::Volatile   | 
            Qualifier::NoExcept   |
            Qualifier::Const_Ptr;
    };
    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A...) & noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::LValueRef  |
            Qualifier::NoExcept   |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A...) const & noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const      |
            Qualifier::LValueRef  |
            Qualifier::NoExcept   |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A...) volatile & noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile   |
            Qualifier::LValueRef  |
            Qualifier::NoExcept   |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A...) const volatile & noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const      |
            Qualifier::Volatile   |
            Qualifier::LValueRef  |
            Qualifier::NoExcept   |
            Qualifier::Const_Ptr;
    };
    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A...) && noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::RValueRef  | 
            Qualifier::NoExcept   |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A...) const && noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const      | 
            Qualifier::RValueRef  | 
            Qualifier::NoExcept   |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A...) volatile && noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile   | 
            Qualifier::RValueRef  | 
            Qualifier::NoExcept   |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A...) const volatile && noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const      | 
            Qualifier::Volatile   | 
            Qualifier::RValueRef  | 
            Qualifier::NoExcept   |
            Qualifier::Const_Ptr;
    };
    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A..., ...)> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers = 
            Qualifier::Variadic   |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A..., ...) const> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Variadic  |
            Qualifier::Const     |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A..., ...) volatile> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Variadic   |
            Qualifier::Volatile   |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A..., ...) const volatile> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Variadic   |
            Qualifier::Const      | 
            Qualifier::Volatile   | 
            Qualifier::Const_Ptr;  
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A..., ...) &> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Variadic   |
            Qualifier::LValueRef  |  
            Qualifier::Const_Ptr;
    };
    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A..., ...) const &> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const      | 
            Qualifier::LValueRef  | 
            Qualifier::Variadic   |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A..., ...) volatile &> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile   | 
            Qualifier::LValueRef  | 
            Qualifier::Variadic   |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A..., ...) const volatile &> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const      | 
            Qualifier::Volatile   | 
            Qualifier::LValueRef  | 
            Qualifier::Variadic   |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A..., ...) &&> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::RValueRef  | 
            Qualifier::Variadic   |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A..., ...) const &&> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const      | 
            Qualifier::RValueRef  | 
            Qualifier::Variadic   |
            Qualifier::Const_Ptr;
    };
    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A..., ...) volatile &&> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile   | 
            Qualifier::RValueRef  | 
            Qualifier::Variadic   |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A..., ...) const volatile &&> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const      | 
            Qualifier::Volatile   | 
            Qualifier::RValueRef  | 
            Qualifier::Variadic   |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A..., ...) noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::NoExcept   | 
            Qualifier::Variadic   |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A..., ...) const noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const      | 
            Qualifier::NoExcept   | 
            Qualifier::Variadic   |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A..., ...) volatile noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile   | 
            Qualifier::NoExcept   | 
            Qualifier::Variadic   |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A..., ...) const volatile noexcept> : MemFunPtrTraits<R,C,A...> { 
        constexpr static Qualifier qualifiers =
            Qualifier::Const      | 
            Qualifier::Volatile   | 
            Qualifier::NoExcept   | 
            Qualifier::Variadic   |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A..., ...) & noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::LValueRef  | 
            Qualifier::NoExcept   | 
            Qualifier::Variadic   |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A..., ...) const & noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const      | 
            Qualifier::LValueRef  | 
            Qualifier::NoExcept   | 
            Qualifier::Variadic   |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A..., ...) volatile & noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile   | 
            Qualifier::LValueRef  | 
            Qualifier::NoExcept   | 
            Qualifier::Variadic   |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A..., ...) const volatile & noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const      | 
            Qualifier::Volatile   | 
            Qualifier::LValueRef  | 
            Qualifier::NoExcept   | 
            Qualifier::Variadic   |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A..., ...) && noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::RValueRef  | 
            Qualifier::NoExcept   | 
            Qualifier::Variadic   |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A..., ...) const && noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const      |  
            Qualifier::RValueRef  | 
            Qualifier::NoExcept   | 
            Qualifier::Variadic   |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A..., ...) volatile && noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile   | 
            Qualifier::RValueRef  | 
            Qualifier::NoExcept   | 
            Qualifier::Variadic   |
            Qualifier::Const_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*const)(A..., ...) const volatile && noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const      | 
            Qualifier::Volatile   | 
            Qualifier::RValueRef  | 
            Qualifier::NoExcept   | 
            Qualifier::Variadic   |
            Qualifier::Const_Ptr;
    };

    // -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A...)> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers = 
            Qualifier::Volatile_Ptr;
    };
    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A...) const> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers = 
            Qualifier::Const         |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A...) volatile> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers = 
            Qualifier::Volatile      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A...) const volatile> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers = 
            Qualifier::Const         | 
            Qualifier::Volatile      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A...) &> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers = 
            Qualifier::LValueRef     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A...) const &> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         | 
            Qualifier::LValueRef     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A...) volatile &> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile      |
            Qualifier::LValueRef     |
            Qualifier::Volatile_Ptr;    
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A...) const volatile &> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers = 
            Qualifier::Const         | 
            Qualifier::Volatile      | 
            Qualifier::LValueRef     |
            Qualifier::Volatile_Ptr;
    };
    
    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A...) &&> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::RValueRef     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A...) const &&> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         | 
            Qualifier::RValueRef     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A...) volatile &&> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile      | 
            Qualifier::RValueRef     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A...) const volatile &&> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         | 
            Qualifier::Volatile      | 
            Qualifier::RValueRef     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A...) noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::NoExcept      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A...) const noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         | 
            Qualifier::NoExcept      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A...) volatile noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile      | 
            Qualifier::NoExcept      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A...) const volatile noexcept> : MemFunPtrTraits<R,C,A...> { 
        constexpr static Qualifier qualifiers =
            Qualifier::Const         | 
            Qualifier::Volatile      | 
            Qualifier::NoExcept      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A...) & noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::LValueRef     | 
            Qualifier::NoExcept      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A...) const & noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         | 
            Qualifier::LValueRef     | 
            Qualifier::NoExcept      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A...) volatile & noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =        
            Qualifier::Volatile      | 
            Qualifier::LValueRef     | 
            Qualifier::NoExcept      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A...) const volatile & noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         | 
            Qualifier::Volatile      | 
            Qualifier::LValueRef     | 
            Qualifier::NoExcept      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A...) && noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::RValueRef     | 
            Qualifier::NoExcept      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A...) const && noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         | 
            Qualifier::RValueRef     | 
            Qualifier::NoExcept      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A...) volatile && noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile      | 
            Qualifier::RValueRef     | 
            Qualifier::NoExcept      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A...) const volatile && noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         | 
            Qualifier::Volatile      | 
            Qualifier::RValueRef     | 
            Qualifier::NoExcept      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A..., ...)> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers = 
            Qualifier::Variadic      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A..., ...) const> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         |
            Qualifier::Variadic      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A..., ...) volatile> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile      |
            Qualifier::Variadic      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A..., ...) const volatile> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         | 
            Qualifier::Volatile      | 
            Qualifier::Variadic      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A..., ...) &> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::LValueRef     | 
            Qualifier::Variadic      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A..., ...) const &> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         | 
            Qualifier::LValueRef     | 
            Qualifier::Variadic      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A..., ...) volatile &> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile      | 
            Qualifier::LValueRef     | 
            Qualifier::Variadic      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A..., ...) const volatile &> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         | 
            Qualifier::Volatile      | 
            Qualifier::LValueRef     | 
            Qualifier::Variadic      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A..., ...) &&> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::RValueRef     | 
            Qualifier::Variadic      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A..., ...) const &&> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         | 
            Qualifier::RValueRef     | 
            Qualifier::Variadic      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A..., ...) volatile &&> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile      | 
            Qualifier::RValueRef     | 
            Qualifier::Variadic      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A..., ...) const volatile &&> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         | 
            Qualifier::Volatile      | 
            Qualifier::RValueRef     | 
            Qualifier::Variadic      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A..., ...) noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::NoExcept      | 
            Qualifier::Variadic      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A..., ...) const noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         | 
            Qualifier::NoExcept      | 
            Qualifier::Variadic      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A..., ...) volatile noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile      | 
            Qualifier::NoExcept      | 
            Qualifier::Variadic      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A..., ...) const volatile noexcept> : MemFunPtrTraits<R,C,A...> { 
        constexpr static Qualifier qualifiers =
            Qualifier::Const         | 
            Qualifier::Volatile      | 
            Qualifier::NoExcept      | 
            Qualifier::Variadic      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A..., ...) & noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::LValueRef     | 
            Qualifier::NoExcept      | 
            Qualifier::Variadic      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A..., ...) const & noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         | 
            Qualifier::LValueRef     | 
            Qualifier::NoExcept      | 
            Qualifier::Variadic      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A..., ...) volatile & noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile      | 
            Qualifier::LValueRef     | 
            Qualifier::NoExcept      | 
            Qualifier::Variadic      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A..., ...) const volatile & noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         | 
            Qualifier::Volatile      | 
            Qualifier::LValueRef     | 
            Qualifier::NoExcept      | 
            Qualifier::Variadic      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A..., ...) && noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::RValueRef     | 
            Qualifier::NoExcept      | 
            Qualifier::Variadic      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A..., ...) const && noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         | 
            Qualifier::RValueRef     | 
            Qualifier::NoExcept      | 
            Qualifier::Variadic      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A..., ...) volatile && noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile_Ptr  |
            Qualifier::Volatile      | 
            Qualifier::RValueRef     | 
            Qualifier::NoExcept      | 
            Qualifier::Variadic      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::*volatile)(A..., ...) const volatile && noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =

            Qualifier::Const         | 
            Qualifier::Volatile      | 
            Qualifier::RValueRef     | 
            Qualifier::NoExcept      | 
            Qualifier::Variadic      |
            Qualifier::Volatile_Ptr;
    };
    
    // -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A...)> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers = 
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A...) const> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers = 
            Qualifier::Const         |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A...) volatile> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers = 
            Qualifier::Volatile      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;

    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A...) const volatile> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers = 
            Qualifier::Const         | 
            Qualifier::Volatile      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A...) &> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers = 
            Qualifier::LValueRef     |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };;

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A...) const &> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr  |
            Qualifier::Const         | 
            Qualifier::LValueRef;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A...) volatile &> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr  |
            Qualifier::Volatile      | 
            Qualifier::LValueRef;    
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A...) const volatile &> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers = 
            Qualifier::Const         | 
            Qualifier::Volatile      | 
            Qualifier::LValueRef     |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };
    
    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A...) &&> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::RValueRef     |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };;

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A...) const &&> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         | 
            Qualifier::RValueRef     |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A...) volatile &&> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile      | 
            Qualifier::RValueRef     |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A...) const volatile &&> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         | 
            Qualifier::Volatile      | 
            Qualifier::RValueRef     |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A...) noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::NoExcept      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };;

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A...) const noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         | 
            Qualifier::NoExcept      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };;

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A...) volatile noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile      | 
            Qualifier::NoExcept      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };;

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A...) const volatile noexcept> : MemFunPtrTraits<R,C,A...> { 
        constexpr static Qualifier qualifiers =
            Qualifier::Const         |
            Qualifier::Volatile      |
            Qualifier::NoExcept      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A...) & noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::LValueRef     |
            Qualifier::NoExcept      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };;

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A...) const & noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         |
            Qualifier::LValueRef     |
            Qualifier::NoExcept      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A...) volatile & noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =     
            Qualifier::Volatile      | 
            Qualifier::LValueRef     | 
            Qualifier::NoExcept      |
            Qualifier::Const_Ptr     |   
            Qualifier::Volatile_Ptr;
    };;

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A...) const volatile & noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         |
            Qualifier::Volatile      |
            Qualifier::LValueRef     |
            Qualifier::NoExcept      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A...) && noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::RValueRef     |
            Qualifier::NoExcept      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A...) const && noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         |
            Qualifier::RValueRef     |
            Qualifier::NoExcept      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A...) const volatile && noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         |
            Qualifier::Volatile      |
            Qualifier::RValueRef     |
            Qualifier::NoExcept      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A..., ...)> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers = 
            Qualifier::Variadic      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };;

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A..., ...) const> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         |
            Qualifier::Variadic      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A..., ...) volatile> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile      |
            Qualifier::Variadic      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };;

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A..., ...) const volatile> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         | 
            Qualifier::Volatile      | 
            Qualifier::Variadic      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A..., ...) &> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::LValueRef     |
            Qualifier::Variadic      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };;

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A..., ...) const &> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         | 
            Qualifier::LValueRef     | 
            Qualifier::Variadic      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A..., ...) volatile &> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile      |
            Qualifier::LValueRef     |
            Qualifier::Variadic      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A..., ...) const volatile &> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         | 
            Qualifier::Volatile      | 
            Qualifier::LValueRef     | 
            Qualifier::Variadic      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A..., ...) &&> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::RValueRef     | 
            Qualifier::Variadic      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };;

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A..., ...) const &&> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         | 
            Qualifier::RValueRef     | 
            Qualifier::Variadic      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A..., ...) volatile &&> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile      | 
            Qualifier::RValueRef     | 
            Qualifier::Variadic      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A..., ...) const volatile &&> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         | 
            Qualifier::Volatile      | 
            Qualifier::RValueRef     | 
            Qualifier::Variadic      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A..., ...) noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::NoExcept      | 
            Qualifier::Variadic      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };;

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A..., ...) const noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         | 
            Qualifier::NoExcept      | 
            Qualifier::Variadic      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };;

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A..., ...) volatile noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile      | 
            Qualifier::NoExcept      | 
            Qualifier::Variadic      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };;

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A..., ...) const volatile noexcept> : MemFunPtrTraits<R,C,A...> { 
        constexpr static Qualifier qualifiers =
            Qualifier::Const         | 
            Qualifier::Volatile      | 
            Qualifier::NoExcept      | 
            Qualifier::Variadic      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A..., ...) & noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::LValueRef     |
            Qualifier::NoExcept      |
            Qualifier::Variadic      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };;

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A..., ...) const & noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         | 
            Qualifier::LValueRef     | 
            Qualifier::NoExcept      | 
            Qualifier::Variadic      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };;

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A..., ...) volatile & noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile      | 
            Qualifier::LValueRef     | 
            Qualifier::NoExcept      | 
            Qualifier::Variadic      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A..., ...) const volatile & noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         | 
            Qualifier::Volatile      | 
            Qualifier::LValueRef     | 
            Qualifier::NoExcept      | 
            Qualifier::Variadic      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A..., ...) && noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::RValueRef     |
            Qualifier::NoExcept      |
            Qualifier::Variadic      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A..., ...) const && noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         | 
            Qualifier::RValueRef     | 
            Qualifier::NoExcept      | 
            Qualifier::Variadic      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A..., ...) volatile && noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile      | 
            Qualifier::RValueRef     | 
            Qualifier::NoExcept      | 
            Qualifier::Variadic      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename C, typename ...A>
    struct CallableTraits<R(C::* const volatile)(A..., ...) const volatile && noexcept> : MemFunPtrTraits<R,C,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const         | 
            Qualifier::Volatile      | 
            Qualifier::RValueRef     | 
            Qualifier::NoExcept      | 
            Qualifier::Variadic      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };

    // -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    template<typename R, typename ...A>
    struct CallableTraits<R(A...)> : FunTraits<R,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Unqualified;
    };

    template<typename R, typename ...A>
    struct CallableTraits<R(A...,...)> : FunTraits<R,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Variadic;
    };

    template<typename R, typename ...A>
    struct CallableTraits<R(A...) noexcept>  : FunTraits<R,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::NoExcept;
    };

    template<typename R,  typename ...A>
    struct CallableTraits<R(A..., ...) noexcept> : FunTraits<R,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::NoExcept  | 
            Qualifier::Variadic;
    };

    // -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    template<typename R, typename ...A>
    struct CallableTraits<R(*)(A...)> : FunPtrTraits<R,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Unqualified;
    };

    template<typename R, typename ...A>
    struct CallableTraits<R(*)(A..., ...)> : FunPtrTraits<R,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Variadic;
    };

    template<typename R, typename ...A>
    struct CallableTraits<R(*)(A...) noexcept>  : FunPtrTraits<R,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::NoExcept;
    };

    template<typename R,  typename ...A>
    struct CallableTraits<R(*)(A..., ...) noexcept> : FunPtrTraits<R,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::NoExcept      | 
            Qualifier::Variadic;
    };

    template<typename R, typename ...A>
    struct CallableTraits<R(*const)(A...)> : FunPtrTraits<R,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const_Ptr;
    };

    template<typename R, typename ...A>
    struct CallableTraits<R(*const)(A..., ...)> : FunPtrTraits<R,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Variadic   |     
            Qualifier::Const_Ptr;
    };

    template<typename R, typename ...A>
    struct CallableTraits<R(*const)(A...) noexcept>  : FunPtrTraits<R,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::NoExcept     |
            Qualifier::Const_Ptr;
    };

    template<typename R,  typename ...A>
    struct CallableTraits<R(*const)(A..., ...) noexcept> : FunPtrTraits<R,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::NoExcept     |
            Qualifier::Variadic     |
            Qualifier::Const_Ptr;
    };
    
    template<typename R, typename ...A>
    struct CallableTraits<R(*volatile)(A...)> : FunPtrTraits<R,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename ...A>
    struct CallableTraits<R(*volatile)(A..., ...)> : FunPtrTraits<R,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Variadic      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename ...A>
    struct CallableTraits<R(*volatile)(A...) noexcept>  : FunPtrTraits<R,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::NoExcept      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R,  typename ...A>
    struct CallableTraits<R(*volatile)(A..., ...) noexcept> : FunPtrTraits<R,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::NoExcept      |
            Qualifier::Variadic      |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename ...A>
    struct CallableTraits<R(*const volatile)(A...)> : FunPtrTraits<R,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename ...A>
    struct CallableTraits<R(* const volatile)(A..., ...)> : FunPtrTraits<R,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::Variadic      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R, typename ...A>
    struct CallableTraits<R(* const volatile)(A...) noexcept>  : FunPtrTraits<R,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::NoExcept      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };

    template<typename R,  typename ...A>
    struct CallableTraits<R(* const volatile)(A..., ...) noexcept> : FunPtrTraits<R,A...> {
        constexpr static Qualifier qualifiers =
            Qualifier::NoExcept      |
            Qualifier::Variadic      |
            Qualifier::Const_Ptr     |
            Qualifier::Volatile_Ptr;
    };
    // -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    template<Functor F>
    struct CallableTraits<F> : CallableTraits<decltype(&F::operator())>{
        // Do nothing.
    };

    template<typename F, typename R>
    concept Returns = std::is_same_v<typename CallableTraits<F>::ReturnType, R>;

    template<typename F, typename ...A>
    concept HasArgumentTypes = Callable<F> && std::is_same_v<typename CallableTraits<F>::ArgTypes, ArgumentHelper<A...>>;

    template<typename F>
    concept IsVoidReturn = std::is_same_v<typename CallableTraits<F>::ReturnType, void>;

    template<typename F>
    concept VoidCallable = 
        Callable<F> 
        && IsVoidReturn<F> 
        && HasArgumentTypes<F>;

    
    using VoidStdFn = std::function<void()>;

    
}

#endif