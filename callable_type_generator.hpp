#ifndef NDOF_FUNCTION_TYPE_GENERATOR_HPP
#define NDOF_FUNCTION_TYPE_GENERATOR_HPP

#include "ndof/details/callable_argument_helper.hpp"
#include "ndof/details/callable_concepts.hpp"
#include "ndof/details/callable_qualifiers.hpp"

#include <concepts>
#include <type_traits>
// TODO: [p3] use add_const, add_volatile, add_cv to reduce code.

namespace ndof{
    // ----------------------------------------------------------------------------------------------------------------------------
    // Member function pointer generators
    // ----------------------------------------------------------------------------------------------------------------------------

    template<typename ...A>
    struct ArgumentType;

    template<Qualifier q, typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr;

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Unqualified, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A...);
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Const, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A...) const;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Volatile, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A...) volatile;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Volatile | Qualifier::Const, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A...) const volatile;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::LValueRef, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A...) &;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Const | Qualifier::LValueRef, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A...) const &;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Volatile | Qualifier::LValueRef, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A...) volatile &;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Volatile | Qualifier::Const | Qualifier::LValueRef, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A...) const volatile &;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::RValueRef, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A...) &&;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Const | Qualifier::RValueRef, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A...) const &&;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Volatile | Qualifier::RValueRef, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A...) volatile &&;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Volatile|Qualifier::Const|Qualifier::RValueRef, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A...) const volatile &&;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::NoExcept, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A...) noexcept;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Const | Qualifier::NoExcept, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A...) const noexcept;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Volatile | Qualifier::NoExcept, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A...) volatile noexcept;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Volatile | Qualifier::Const | Qualifier::NoExcept, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A...) const volatile noexcept;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Unqualified | Qualifier::LValueRef | Qualifier::NoExcept, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A...) & noexcept;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Const | Qualifier::LValueRef | Qualifier::NoExcept, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A...) const & noexcept;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Volatile | Qualifier::LValueRef | Qualifier::NoExcept, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A...) volatile & noexcept;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Volatile | Qualifier::Const | Qualifier::LValueRef | Qualifier::NoExcept, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A...) const volatile & noexcept;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Unqualified | Qualifier::RValueRef | Qualifier::NoExcept, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A...) && noexcept;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Const | Qualifier::RValueRef | Qualifier::NoExcept, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A...) const && noexcept;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Volatile|Qualifier::RValueRef | Qualifier::NoExcept, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A...) volatile && noexcept;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Volatile | Qualifier::Const | Qualifier::RValueRef | Qualifier::NoExcept, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A...) const volatile && noexcept;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Variadic, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A..., ...);
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Const | Qualifier::Variadic, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A..., ...) const;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Volatile | Qualifier::Variadic, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A..., ...) volatile;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Const | Qualifier::Volatile | Qualifier::Variadic, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A..., ...) const volatile;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::LValueRef | Qualifier::Variadic, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A..., ...) &;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Const | Qualifier::LValueRef | Qualifier::Variadic, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A..., ...) const &;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Volatile | Qualifier::LValueRef | Qualifier::Variadic, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A..., ...) volatile &;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Const | Qualifier::Volatile | Qualifier::LValueRef | Qualifier::Variadic, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A..., ...) const volatile &;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::RValueRef | Qualifier::Variadic, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A..., ...) &&;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Const | Qualifier::RValueRef | Qualifier::Variadic, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A..., ...) const &&;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Volatile | Qualifier::RValueRef | Qualifier::Variadic, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A..., ...) volatile &&;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Const | Qualifier::Volatile | Qualifier::RValueRef | Qualifier::Variadic, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A..., ...) const volatile &&;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::NoExcept | Qualifier::Variadic, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A..., ...) noexcept;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Const | Qualifier::NoExcept | Qualifier::Variadic, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A..., ...) const noexcept;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Volatile | Qualifier::NoExcept | Qualifier::Variadic, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A..., ...) volatile noexcept;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Const | Qualifier::Volatile | Qualifier::NoExcept | Qualifier::Variadic, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A..., ...) const volatile noexcept;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Unqualified | Qualifier::LValueRef | Qualifier::NoExcept | Qualifier::Variadic, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A..., ...) & noexcept;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Const | Qualifier::LValueRef | Qualifier::NoExcept | Qualifier::Variadic, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A..., ...) const & noexcept;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Volatile | Qualifier::LValueRef | Qualifier::NoExcept | Qualifier::Variadic, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A..., ...) volatile & noexcept;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Const | Qualifier::Volatile | Qualifier::LValueRef | Qualifier::NoExcept | Qualifier::Variadic, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A..., ...) const volatile & noexcept;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::RValueRef | Qualifier::NoExcept, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A..., ...) && noexcept;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Const | Qualifier::RValueRef | Qualifier::NoExcept | Qualifier::Variadic, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A..., ...) const && noexcept;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Volatile|Qualifier::RValueRef | Qualifier::NoExcept | Qualifier::Variadic, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A..., ...) volatile && noexcept;
    };

    template<typename R, typename C, typename ...A>
    struct GenerateMemberFunctionPtr<Qualifier::Const | Qualifier::Volatile | Qualifier::RValueRef | Qualifier::NoExcept | Qualifier::Variadic, R, C, ArgumentType<A...>> {
        using type =  R(C::*)(A..., ...) const volatile && noexcept;
    };

    // ----------------------------------------------------------------------------------------------------------------------------
    // Function generators
    // ----------------------------------------------------------------------------------------------------------------------------
    
    template<Qualifier q, typename R, typename C, typename ...A>
    struct GenerateFunction;

    template<typename R, typename ...A>
    struct GenerateFunction<Qualifier::Unqualified, R, ArgumentHelper<A...>>{
        using type =  R(*)(A...);
    };

    template<typename R, typename ...A>
    struct GenerateFunction<Qualifier::NoExcept, R, ArgumentHelper<A...>>{
        using type =  R(*)(A...) noexcept;
    };

    template<typename R, typename ...A>
    struct GenerateFunction<Qualifier::Variadic, R, ArgumentHelper<A...>>{
        using type =  R(*)(A..., ...);
    };

    template<typename R, typename ...A>
    struct GenerateFunction<Qualifier::NoExcept | Qualifier::Variadic, R, ArgumentHelper<A...>>{
        using type =  R(*)(A..., ...) noexcept;
    };



    // ----------------------------------------------------------------------------------------------------------------------------
    // Function pointer generators
    // ----------------------------------------------------------------------------------------------------------------------------

    template<Qualifier q, typename R, typename A>
    struct GenerateFunctionPtr;

    template<typename R, typename ...A>
    struct GenerateFunctionPtr<Qualifier::Unqualified, R, ArgumentHelper<A...>>{
        using type =  R(*)(std::ref(A));
    };

    template<typename R, typename ...A>
    struct GenerateFunctionPtr<Qualifier::NoExcept, R, ArgumentHelper<A...>>{
        using type =  R(*)(A...) noexcept;
    };

    template<typename R, typename ...A>
    struct GenerateFunctionPtr<Qualifier::Variadic, R, ArgumentHelper<A...>>{
        using type =  R(*)(A..., ...);
    };

    template<typename R, typename ...A>
    struct GenerateFunctionPtr<Qualifier::NoExcept | Qualifier::Variadic, R, ArgumentHelper<A...>>{
        using type =  R(*)(A..., ...) noexcept;
    };

    template<typename R, typename ...A>
    struct GenerateFunctionPtr<Qualifier::Const_Ptr, R, ArgumentHelper<A...>>{
        using type =  R(* const)(A...);
    };

    template<typename R, typename ...A> 
    struct GenerateFunctionPtr<Qualifier::Volatile_Ptr, R, ArgumentHelper<A...>>{
        using type =  R(* volatile)(A...);
    };

    template<typename R, typename ...A> 
    struct GenerateFunctionPtr<Qualifier::Const_Ptr | Qualifier::Volatile_Ptr, R, ArgumentHelper<A...>>{
        using type =  R(* const volatile)(A...);
    };

    template<typename R, typename ...A> 
    struct GenerateFunctionPtr<Qualifier::Const_Ptr | Qualifier::NoExcept, R, ArgumentHelper<A...>>{
        using type =  R(* const)(A...) noexcept;
    };

    template<typename R, typename ...A>
    struct GenerateFunctionPtr<Qualifier::Volatile_Ptr | Qualifier::NoExcept, R, ArgumentHelper<A...>>{
        using type =  R(* volatile)(A...) noexcept;
    };

    template<typename R, typename ...A>
    struct GenerateFunctionPtr<Qualifier::Const_Ptr | Qualifier::Volatile_Ptr | Qualifier::NoExcept, R, ArgumentHelper<A...>>{
        using type =  R(* const volatile)(A...) noexcept;
    };

    template<typename R, typename ...A> 
    struct GenerateFunctionPtr<Qualifier::Const_Ptr | Qualifier::Variadic, R, ArgumentHelper<A...>>{
        using type =  R(* const)(A..., ...);
    };

    template<typename R, typename ...A>
    struct GenerateFunctionPtr<Qualifier::Volatile_Ptr | Qualifier::Variadic, R, ArgumentHelper<A...>>{
        using type =  R(* volatile)(A..., ...);
    };

    template<typename R, typename ...A>
    struct GenerateFunctionPtr<Qualifier::Const_Ptr | Qualifier::Volatile_Ptr | Qualifier::Variadic, R, ArgumentHelper<A...>>{
        using type =  R(* const volatile)(A..., ...);
    };

    template<typename R, typename ...A> 
    struct GenerateFunctionPtr<Qualifier::Const_Ptr | Qualifier::NoExcept | Qualifier::Variadic, R, ArgumentHelper<A...>>{
        using type =  R(* const)(A..., ...) noexcept;
    };

    template<typename R, typename ...A>
    struct GenerateFunctionPtr<Qualifier::Volatile_Ptr | Qualifier::NoExcept | Qualifier::Variadic, R, ArgumentHelper<A...>>{
        using type =  R(* volatile)(A..., ...) noexcept;
    };  

    template<typename R, typename ...A>
    struct GenerateFunctionPtr<Qualifier::Const_Ptr | Qualifier::Volatile_Ptr | Qualifier::NoExcept | Qualifier::Variadic, R,  ArgumentHelper<A...>>{
        using type =  R(* const volatile)(A..., ...) noexcept;
    };
 
    // ----------------------------------------------------------------------------------------------------------------------------
    template<Callable F>
    struct as_function_ptr{
        using type = typename GenerateFunctionPtr<F::qualifiers, typename F::ReturnType, typename F::ArgTypes>::type;
    };

    template<Callable F>
    using as_function_ptr_t = typename as_function_ptr<F>::type;

    template<Callable F>
    constexpr bool can_convert_to_function_ptr_v = std::is_convertible_v<F, as_function_ptr_t<F>>;
    

}
#endif
 