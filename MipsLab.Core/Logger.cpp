#include "pch.h"
#include "Logger.hpp"

#include <iostream>

namespace mipslab {

    void Logger::log(
        LogLevel level,
        std::string_view message
    ) {
        const char* label = "";

        switch (level) {
        case LogLevel::Debug:
            label = "DEBUG";
            break;
        case LogLevel::Info:
            label = "INFO";
            break;
        case LogLevel::Warning:
            label = "WARNING";
            break;
        case LogLevel::Error:
            label = "ERROR";
            break;
        }

        std::cerr << '[' << label << "] "
            << message << '\n';
    }

    void Logger::debug(std::string_view message) {
        log(LogLevel::Debug, message);
    }

    void Logger::info(std::string_view message) {
        log(LogLevel::Info, message);
    }

    void Logger::warning(std::string_view message) {
        log(LogLevel::Warning, message);
    }

    void Logger::error(std::string_view message) {
        log(LogLevel::Error, message);
    }

}
