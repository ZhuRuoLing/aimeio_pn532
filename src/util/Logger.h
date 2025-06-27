//
// Created by jkl-9 on 2025-06-27.
//

#ifndef AIME_IO_PN532_LOGGER_H
#define AIME_IO_PN532_LOGGER_H

#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

class Logger {
private:
    std::ofstream logFile;

public:
    Logger(const std::string& filename);

    ~Logger();

    template <typename... Args>
    void log(const std::string& format, Args&&... args);
};


#endif //AIME_IO_PN532_LOGGER_H
