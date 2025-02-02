//
// Created by ZhuRuoLing on 2/2/2025.
//

#ifndef AIME_IO_PN532_FELICA_H
#define AIME_IO_PN532_FELICA_H


#include <cstdint>
#include "nfc/nfc.h"
#include <iostream>
#include <fstream>
#include <filesystem>

#define OPEN_DEVICE_FAILED (-1)
#define INIT_DEVICE_FAILED (-1)

namespace fs = std::filesystem;

class Logger {
private:
    std::ofstream logFile;

public:
    Logger(const std::string& filename) {
        if (fs::exists(filename)) {
            fs::remove(filename);
        }

        logFile.open(filename, std::ios::out | std::ios::app);
    }

    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    template <typename... Args>
    void log(const std::string& format, Args&&... args) {
        if (logFile.is_open()) {
            std::string formatted_message = std::vformat(format, std::make_format_args(args...));
            logFile << formatted_message << std::endl;
        } else {
            std::cerr << "Log file is not open. Message not logged." << std::endl;
        }
    }
};

class FelicaReader {
private:
    nfc_context *context = nullptr;
    nfc_device *reader = nullptr;
    const char *connString = nullptr;
    bool silence = false;
public:
    FelicaReader(const char *connString, bool silence) noexcept;

    ~FelicaReader() noexcept;

    int createDevice() noexcept;

    int readCardForId(uint8_t *id) noexcept;
};


#endif //AIME_IO_PN532_FELICA_H
