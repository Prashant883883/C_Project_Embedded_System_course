#include <stdio.h>
#include "pico/stdlib.h"

int main() {
    stdio_init_all();

    const uint LED_PIN = 15;   // External LED on GP15

    gpio_init(LED_PIN);        
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (true) {
        gpio_put(LED_PIN, 1);   // turn ON
        sleep_ms(500);

        gpio_put(LED_PIN, 0);   // turn OFF
        sleep_ms(500);
    }
}
