#ifndef NDOF_FUNCTION_QUALIFIERS_HPP
#define NDOF_FUNCTION_QUALIFIERS_HPP

#include <cstdint>
#include <type_traits>
#include <concepts>

namespace ndof {
    using underlying_qualifier_t = std::uint32_t;
 
    enum class Qualifier : underlying_qualifier_t { 
        Undefined    =   0,
        Unqualified  =   1,
        Const        =   2,
        Volatile     =   4,
        LValueRef    =   8,
        RValueRef    =  16,
        NoExcept     =  32,
        Variadic     =  64,
        Const_Ptr    = 128,
        Volatile_Ptr = 256
    };

    constexpr Qualifier operator | (Qualifier _1st, Qualifier _2nd) {
        using T = std::underlying_type_t<Qualifier>;
        return static_cast<Qualifier>(static_cast<T>(_1st) | static_cast<T>(_2nd));
    }

    constexpr Qualifier operator & (const Qualifier& _1st, const Qualifier& _2nd) {
        using T = std::underlying_type_t<Qualifier>;
        return static_cast<Qualifier>(static_cast<T>(_1st) & static_cast<T>(_2nd));
    }

    constexpr Qualifier operator ^ (Qualifier _1st, Qualifier _2nd) {
        using T = std::underlying_type_t<Qualifier>;
        return static_cast<Qualifier>(static_cast<T>(_1st) ^ static_cast<T>(_2nd));
    } 
}

#endif

 