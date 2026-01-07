#include <stdio.h>
#include "pico/stdlib.h"

int main() {
    stdio_init_all();

    const uint RED = 15;
    const uint YELLOW = 14;
    const uint GREEN = 13;
    const uint BUZZER = 2;
    const uint BUTTON = 17;

    // Initialize LEDs
    gpio_init(RED);
    gpio_set_dir(RED, GPIO_OUT);

    gpio_init(YELLOW);
    gpio_set_dir(YELLOW, GPIO_OUT);

    gpio_init(GREEN);
    gpio_set_dir(GREEN, GPIO_OUT);

    // Initialize buzzer
    gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);

    // Initialize button
    gpio_init(BUTTON);
    gpio_set_dir(BUTTON, GPIO_IN);
    gpio_pull_down(BUTTON);   // since button goes to 3.3V

    while (true) {

       if (gpio_get(BUTTON)) {
    gpio_put(RED, 1);
    gpio_put(YELLOW, 0);
    gpio_put(GREEN, 0);

    
    for (int i = 0; i < 1000; i++) {
        gpio_put(BUZZER, 1);
        sleep_us(250);
        gpio_put(BUZZER, 0);
        sleep_us(250);
    }
}

        else {
            // NORMAL TRAFFIC LIGHT CYCLE

            // RED
            gpio_put(RED, 1);
            gpio_put(YELLOW, 0);
            gpio_put(GREEN, 0);
            sleep_ms(1500);

            // YELLOW
            gpio_put(RED, 0);
            gpio_put(YELLOW, 1);
            gpio_put(GREEN, 0);
            sleep_ms(1000);

            // GREEN
            gpio_put(RED, 0);
            gpio_put(YELLOW, 0);
            gpio_put(GREEN, 1);
            sleep_ms(1500);
        }
    }
}
