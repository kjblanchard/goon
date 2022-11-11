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
