#ifdef GN_PLATFORM_WINDOWS
#ifdef GN_BUILD_DLL
#define GN_API __declspec(dllexport)
#else
#define GN_API __declspec(dllimport)
#endif
#else
#define GN_API
#endif

#define BIT(x) (1 << x)
#if defined(GN_PLATFORM_MACOS) || defined(GN_PLATFORM_LINUX)
#ifdef GN_ENABLE_ASSERTS
#include <signal.h>
#define GN_ASSERT(x, ...)                                   \
    {                                                       \
        if (!(x))                                           \
        {                                                   \
            GN_ERROR("Assertion Failed! {0}", __VA_ARGS__); \
            raise(SIGTRAP);                                 \
        }                                                   \
    }
#define GN_CORE_ASSERT(x, ...)                                   \
    {                                                            \
        if (!(x))                                                \
        {                                                        \
            GN_CORE_ERROR("Assertion Failed! {0}", __VA_ARGS__); \
            raise(SIGTRAP);                                      \
        }                                                        \
    }
#else
#define GN_ASSERT(x, ...)
#define GN_CORE_ASSERT(x, ...)
#endif
#else
#ifdef GN_ENABLE_ASSERTS
#define GN_ASSERT(x, ...)                                   \
    {                                                       \
        if (!(x))                                           \
        {                                                   \
            GN_ERROR("Assertion Failed! {0}", __VA_ARGS__); \
            __debugbreak();                                 \
        }                                                   \
    }
#define GN_CORE_ASSERT(x, ...)                                   \
    {                                                            \
        if (!(x))                                                \
        {                                                        \
            GN_CORE_ERROR("Assertion Failed! {0}", __VA_ARGS__); \
            __debugbreak();                                      \
        }                                                        \
    }
#else
#define GN_ASSERT(x, ...)
#define GN_CORE_ASSERT(x, ...)
#endif
#endif

// This is used to bind a function from a class easily..  It passes in the current object with this, and then passes in the variable passed in as the second param
#define GN_BIND_EVENT_FN(x) std::bind(x, this, std::placeholders::_1)
