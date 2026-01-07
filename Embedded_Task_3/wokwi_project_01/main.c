#include <stdio.h>
#include "pico/stdlib.h"

int main() {
    stdio_init_all();  // start serial communication

    for (int i = 0; i < 10; i++) {
        printf("%d\n", i);  // This is use to print the number
        sleep_ms(500);      // this is used to make a delay of 0.5 second for every new number printed
    }

    return 0;
}
