#pragma once

#include <iostream>
#include <string_view>

namespace mipslab {

    enum class LogLevel {
        Debug,
        Info,
        Warning,
        Error
    };

    class Logger {
    public:
        static void log(
            LogLevel level,
            std::string_view message
        );

        static void debug(std::string_view message);
        static void info(std::string_view message);
        static void warning(std::string_view message);
        static void error(std::string_view message);
    };

}

