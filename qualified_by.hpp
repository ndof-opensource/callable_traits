#ifndef NDOF_DETAILS_QUALIFIED_BY_HPP
#define NDOF_DETAILS_QUALIFIED_BY_HPP

#include <ndof/details/definitions.hpp>
#include <ndof/details/callable_traits.hpp>
#include <ndof/details/callable_concepts.hpp>

#include <concepts>

namespace ndof {
 

    template<typename F, Qualifier q>
    concept QualifiedBy = 
        Callable<F> 
        && ((((CallableTraits<F>::qualifier & q) == q) 
                && (CallableTraits<F>::qualifiers != Qualifier::Unqualified))
            || ((q == Qualifier::Unqualified)
                && (CallableTraits<F>::qualifiers == Qualifier::Unqualified)));

    template<typename F> concept Unqualified          = QualifiedBy<F, Qualifier::Unqualified>;

    template<typename F> concept NoExceptQualified    = QualifiedBy<F, Qualifier::NoExcept>;
    template<typename F> concept VariadicQualified    = QualifiedBy<F, Qualifier::Variadic>;
    template<typename F> concept ConstQualified       = QualifiedBy<F, Qualifier::Const>;
    template<typename F> concept ConstPtrQualified    = QualifiedBy<F, Qualifier::Const_Ptr>;
    template<typename F> concept VolatileQualified    = QualifiedBy<F, Qualifier::Volatile>;
    template<typename F> concept VolatilePtrQualified = QualifiedBy<F, Qualifier::Volatile_Ptr>;
    template<typename F> concept LValueRefQualified   = QualifiedBy<F, Qualifier::LValueRef>;
    template<typename F> concept RValueRefQualified   = QualifiedBy<F, Qualifier::RValueRef>;

} // namespace ndof

#endif // NDOF_DETAILS_QUALIFIED_BY_HPP