//
// Created by ZhuRuoLing on 2/3/2025.
//

#include "aimeio.h"
#include "Felica.h"
#include "string"
#include "sstream"
#include "iostream"
#include "util/Logger.h"

static FelicaReader *felicaReader = nullptr;
static Logger logger = Logger("aimeio.log");
static uint8_t idM[8];
static bool hasAime = false;

#define CONFIG_PATH ".\\segatools.ini"

uint16_t aime_io_get_api_version() {
    return 0x0100;
}

HRESULT aime_io_init() {
    if (felicaReader) {
        delete felicaReader;
        felicaReader = nullptr;
    }
    char devicePort[256] = {0};
    DWORD result = GetPrivateProfileString(
        "aime",
        "device_port",
        "COM6",
        devicePort,
        sizeof(devicePort),
        CONFIG_PATH
    );

    if (result > 0) {
        logger.log("device_port = {}", devicePort);
    } else {
        logger.log("Failed to read device_port from INI file.\n");
    }

    std::string conn_string;
    conn_string += "pn532_uart:";
    conn_string += devicePort;

    felicaReader = new FelicaReader(conn_string.c_str(), false);
    if (!felicaReader->createDevice()) {
        return S_FALSE;
    }
    logger.log("createDevice Success.");
    return S_OK;
}

HRESULT aime_io_nfc_poll(uint8_t unit_no) {
    if (unit_no != 0)return S_OK;
    if (felicaReader) {
        logger.log("Polling!");
        hasAime = felicaReader->readCardForId(idM) == 1;
    }
    return S_OK;
}

HRESULT aime_io_nfc_get_aime_id(
    uint8_t unit_no,
    uint8_t *luid,
    size_t luid_size
) {
    logger.log("legacy unit_no {}", unit_no);
    if (unit_no != 0)return S_FALSE;

    if (hasAime) {
        std::stringstream ss;
        for (const auto &item: idM) {
            ss << (int)item;
        }
        while (ss.str().length() < 20) {
            ss << '0';
        }
        std::string luidString = ss.str();
        logger.log("Legacy luid: {}", luidString);
        uint8_t id[10];
        memset(id, 0, 10);
        for (int i = 0, j = 0; i < 20; i += 2) {
            id[j++] = (uint8_t) (stoi(luidString.substr(i, 2)));
        }
        memcpy(luid, id, 10);
        return S_OK;
    }
    return S_FALSE;
}

HRESULT aime_io_nfc_get_felica_id(uint8_t unit_no, uint64_t *IDm) {
    logger.log("felica id {}", unit_no);
    if (unit_no != 0)return S_FALSE;
    if (!hasAime) {
        logger.log("we have no aime.");
        return S_FALSE;
    }
    logger.log("before aime!!! {:#x}", *IDm);
    uint64_t value = 0;
    for (int i = 0; i < 8; ++i) {
        value = (value<<8) | idM[i];
    }
    *IDm = value;
    logger.log("after aime!!! {:#x}", *IDm);

    return S_OK;
}


void aime_io_led_set_color(uint8_t unit_no, uint8_t r, uint8_t g, uint8_t b) {
    //we have no leds xD
}