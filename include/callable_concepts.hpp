#ifndef NDOF_CALLABLE_CONCEPTS_HPP
#define NDOF_CALLABLE_CONCEPTS_HPP
 
#include <type_traits>
#include <concepts>
#include <optional>

namespace ndof {

    template<typename F> concept Functor           = requires(F f) { &F::operator(); };
    template<typename F> concept Function          = std::is_function_v<F>;
    template<typename F> concept FunctionPtr       = std::is_pointer_v<F> && Function<std::remove_pointer_t<F>>;
    template<typename F> concept MemberFunctionPtr = std::is_member_function_pointer_v<F>;
    
    template<typename F>
    concept Callable = 
        MemberFunctionPtr<F> 
        || Function<F>
        || FunctionPtr<F>
        || Functor<F>;
    
    template<typename F>
    concept StandaloneFunction = 
        Function<F> 
        || FunctionPtr<F>;
    
}

 


#endif
