# Static Reflections

I had a need at work for a very primative version of static reflections, so I created this small library:

# Usage: 

After linking the library, you can reflect a type to expose its member variables or functions as such:

```cpp
GENERATE_STATIC_REFLECTION_MEMBER_FUNCTION(@Param functionName, @Param Function return type, @Param accessor name);
```

For example, for primative types:

```cpp
GENERATE_STATIC_REFLECTION_MEMBER_FUNCTION(foo, int, int);

// Generates:

template <typename T> 
struct has_foo_returnType_int { 
private: 
    template <typename C> 
    static constexpr auto check(C*) -> 
        typename std::is_same<decltype(std::declval<C>().FuncName()), int>::type; 
    
    template <typename> 
    static constexpr std::false_type check(...); 
    \
public: \
    static constexpr bool value = std::is_same<decltype(check<T>(nullptr)), std::true_type>::value; 
}; 
template <typename T> 
constexpr bool has_foo_returnType_int_v = has_foo_returnType_int<T>::value

// Can access simply by:

template<typename T>
if constexpr (has_foo_returnType_int_v<T>)
{
  // do work
}
```

For types that are non primative and might have long names (such as std::optional<std::vector<int32_t>>), you can use the third argument to generate the return type name for easier usability:

```cpp
GENERATE_STATIC_REFLECTION_MEMBER_FUNCTION(foo, std::string, string);

// Generates:
template <typename T> 
struct has_foo_returnType_string { 
private: 
    template <typename C> 
    static constexpr auto check(C*) -> 
        typename std::is_same<decltype(std::declval<C>().FuncName()), std::string>::type; 
    
    template <typename> 
    static constexpr std::false_type check(...); 
    \
public: \
    static constexpr bool value = std::is_same<decltype(check<T>(nullptr)), std::true_type>::value; 
}; 
template <typename T> 
constexpr bool has_foo_returnType_string_v = has_foo_returnType_string<T>::value

// Can access simply by:

template<typename T>
if constexpr (has_foo_returnType_string_v<T>)
{
  // do work
}
```

Note that all calls to the generated code must be in a constexpr constext, as c++ does NOT support runtime reflections, we must rely on static reflections :( 

```cpp

GENERATE_STATIC_REFLECTION_MEMBER_FUNCTION(foo, std::string, string);


// WILL NOT COMPILE AS IS NOT IN CONSTEXPR CONTEXT
template<typename T>
void func()
{
if (has_foo_returnType_string_v<T>)
{
    std::cout << "I do not compile\n";
}
}
```


```cpp

GENERATE_STATIC_REFLECTION_MEMBER_FUNCTION(foo, std::string, string);


// will compile as is in contexpr context
template<typename T>
void func()
{
if constexpr (has_foo_returnType_string_v<T>)
{
    std::cout << "I am a string\n";
}
}
```
