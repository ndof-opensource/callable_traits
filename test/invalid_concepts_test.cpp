#include "callable_concepts.hpp"

using namespace ndof;

struct NotCallable {};

void test_invalid() {
    static_assert(!Callable<int>);
    static_assert(!Callable<NotCallable>);
    static_assert(!FunctionPtr<double*>);
    static_assert(!MemberFunctionPtr<void(*)(int)>);
    static_assert(!StdFunction<int>);
}

