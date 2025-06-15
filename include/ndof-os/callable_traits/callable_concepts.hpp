#ifndef NDOF_CALLABLE_CONCEPTS_HPP
#define NDOF_CALLABLE_CONCEPTS_HPP
 
#include <type_traits>
#include <concepts>
#include <functional>

namespace ndof {

    // Matches std::function<R(Args...)> with any cv/ref qualifiers
    template<typename T>
    struct is_std_function_impl : std::false_type {};
    
    template<typename R, typename... Args>
    struct is_std_function_impl<std::function<R(Args...)>> : std::true_type {};
    
    template<typename T>
    struct is_std_function : is_std_function_impl<std::remove_cvref_t<T>> {};
    
    template<typename F>
    concept StdFunction = is_std_function<F>::value;

    // Matches any type with an operator()
    // TODO: Does not work for overloaded operator(), e.g. [](auto x) {}
    // NOTE: [](auto){} is a templated method type.  Concepts can only be applied to types. (Line 31)
    template<typename F>
    concept Functor = requires {
        typename std::remove_cvref_t<F>;
        requires std::is_class_v<std::remove_cvref_t<F>>;
        requires requires(std::remove_cvref_t<F> f) {
            &std::remove_cvref_t<F>::operator(); // checks for call operator
        };
        requires !StdFunction<F>;
    };

    // Matches raw function types (e.g., void(int))
    template<typename F>
    concept Function = std::is_function_v<F>;

    // Matches references to raw function types
    template<typename T>
    concept FunctionRef 
        = std::is_reference_v<T> 
            && std::is_function_v<std::remove_reference_t<T>>;

    // Matches function pointers (e.g., void(*)(int))
    template<typename F>
    concept FunctionPtr = std::is_pointer_v<F> && Function<std::remove_pointer_t<F>>;

    // Matches member function pointers (e.g., void(Class::*)(int))
    template<typename F>
    concept MemberFunctionPtr = std::is_member_function_pointer_v<F>;

    // Matches any structurally callable type
    template<typename F>
    concept Callable = 
        MemberFunctionPtr<F> 
        || Function<F> 
        || FunctionRef<F>
        || FunctionPtr<F> 
        || Functor<F>
        || StdFunction<F>;

    // Matches only free-standing functions and function pointers
    template<typename F>
    concept StandaloneFunction = 
        Function<F> 
        || FunctionRef<F>
        || FunctionPtr<F>;

    // TODO: Do we want to handle function-like types from other libraries, e.g. 
    // Boost, std::packaged_task, std::bind, etc...?
}

     


#endif
