#include <ncurses.h>
#include <string.h>

#include "display_popup.h"


void display_popup(const char *message) {
    // Initialize ncurses
    initscr();          // Start curses mode

    // Get the dimensions of the terminal window
    int height, width;
    getmaxyx(stdscr, height, width);

    // Calculate the center position
    int x = (width - strlen(message)) / 2;
    int y = height / 2;

    // Print the message at the center of the screen
    mvprintw(y, x, "%s", message);

    // Refresh the screen to display the text
    refresh();

    // Wait for a key press
    getch();

    // End ncurses
    endwin();           // End curses mode
}

