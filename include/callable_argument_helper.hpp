#ifndef NDOF_DETAILS_CALLABLE_ARGUMENT_WRAPPER_HPP
#define NDOF_DETAILS_CALLABLE_ARGUMENT_WRAPPER_HPP
#include <cstddef>
#include <tuple>

// TODO: [P2] Use ranges & create a ranged iterator.

namespace ndof
{
    template <typename T>
    struct Identity
    {
        using type = T;

        // Double check T is universal reference.
        auto operator()(auto&& a) -> decltype(a)
        {
            return std::forward<decltype(a)>(a);
        }
    };

    template <typename... A>
    struct ArgumentHelper : std::tuple<A...>
    {
    public:
        // Pull the base class's constructor (std::tuple<A...>) into this struct.
        using std::tuple<A...>::tuple;
        using type = std::tuple<A...>;
        using number_of_arguments = std::integral_constant<std::size_t, sizeof...(A)>;

        static constexpr std::size_t index_of_last = number_of_arguments::value - 1;

    private:
        template <typename>
        struct make_parameters;

        template <typename... B>
        struct make_parameters<std::tuple<B...>>
        {
            using type = ArgumentHelper<B...>;
        };

        template <typename, typename>
        struct ReverseImpl
        {
        };

        template <typename... Accumulator>
        struct ReverseImpl<ArgumentHelper<>, ArgumentHelper<Accumulator...>>
        {
            using type = ArgumentHelper<Accumulator...>;
        };

        template <typename Head, typename... Tail, typename... Accumulator>
        struct ReverseImpl<ArgumentHelper<Head, Tail...>, ArgumentHelper<Accumulator...>>
        {
            using type = typename ReverseImpl<ArgumentHelper<Tail...>, ArgumentHelper<Head, Accumulator...>>::type;
        };

        template <std::size_t, typename, template <typename> typename>
        struct TakeImpl;

        template <std::size_t N, template <typename> typename Transform, typename... T>
            requires(N == sizeof...(T))
        struct TakeImpl<N, ArgumentHelper<T...>, Transform>
        {
            using type = ArgumentHelper<decltype(std::declval<Transform<T>>()(
                std::declval<T>()))...>;
        };

        template <std::size_t N, template <typename> typename Transform, typename... T>
            requires(N < sizeof...(A) && N != sizeof...(T))
        struct TakeImpl<N, ArgumentHelper<T...>, Transform>
        {
            static constexpr auto current_size = sizeof...(T);
            
            using type = typename TakeImpl<
                N, 
                ArgumentHelper<
                    T..., 
                    std::tuple_element_t<current_size, std::tuple<A...>>
                >, 
                Transform
            >::type;
        };

    public:
        // Reverse the parameter list.

        using Reverse = typename ReverseImpl<ArgumentHelper<A...>, ArgumentHelper<>>::type;

        // Take the first N elements and optionally apply a transform to them.
        template <std::size_t N, template <typename> typename Transform = Identity>
            requires(N <= sizeof...(A))
        using Take = typename TakeImpl<N, ArgumentHelper<>, Transform>::type;

        // Take the last N elements and optionally apply a transform to them.
        template <std::size_t N, template <typename> typename Transform = Identity>
            requires(N <= sizeof...(A))
        using TakeBack = typename Reverse::template Take<N, Transform>::Reverse;

        // Split the parameter list at N.
        template <std::size_t N>
        struct Split
        {
            using first = Take<N>;
            using second = TakeBack<number_of_arguments::value - N>;
        };


        // Apply a transform to all argument types.
        template <template <typename> typename TransformTemplate>
        using Transform = Take<number_of_arguments::value, TransformTemplate>;

        // Take the first N elements and optionally apply a transform to them.
        template <std::size_t N, template <typename> typename Transform = Identity>
        constexpr auto take() const
        {
            return std::apply([](auto... elems)
                              { return Take<N, Transform>{elems...}; }, *this);
        }

        // Take the last N elements and optionally apply a transform to them.
        template <std::size_t N, template <typename> typename Transform = Identity>
        constexpr auto take_back() const
        {
            return std::apply([](auto... elems)
                              { return TakeBack<N, Transform>{elems...}; }, *this);
        }

        // Get any element by position.
        template <std::size_t I>
        constexpr auto get() const
        {
            if constexpr (I >= number_of_arguments::value)
            {
                return std::get<index_of_last>(*this);
            }
            else
            {
                return std::get<I>(*this);
            }
        }

        template <std::size_t N>
        constexpr auto split() const
        {
            return take<N>(), take_back<number_of_arguments::value - N>();
        }

        // Apply a transform to all argument types.
        template <template <typename> typename TransformTemplate>
        constexpr auto transform() const
        {
            return std::apply([](auto &&...elems)
                              { return Transform<TransformTemplate>{std::forward<decltype(elems)>(elems)...}; }, *this);
        }

        // Return the first element as a ArgumentHelper.
        template <template <typename...> typename TransformTemplate = Identity>
        constexpr auto car() const
        {
            return take<1, TransformTemplate>();
        }

        // Return everything but the first element as a ArgumentHelper.
        template <template <typename...> typename TransformTemplate = Identity>
        constexpr auto cdr() const
        {
            return take_back<number_of_arguments::value - 1, TransformTemplate>();
        }

        template <template <typename...> typename TransformTemplate = Identity>
        constexpr auto pop_front() const
        {
            return split<1, TransformTemplate>();
        }

        template <template <typename...> typename TransformTemplate = Identity>
        constexpr auto pop_back() const
        {
            return get<number_of_arguments::value - 1>(), take<number_of_arguments::value - 1, TransformTemplate>();
        }
    };

} // namespace ndof

#endif // NDOF_DETAILS_CALLABLE_ARG_WRAPPER_HPP
