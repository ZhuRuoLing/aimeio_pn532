//
// Created by jkl-9 on 2025-06-27.
//

#ifndef AIME_IO_PN532_LOGGING_H
#define AIME_IO_PN532_LOGGING_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include "dprintf.h"

namespace fs = std::filesystem;

#define logr(FORMAT) dprintf(FORMAT)

#define log(FORMAT,...) dprintf(std::format(FORMAT, __VA_ARGS__).c_str())


#endif //AIME_IO_PN532_LOGGING_H
