/**
 * fifteen.c
 *
 * Refer to Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to boardDimension x boardDimension).
 *
 * Usage: fifteen boardDimension
 *
 * whereby the board's dimensions are to be boardDimension x boardDimension,
 * where boardDimension must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

#ifndef INT_MAX
#define INT_MAX 12345678
#endif // INT_MAX

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int boardDimension;

// prototypes
void greet(void);

void initBoard(void);

void draw(void);

short move(int tile);

short won(void);

int get_int();

void easySleep(double d);

int main(int argc, char *argv[]) {
    // ensure proper usage
    if (argc != 2) {
        printf("Usage: <PROGRAM> X by X where X is greater than 2, and less than 10.\n");
        return 1;
    }

    // ensure valid dimensions
    boardDimension = atoi(argv[1]);
    if (boardDimension < DIM_MIN || boardDimension > DIM_MAX) {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
               DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL) {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    initBoard();

    // accept moves until game is won
    while (true) {
        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < boardDimension; i++) {
            for (int j = 0; j < boardDimension; j++) {
                fprintf(file, "%i", board[i][j]);
                if (j < boardDimension - 1) {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won()) {
            printf("\n");
            printf("Game Over!\n");
            printf("Result = 'WIN'\n");
            break;
        }
        {
            //prompt for move
            printf("Tile to move: ");
            int tile = get_int();
            printf("\n");

            // quit if user inputs 0 (for testing)
            if (tile == 0) {
                break;
            }

            // log move (for testing)
            fprintf(file, "%i\n", tile);
            fflush(file);

            // move if possible, else report illegality
            if (!move(tile)) {
                printf("\nIllegal move.\n");
                easySleep(0.5);
            }

            // sleep thread for animation's sake
            easySleep(0.5);
        }

        // close log
        fclose(file);

        // success
        return 0;
    }
}

void easySleep(double seconds) {
    double timeSeconds = seconds;
    double ttSleep = timeSeconds * 1000000;
    usleep((int) ttSleep);
}

/**
 * Get an non-negative integer from user input
 * If the input is not non-negative integer, return INT_MAX
 */
int get_int() {
    int input = 0;
    short invalid = 0;

    char c = getchar();
    if (c == '\n')
        return INT_MAX;

    while (c != '\n') {
        if ((c >= '0') && (c <= '9')) {
            input = input * 10 + (c - '0');
        } else {
            invalid = 1;
        }

        c = getchar();
    }

    if (invalid)
        return INT_MAX;
    else
        return input;
}

/**
 * Greets player.
 */
void greet(void) {
    printf("WELCOME TO GAME OF FIFTEEN\n");
    easySleep(2);
}

/**
 * Initializes the game's board with tiles numbered 1 through boardDimension*boardDimension - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void initBoard(void) {
    int boardDimSquared = boardDimension * boardDimension;
    int pointer = 0;
    for (int i = 0; i < boardDimension; i++) {
        for (int j = 0; j < boardDimension; ++j) {
            pointer++;
            board[i][j] = (boardDimSquared - pointer);
        }
    }
    if (((boardDimension % 2 == 0))) {
        int tempStorage = board[boardDimension - 1][boardDimension - 2];
        board[boardDimension - 1][boardDimension - 2] = board[boardDimension - 1][boardDimension - 3];
        board[boardDimension - 1][boardDimension - 3] = tempStorage;
    }
}

void draw(void) {
    /*
     * Make da board.
     */
    for (int i = 0; i < boardDimension; ++i) {
        for (int j = 0; j < boardDimension; ++j) {
            if (board[i][j] > 0) {
                printf((const char *) board[i][j]);
            } else {
                printf("__");
            }
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns 1, else
 * returns 0.
 */
short move(int tile) {
    int boardColumn; // X values (up and down)
    int boardRow; // Y values (right to left)

    for (int i = 0; i < boardDimension; ++i) {
        for (int j = 0; j < boardDimension; ++j) {
            if (tile == board[i][j]) {
                int nullSpace = 0;
                // Check if the tile the user picks is on a border (adjactent to blank).
                if (((boardColumn == (i - 1)) && (j == boardRow)) || ((boardColumn == (i + 1)) && (j == boardRow)) ||
                    ((i == boardColumn) && (boardRow == (j - 1))) || ((i == boardColumn) && (boardRow == (j + 1)))) {
                    //Tile is next to a border; so now we move the tiles.
                    board[boardColumn][boardRow] = tile;
                    //Set the currently selected tile to a 'null' space, a.k.a 0.
                    board[i][j] = nullSpace;
                    boardRow = j;
                    boardColumn = i;

                    return 1;
                } else {
                    perror("That's not a valid tile to be moved, try again.");
                    return 0;
                }
            }
        }
    }
    return 0;
}

/**
 * Returns 1 if game is won (i.e., board is in winning configuration),
 * else 0.
 */
short won(void) {
    int boardPointer = -1;
    for (int i = 0; i < boardDimension; ++i) {
        for (int j = 0; j < boardDimension; ++j) {
            boardPointer++;
            if (board[i][j] != boardPointer) {
                return 0;
            }
        }
    }
    printf("EZ Clap");
    return 1;
}

