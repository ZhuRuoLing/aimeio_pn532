//
// Created by jkl-9 on 2025-06-27.
//

#include "Logger.h"
#include "dprintf.h"

Logger::Logger(const std::string &filename) {
    if (fs::exists(filename)) {
        fs::remove(filename);
    }

    logFile.open(filename, std::ios::out | std::ios::app);
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

template<typename... Args>
void Logger::log(const std::string &format, Args &&... args) {
    if (logFile.is_open()) {
        std::string formatted_message = std::vformat(format, std::make_format_args(args...));
        logFile << formatted_message << std::endl;
        dprintf(formatted_message.c_str());
    } else {
        std::cerr << "Log file is not open. Message not logged." << std::endl;
    }
}