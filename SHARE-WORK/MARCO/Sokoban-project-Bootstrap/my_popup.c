#include <string.h>
#include <stdio.h>
#include "display_popup.h"

int main(int argc, char *argv[]) {
    // Check if a message is provided as a command-line argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <message>\n", argv[0]);
        return 1;
    }

    // Display the popup with the provided message
    display_popup(argv[1]);

    return 0;
}

