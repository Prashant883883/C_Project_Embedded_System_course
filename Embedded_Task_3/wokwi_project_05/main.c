#include <stdio.h>
#include "pico/stdlib.h"

int main() {
    stdio_init_all();

    const uint LED = 15;
    const uint BUTTON = 14;

    // LED setup
    gpio_init(LED);
    gpio_set_dir(LED, GPIO_OUT);

    // Button setup
    gpio_init(BUTTON);
    gpio_set_dir(BUTTON, GPIO_IN);
    gpio_pull_down(BUTTON);  

    while (true) {
        if (gpio_get(BUTTON)) {    // if button is pressed
            gpio_put(LED, 1);      // turn LED ON
        } else {
            gpio_put(LED, 0);      // turn LED OFF
        }
    }
}
