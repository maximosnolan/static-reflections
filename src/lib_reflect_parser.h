#ifndef INCLUDED_LIB_REFLECT_PARSER_H
#define INCLUDED_LIB_REFLECT_PARSER_H

#include <iostream>
#include <type_traits>
#include <string>
#include <cxxabi.h> 

// Impl 
// Macro to generate the has<FuncName> template struct with specified return type
#define GENERATE_STATIC_REFLECTION_MEMBER_FUNCTION(__FuncName__, __ReturnType__, __Lookup__) \
template <typename T> \
struct has_##__FuncName__##_returnType_##__Lookup__ { \
private: \
    template <typename C> \
    static constexpr auto check(C*) -> \
        typename std::is_same<decltype(std::declval<C>().FuncName()), __ReturnType__>::type; \
    \
    template <typename> \
    static constexpr std::false_type check(...); \
    \
public: \
    static constexpr bool value = std::is_same<decltype(check<T>(nullptr)), std::true_type>::value; \
}; \
template <typename T> \
constexpr bool has_##__FuncName__##_returnType_##__Lookup__##_v = has_##__FuncName__##_returnType_##__Lookup__<T>::value

// Macro to generate the has<VarName> template struct with specified type
#define GENERATE_STATIC_REFLECTION_MEMBER_VARIABLE(__VarName__, __VarType__, __Lookup__) \
template <typename T> \
struct has_##__VarName__##_ofType_##__Lookup__ { \
private: \
    template <typename C> \
    static constexpr auto check(C*) -> \
        typename std::is_same<decltype(std::declval<C>().__VarName__), __VarType__>::type; \
    \
    template <typename> \
    static constexpr std::false_type check(...); \
    \
public: \
    static constexpr bool value = std::is_same<decltype(check<T>(nullptr)), std::true_type>::value; \
}; \
template <typename T> \
constexpr bool has_##__VarName__##_ofType_##__Lookup__##_v = has_##__VarName__##_ofType_##__Lookup__<T>::value

// Helper struct to extract type name
template <typename T>
struct TypeName {
    static std::string get() {

        const char* mangled_name = typeid(T).name();

        int status;
        char* demangled_name = abi::__cxa_demangle(mangled_name, nullptr, nullptr, &status);

        if (status == 0) {
            std::string name(demangled_name);
            free(demangled_name); // Free the demangled name allocated by __cxa_demangle
            return name;
        } else {
            return mangled_name;
        }
    }
};

// Macro to get the type name as a string
#define TYPE_NAME(type) TypeName<type>::get()

#endif