#pragma once

#include <Goon/Core.hpp>
#include <spdlog/logger.h>
#include <spdlog/fmt/ostr.h>

namespace Goon {
    /**
     * @brief Singleton logging class for the engine and application
     */
    class GN_API Log
    {
        public:
            /**
             * @brief Initializes the Logger
             */
            static void Init();
            /**
             * @brief Gets the core logger
             *
             * @return Shared ptr to a core logger used for the engine
             */
            inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() {return s_CoreLogger;}
            /**
             * @brief Gets the Client (application) logger
             *
             * @return Shared ptr to a client logger
             */
            inline static std::shared_ptr<spdlog::logger>& GetClientLogger() {return s_ClientLogger;}
        private:
            /**
             * @brief Shared ptr to a spdlog logger
             */
            static std::shared_ptr<spdlog::logger> s_CoreLogger;
            /**
             * @brief Shared ptr to a client logger
             */
            static std::shared_ptr<spdlog::logger> s_ClientLogger;


    };
}

//Macros so that we can strip this in distribution builds easily.
//
//Core log metrics
#define GN_CORE_ERROR(...) ::Goon::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GN_CORE_WARN(...) ::Goon::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GN_CORE_INFO(...) ::Goon::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GN_CORE_TRACE(...) ::Goon::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GN_CORE_FATAL(...) ::Goon::Log::GetCoreLogger()->fatal(__VA_ARGS__)
//Client log metrics
#define GN_ERROR(...) ::Goon::Log::GetClientLogger()->error(__VA_ARGS__)
#define GN_WARN(...) ::Goon::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GN_INFO(...) ::Goon::Log::GetClientLogger()->info(__VA_ARGS__)
#define GN_TRACE(...) ::Goon::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GN_FATAL(...) ::Goon::Log::GetClientLogger()->fatal(__VA_ARGS__)
