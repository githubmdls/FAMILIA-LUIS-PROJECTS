#include "my.h"
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int i = 1;
    int x;
    int y;
    int fd = 0;
    char *BUFFER[10000];

    initscr();
    getmaxyx(stdscr, y, x);
    fd = open(argv[1], O_RDONLY);
    int size = read(fd, BUFFER, 1000);
    printw("%s", BUFFER);
    refresh();
    getch();
    endwin();
    return 0;
}

int my_strlen(char const *str)
{
    int nb = 0;

    while (str[nb] != '\0') {
        nb = nb + 1;
    }
    return nb;
}

