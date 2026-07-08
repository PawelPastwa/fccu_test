#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

/* Nasze własne, profesjonalnie wyizolowane moduły */
#include "system_status.h"
#include "can_interface.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);


// DO TESTU NA ESP32S3 SUPER MINI ZGODNIE Z DTSI TRZEBA POLACZYC KABLEM GPIO 4 i 5

int main(void) {
    // Zatrzymujemy procesor na 4 sekundy.
    k_msleep(4000);

    LOG_INF("=== Uruchamianie komputera pokładowego VCU (ESP32-S3) ===");

    init_system_status();
    init_can_system();

    uint8_t test_payload[4] = {0xDE, 0xAD, 0xBE, 0xEF};
    LOG_INF("Wysylam testowa ramke CAN...");
    can_transmit_message(0x123, test_payload, 4);

    /* nadajemy stały sygnał */
    while (1) {
        LOG_INF("System zyje... wystrzeliwuje ramke do sieci CAN.");
        can_transmit_message(0x123, test_payload, 4);

        // Czekamy sekundę przed kolejnym strzałem
        k_msleep(1000);
    }

    return 0;
}