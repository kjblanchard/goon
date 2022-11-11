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
#ifdef GN_PLATFORM_MACOS
#ifdef GN_ENABLE_ASSERTS
#include <signal.h>
#define GN_ASSERT(x, ...) {if(!(x)){GN_ERROR("Assertion Failed! {0}", __VA_ARGS__); raise(SIGTRAP); } }
#define GN_CORE_ASSERT(x, ...) {if(!(x)){GN_CORE_ERROR("Assertion Failed! {0}", __VA_ARGS__); raise(SIGTRAP); } }
#else
#define GN_ASSERT(x, ...)
#define GN_CORE_ASSERT(x, ...)
#endif
#else
#ifdef GN_ENABLE_ASSERTS
#define GN_ASSERT(x, ...) {if(!(x)){GN_ERROR("Assertion Failed! {0}", __VA_ARGS__); __debugbreak(); } }
#define GN_CORE_ASSERT(x, ...) {if(!(x)){GN_CORE_ERROR("Assertion Failed! {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define GN_ASSERT(x, ...)
#define GN_CORE_ASSERT(x, ...)
#endif
#endif
