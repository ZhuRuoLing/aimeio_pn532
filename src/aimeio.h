//
// Created by ZhuRuoLing on 2/3/2025.
//

#ifndef AIME_IO_PN532_AIMEIO_H
#define AIME_IO_PN532_AIMEIO_H

#define EXPORT __declspec(dllexport)

#pragma once

#include <Windows.h>

#include <cstddef>
#include <cstdint>

EXPORT uint16_t aime_io_get_api_version();

EXPORT HRESULT aime_io_init();

EXPORT HRESULT aime_io_nfc_poll(uint8_t unit_no);

EXPORT HRESULT aime_io_nfc_get_aime_id(
    uint8_t unit_no,
    uint8_t *luid,
    size_t luid_size);

EXPORT HRESULT aime_io_nfc_get_felica_id(uint8_t unit_no, uint64_t *IDm);


EXPORT void aime_io_led_set_color(uint8_t unit_no, uint8_t r, uint8_t g, uint8_t b);

#endif //AIME_IO_PN532_AIMEIO_H
