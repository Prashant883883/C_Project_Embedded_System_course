#include <stdio.h>
#include "pico/stdlib.h"

int main() {
    stdio_init_all();

    const uint LED_PIN = 25;   // Onboard LED pin

    gpio_init(LED_PIN);        // Enable the pin
    gpio_set_dir(LED_PIN, GPIO_OUT);   // Make it an OUTPUT

    while (true) {
        gpio_put(LED_PIN, true);   // Turn LED ON
        sleep_ms(500);             // Wait 0.5 sec

        gpio_put(LED_PIN, false);  // Turn LED OFF
        sleep_ms(500);             // Wait 0.5 sec
    }
}
