#include <gtest/gtest.h>
#include "callable_concepts.hpp"

using namespace ndof;

// Helpers for triggering compile-time concept evaluation
template<typename T>
constexpr bool is_callable = Callable<T>;

template<typename T>
constexpr bool is_standalone_function = StandaloneFunction<T>;

template<typename T>
constexpr bool is_functor = Functor<T>;

template<typename T>
constexpr bool is_std_function = StdFunction<T>;

template<typename T>
constexpr bool is_member_function_ptr = MemberFunctionPtr<T>;

template<typename T>
constexpr bool is_function_ptr = FunctionPtr<T>;

template<typename T>
constexpr bool is_function = Function<T>;

// Free function
void free_function(int) {}
void another_function(double) {}

struct MyClass {
    void member_function(char) {}
};

struct FunctorType {
    void operator()() const {}
};

struct FunctorWithArgs {
    int operator()(int, float) { return 0; }
};

TEST(CallableConceptTests, FunctionTypes) {
    static_assert(is_function<void(int)>);
    static_assert(!is_function<int>);
}

TEST(CallableConceptTests, FunctionPointers) {
    static_assert(is_function_ptr<void(*)(double)>);
    static_assert(!is_function_ptr<int*>);
}

TEST(CallableConceptTests, MemberFunctionPointers) {
    static_assert(is_member_function_ptr<void(MyClass::*)(char)>);
    static_assert(!is_member_function_ptr<void(*)(char)>);
}

TEST(CallableConceptTests, FunctorsAndLambdas) {
    static_assert(is_functor<FunctorType>);
    static_assert(is_functor<FunctorWithArgs>);
    static_assert(is_functor<decltype([](){})>);
    static_assert(is_functor<decltype([](int){ return 1; })>);
}

TEST(CallableConceptTests, StdFunctionVariants) {
    using StdFunc = std::function<void()>;
    using StdFuncWithArgs = std::function<int(int, float)>;

    static_assert(is_std_function<StdFunc>);
    static_assert(is_std_function<const StdFuncWithArgs&>);
    static_assert(!is_std_function<int>);
}

TEST(CallableConceptTests, Callable) {
    using StdFunc = std::function<void()>;
    using Lambda = decltype([](int){});

    static_assert(is_callable<void(int)>);
    static_assert(is_callable<void(*)(int)>);
    static_assert(is_callable<void(MyClass::*)(char)>);
    static_assert(is_callable<FunctorType>);
    static_assert(is_callable<Lambda>);
    static_assert(is_callable<StdFunc>);
}

TEST(CallableConceptTests, StandaloneFunction) {
    static_assert(is_standalone_function<void(int)>);
    static_assert(is_standalone_function<void(*)(double)>);
    static_assert(!is_standalone_function<FunctorType>);
    static_assert(!is_standalone_function<std::function<void()>>);
}

