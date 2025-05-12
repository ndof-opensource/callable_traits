#ifndef NDOF_DETAILS_CALLABLE_UTILS_HPP
#define NDOF_DETAILS_CALLABLE_UTILS_HPP

 
#include "callable_traits.hpp"
#include "callable_concepts.hpp"

#include <type_traits>
#include <concepts>

namespace ndof{
 
    template<typename ...W>
    struct has_rvalue_ref_v : std::true_type{};
    
    template<typename ...A>
    struct has_rvalue_ref_v : std::false_type requires (!(std::is_rvalue_reference_v<A> || ...)){};

 
    template<Function F, Function G>
    requires (CallableTraits<G>::argument_count <= CallableTraits<F>::argument_count)
    struct is_callable_with_args{
        using R = typename CallableTraits<F>::ReturnType;
        // TODO: Replace take_n_types_from_tuple with ArgumentHelper.  
        using Args = typename take_n_types_from_tuple<CallableTraits<G>::argument_count,CallableTraits<F>::ArgTypes>::type;
        template<typename A...>
        constexpr bool is_invocable = false;

        template<typename ...A>
        constexpr bool is_invocable<std::tuple<A...>> = std::same_as<void, R> ?
             std::is_invocable_v<G,A...> 
             : std::is_invocable_r_v<R,G,A...>;

        static constexpr bool value = is_invocable<Args>;
    };


    
}
#endif
