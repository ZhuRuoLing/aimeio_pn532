#include "nfc/nfc.h"
#include "nfc/nfc-internal.h"
#include "Felica.h"

#include <string>
#include <sstream>
#include <iomanip>
#include <thread>

std::string felicaIdToString0(const uint8_t *array) {
    std::stringstream ss;
    for (int i = 0; i < 8; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(array[i]);
    }
    return ss.str();
}

uint8_t id[8];

int main() {
    FelicaReader reader("pn532_uart:COM6",false);
    if (!reader.createDevice())return 1;
    while (true) {
        if (reader.readCardForId(id) == 1){
            printf("New Aime: %s\n", felicaIdToString0(id).c_str());
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}
