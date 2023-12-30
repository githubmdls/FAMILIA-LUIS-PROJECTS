#include <ncurses.h>
#include <stdlib.h>

#define MAX_ROWS 10
#define MAX_COLS 10
#define MAX_BOXES 5

char board[MAX_ROWS][MAX_COLS];
int playerRow, playerCol;
int boxCount;

typedef struct {
    int row;
    int col;
} Box;

Box boxes[MAX_BOXES];

void initializeBoard() {
    // Define the game board
    const char *map[] = {
        "##########",
        "#    P   #",
        "#   XO   #",
        "#   BX   #",
        "#   OX   #",
        "#   XX   #",
        "#        #",
        "#        #",
        "#        #",
        "##########"
    };

    // Copy the map to the board
    for (int i = 0; i < MAX_ROWS; ++i) {
        for (int j = 0; j < MAX_COLS; ++j) {
            board[i][j] = map[i][j];
            if (board[i][j] == 'P') {
                playerRow = i;
                playerCol = j;
            } else if (board[i][j] == 'B') {
                boxes[boxCount].row = i;
                boxes[boxCount].col = j;
                boxCount++;
            }
        }
    }
}

void displayBoard() {
    // Display the game board using ncurses
    clear();  // Clear the screen

    for (int i = 0; i < MAX_ROWS; ++i) {
        for (int j = 0; j < MAX_COLS; ++j) {
            mvaddch(i, j * 2, board[i][j] | A_BOLD);
        }
    }

    refresh();  // Refresh the screen
}

int movePlayer(int newRow, int newCol) {
    // Move the player on the board
    if (board[newRow][newCol] == ' ' || board[newRow][newCol] == 'O') {
        // Empty space or storage location, move the player
        board[playerRow][playerCol] = (board[playerRow][playerCol] == 'O') ? '.' : ' ';
        playerRow = newRow;
        playerCol = newCol;
        board[playerRow][playerCol] = 'P';
        return 1;  // Successful move
    } else if (board[newRow][newCol] == 'X') {
        // Box in front, check if we can move the box
        int boxRow = newRow + (newRow - playerRow);
        int boxCol = newCol + (newCol - playerCol);

        if (board[boxRow][boxCol] == ' ' || board[boxRow][boxCol] == 'O') {
            // Empty space or storage location, move the box and then the player
            board[boxRow][boxCol] = (board[boxRow][boxCol] == 'O') ? 'X' : ' ';
            board[playerRow][playerCol] = (board[playerRow][playerCol] == 'O') ? '.' : ' ';
            playerRow = newRow;
            playerCol = newCol;
            board[playerRow][playerCol] = 'P';
            return 1;  // Successful move
        }
    }

    return 0;  // Invalid move
}

int checkWinCondition() {
    for (int i = 0; i < boxCount; ++i) {
        if (board[boxes[i].row][boxes[i].col] != 'O') {
            return 0;  // Not all boxes are on storage locations
        }
    }
    return 1;  // All boxes are on storage locations
}

int main() {
    // Initialize ncurses
    initscr();
    cbreak();  // Disable line buffering
    noecho();  // Don't display input characters
    keypad(stdscr, TRUE);  // Enable special keys

    initializeBoard();

    while (1) {
        displayBoard();

        // Get user input
        int move = getch();

        // Update player position based on input
        int newRow = playerRow;
        int newCol = playerCol;

        switch (move) {
            case KEY_UP:
                newRow--;
                break;
            case KEY_DOWN:
                newRow++;
                break;
            case KEY_LEFT:
                newCol--;
                break;
            case KEY_RIGHT:
                newCol++;
                break;
            case 'q':
                // Quit the game
                endwin();  // End curses mode
                return 1;
        }

        // Try to move the player and update the board
        int result = movePlayer(newRow, newCol);

        if (result == 0) {
            // Invalid move, try again
            mvprintw(MAX_ROWS + 1, 0, "Invalid move!");
            refresh();
            getch();  // Wait for a key press
        }

        // Check win condition
        if (checkWinCondition()) {
            mvprintw(MAX_ROWS + 1, 0, "You win!");
            refresh();
            getch();  // Wait for a key press
            break;
        }
    }

    endwin();  // End curses mode
    return 0;
}

