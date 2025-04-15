#include <gtest/gtest.h>
#include <functional>
#include "callable_concepts.hpp"

using namespace ndof;

// Free functions
void free_function(int) {}
void another_function(double) {}

// Member function
struct MyClass {
    void member_function(char) {}
};

// Functor (call operator)
struct FunctorType {
    void operator()() const {}
};

struct FunctorWithArgs {
    int operator()(int, float) { return 0; }
};

TEST(CallableConceptTests, FunctionTypes) {
    static_assert(Function<void(int)>);
    static_assert(!Function<int>);
}

TEST(CallableConceptTests, FunctionPointers) {
    static_assert(FunctionPtr<void(*)(double)>);
    static_assert(!FunctionPtr<int*>);
}

TEST(CallableConceptTests, MemberFunctionPointers) {
    static_assert(MemberFunctionPtr<void(MyClass::*)(char)>);
    static_assert(!MemberFunctionPtr<void(*)(char)>);
}

TEST(CallableConceptTests, FunctorsAndLambdas) {
    static_assert(Functor<FunctorType>);
    static_assert(Functor<FunctorWithArgs>);
    static_assert(Functor<decltype([](){})>);
    static_assert(Functor<decltype([](int){ return 1; })>);
}

TEST(CallableConceptTests, StdFunctionVariants) {
    using StdFunc = std::function<void()>;
    using StdFuncWithArgs = std::function<int(int, float)>;

    static_assert(StdFunction<StdFunc>);
    static_assert(StdFunction<const StdFuncWithArgs&>);
    static_assert(!StdFunction<int>);
}

TEST(CallableConceptTests, CallableIncludesAllValidTypes) {
    using StdFunc = std::function<void()>;
    using Lambda = decltype([](int){});

    static_assert(Callable<void(int)>);
    static_assert(Callable<void(*)(int)>);
    static_assert(Callable<void(MyClass::*)(char)>);
    static_assert(Callable<FunctorType>);
    static_assert(Callable<Lambda>);
    static_assert(Callable<StdFunc>);
}

TEST(CallableConceptTests, StandaloneFunctionExcludesFunctors) {
    static_assert(StandaloneFunction<void(int)>);
    static_assert(StandaloneFunction<void(*)(double)>);
    static_assert(!StandaloneFunction<FunctorType>);
    static_assert(!StandaloneFunction<std::function<void()>>);
}

