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

#include "util/dprintf.h"
#include "util/Logger.h"

#define OPEN_DEVICE_FAILED (-1)
#define INIT_DEVICE_FAILED (-1)

class FelicaReader {
private:
    nfc_context *context = nullptr;
    nfc_device *reader = nullptr;
    const char *connString = nullptr;
    Logger logger = Logger("logs_Felica.txt");
    bool silence = false;
public:
    FelicaReader(const char *connString, bool silence) noexcept;

    ~FelicaReader() noexcept;

    int createDevice() noexcept;

    int readCardForId(uint8_t *id) noexcept;
};


#endif //AIME_IO_PN532_FELICA_H
