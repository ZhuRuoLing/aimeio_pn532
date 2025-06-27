//
// Created by ZhuRuoLing on 2/2/2025.
//

#include <cstring>
#include "Felica.h"
#include "util/logging.h"

FelicaReader::FelicaReader(const char *connString, bool silence) noexcept {
    this->connString = connString;
    this->silence = silence;
}

FelicaReader::~FelicaReader() noexcept {
    if (this->reader) {
        nfc_close(this->reader);
    }
    if (this->context) {
        nfc_exit(context);
    }
}

int FelicaReader::createDevice() noexcept {
    nfc_init(&this->context);
    this->reader = nfc_open(this->context, this->connString);
    if (!this->reader) {
        log("Open reader ({}) failed\n", connString);
        return false;
    }
    int initResult = nfc_initiator_init(this->reader);
    if (initResult) {
        log("Init reader as initiator failed.\n");
        return false;
    }
    log("Initiated reader.\n");
    return true;
}

std::string felicaIdToString(const uint8_t *array) {
    std::stringstream ss;
    for (int i = 0; i < 8; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(array[i]);
    }
    return ss.str();
}

int FelicaReader::readCardForId(uint8_t *id) noexcept {
    nfc_modulation modulation{
        .nmt = NMT_FELICA,
        .nbr = NBR_212
    };
    nfc_target target;
    int result = nfc_initiator_list_passive_targets(this->reader, modulation, &target, 1);
    if (result == 1) {
        memcpy(id, target.nti.nfi.abtId, 8);
        log("felica id: {}", felicaIdToString(id));
    }
    return result;
}

