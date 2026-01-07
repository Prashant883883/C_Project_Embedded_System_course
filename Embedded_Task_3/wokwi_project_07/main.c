#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pico/stdlib.h"

int main() {
    stdio_init_all();

    const uint LED = 15;
    const uint BUTTON = 14;

    gpio_init(LED);
    gpio_set_dir(LED, GPIO_OUT);

    gpio_init(BUTTON);
    gpio_set_dir(BUTTON, GPIO_IN);
    gpio_pull_down(BUTTON);

    while (true) {
        printf("Get ready...\n");

        // Generate random delay between 1 and 4 seconds
        srand(time_us_32());
        int delay_ms = 1000 + (rand() % 3000);  
        
        // Watch for cheating
        for (int i = 0; i < delay_ms; i += 10) {
            if (gpio_get(BUTTON)) {
                printf("Too early! You pressed before the signal!\n");
                sleep_ms(2000);
                goto NEXT_ROUND; // restart game
            }
            sleep_ms(10);
        }

        // Turn LED ON → start reaction timer
        gpio_put(LED, 1);
        absolute_time_t start = get_absolute_time();

        // Wait for button press
        while (!gpio_get(BUTTON)) {
            // just wait
        }

        // Stop timer
        absolute_time_t end = get_absolute_time();
        int reaction_time = absolute_time_diff_us(start, end) / 1000;  // convert to ms

        printf("Your reaction time: %d ms\n", reaction_time);

        // Turn LED off and restart after delay
        sleep_ms(2000);

    NEXT_ROUND:
        gpio_put(LED, 0);
        sleep_ms(1500);
    }
}
