#include <string> 
#include <iostream> 

#include <lib_reflect_parser.h>

// Example usage
struct HasVar {
    int myVar;
};

struct NoVar {};

struct HasFoo {
    int foo() { return 0; }
};

struct NoFoo {};

struct HasFooStr
{
    std::string foo() { return ""; }
};

// Generate the type trait for "foo" with return type int
GENERATE_STATIC_REFLECTION_MEMBER_FUNCTION(foo, int, int);
GENERATE_STATIC_REFLECTION_MEMBER_FUNCTION(foo, std::string, string);

// Generate the type trait for "myVar" with type int
GENERATE_STATIC_REFLECTION_MEMBER_VARIABLE(myVar, int, int);

template<typename T> 
void doSomething(T& var)
{
    if constexpr (has_foo_returnType_int_v<T>)
    {
        // do work for this type 
        std::cout << "this type[" << TYPE_NAME(T) << "] has foo int\n";
    }
    if constexpr (has_foo_returnType_string_v<T>)
    {
        std::cout << "this type[" << TYPE_NAME(T) << "] has foo -> std::string\n";
    }

    if constexpr (has_myVar_ofType_int_v<T>)
    {
        // do work for this type 
        std::cout << "this type[" << TYPE_NAME(T) << "] has myVar (int)\n";
    }
    // do work for all types
}

int main() {
    std::cout << "HasFoo\n";
    HasFoo hasFooType;
    doSomething(hasFooType);

    std::cout << "HasFooStr\n";
    HasFooStr hasFooStr; 
    doSomething(hasFooStr);

    std::cout << "NoFoo\n";
    NoFoo noFooType; 
    doSomething(noFooType);

    std::cout << "HasVar\n";
    HasVar hasVarType; 
    doSomething(hasVarType);

    std::cout << "NoVar\n";
    NoVar noVarType;
    doSomething(noVarType);

}