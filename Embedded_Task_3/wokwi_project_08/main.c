#include <stdio.h>
#include "pico/stdlib.h"

int main() {
    stdio_init_all();

    const uint PIR = 16;      // PIR OUT pin
    const uint LED = 15;      // LED pin
    const uint BUZZER = 14;   // Passive buzzer pin

    gpio_init(PIR);
    gpio_set_dir(PIR, GPIO_IN);

    gpio_init(LED);
    gpio_set_dir(LED, GPIO_OUT);

    gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);

    while (true) {

        if (gpio_get(PIR)) {
            // Motion detected
            gpio_put(LED, 1);
            printf("Motion Detected!\n");

            // PASSIVE BUZZER TONE (~2 kHz)
            for (int i = 0; i < 1000; i++) {
                gpio_put(BUZZER, 1);
                sleep_us(250);   // ON for 250 microseconds
                gpio_put(BUZZER, 0);
                sleep_us(250);   // OFF for 250 microseconds
            }

        } 
        else {
            // No motion
            gpio_put(LED, 0);
            gpio_put(BUZZER, 0);
        }

        sleep_ms(100); // reduce CPU load
    }
}
