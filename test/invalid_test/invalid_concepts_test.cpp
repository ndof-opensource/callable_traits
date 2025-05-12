#include <callable_traits/ndof-os/callable_concepts.hpp>

using namespace ndof;

// Each of these instantiates a type or function with a concept constraint
// that should fail at compile time if the concept is correctly defined.

// Callable<int> int is not callable
template<Callable T>
struct InvalidCallableTest {};

InvalidCallableTest<int> bad1;

// FunctionPtr<double*> double* is not a pointer to a function
template<FunctionPtr T>
struct InvalidFunctionPtrTest {};

InvalidFunctionPtrTest<double*> bad2;

// MemberFunctionPtr<void(*)(int)> this is a function pointer, not a member function pointer
template<MemberFunctionPtr T>
struct InvalidMemberFunctionPtrTest {};

InvalidMemberFunctionPtrTest<void(*)(int)> bad3;

// StdFunction<int> int is not a std::function<R(Args...)>
template<StdFunction T>
struct InvalidStdFunctionTest {};

InvalidStdFunctionTest<int> bad4;
