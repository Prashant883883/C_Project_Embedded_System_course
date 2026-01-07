#include <stdio.h>
#include "pico/stdlib.h"
#include <string.h>

int main() {
    stdio_init_all();

    char name[50];      

    printf("Enter your name: ");
    scanf("%49s", name); 

    // Check if name is Clark Kent
    if (strcmp(name, "Clark") == 0 || strcmp(name, "Kent") == 0 || strcmp(name, "Clark_Kent") == 0) {
        printf("You are Superman!\n");
    } else {
        printf("You are an ordinary person.\n");
    }

    return 0;
}
