/*
 * Tic Tac Toe in C
 * Modes: Player vs Player, Player vs Computer
 * Compile: gcc tictactoe.c -o tictactoe
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 3

char board[SIZE][SIZE];

/* ---------- Board helpers ---------- */

void resetBoard(void) {
    char c = '1';
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = c++;
}

void printBoard(void) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        printf("     %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
        if (i < SIZE - 1)
            printf("    ---+---+---\n");
    }
    printf("\n");
}

int isCellFree(int pos) {           /* pos is 1..9 */
    int r = (pos - 1) / SIZE;
    int c = (pos - 1) % SIZE;
    return board[r][c] != 'X' && board[r][c] != 'O';
}

void placeMark(int pos, char mark) {
    board[(pos - 1) / SIZE][(pos - 1) % SIZE] = mark;
}

void removeMark(int pos) {          /* used by the AI when testing moves */
    board[(pos - 1) / SIZE][(pos - 1) % SIZE] = (char)('0' + pos);
}

/* Returns 'X' or 'O' if that player has won, otherwise 0 */
char checkWinner(void) {
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return board[i][0];
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return board[0][i];
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return board[0][2];
    return 0;
}

int isDraw(void) {
    for (int pos = 1; pos <= 9; pos++)
        if (isCellFree(pos))
            return 0;
    return 1;
}

/* ---------- Input ---------- */

int readInt(const char *prompt) {
    char line[64];
    int value;
    while (1) {
        printf("%s", prompt);
        if (!fgets(line, sizeof line, stdin)) {
            printf("\nInput closed. Exiting.\n");
            exit(0);
        }
        if (sscanf(line, "%d", &value) == 1)
            return value;
        printf("  Please enter a number.\n");
    }
}

int getHumanMove(const char *name, char mark) {
    char prompt[64];
    snprintf(prompt, sizeof prompt, "%s (%c), choose a cell (1-9): ", name, mark);
    while (1) {
        int pos = readInt(prompt);
        if (pos < 1 || pos > 9)
            printf("  Invalid! Pick a number from 1 to 9.\n");
        else if (!isCellFree(pos))
            printf("  That cell is already taken. Try another.\n");
        else
            return pos;
    }
}

/* ---------- Computer player ---------- */

/* Try every free cell; return the one where `mark` wins immediately, or 0 */
int findWinningMove(char mark) {
    for (int pos = 1; pos <= 9; pos++) {
        if (!isCellFree(pos)) continue;
        placeMark(pos, mark);
        char w = checkWinner();
        removeMark(pos);
        if (w == mark) return pos;
    }
    return 0;
}

int getComputerMove(char me, char opponent) {
    int pos;

    if ((pos = findWinningMove(me)) != 0)        return pos;  /* 1. win        */
    if ((pos = findWinningMove(opponent)) != 0)  return pos;  /* 2. block      */
    if (isCellFree(5))                           return 5;    /* 3. centre     */

    int corners[] = {1, 3, 7, 9};                             /* 4. corners    */
    int free_corners[4], n = 0;
    for (int i = 0; i < 4; i++)
        if (isCellFree(corners[i])) free_corners[n++] = corners[i];
    if (n > 0) return free_corners[rand() % n];

    do { pos = rand() % 9 + 1; } while (!isCellFree(pos));    /* 5. any cell   */
    return pos;
}

/* ---------- Game loop ---------- */

/* Returns 'X', 'O' or 'D' (draw) */
char playGame(int vsComputer, const char *name1, const char *name2) {
    char current = 'X';
    resetBoard();

    while (1) {
        printBoard();

        int pos;
        if (current == 'X') {
            pos = getHumanMove(name1, 'X');
        } else if (vsComputer) {
            pos = getComputerMove('O', 'X');
            printf("%s (O) chooses cell %d\n", name2, pos);
        } else {
            pos = getHumanMove(name2, 'O');
        }

        placeMark(pos, current);

        char winner = checkWinner();
        if (winner) {
            printBoard();
            return winner;
        }
        if (isDraw()) {
            printBoard();
            return 'D';
        }
        current = (current == 'X') ? 'O' : 'X';
    }
}

void readName(const char *prompt, char *dest, size_t size) {
    printf("%s", prompt);
    if (!fgets(dest, (int)size, stdin)) {
        dest[0] = '\0';
    }
    dest[strcspn(dest, "\n")] = '\0';
}

int main(void) {
    srand((unsigned)time(NULL));

    char name1[32] = "Player 1";
    char name2[32] = "Player 2";
    int scoreX = 0, scoreO = 0, draws = 0;

    printf("=====================================\n");
    printf("         TIC  TAC  TOE  (C)\n");
    printf("=====================================\n");
    printf("  1. Player vs Player\n");
    printf("  2. Player vs Computer\n");

    int mode;
    do {
        mode = readInt("Select mode (1 or 2): ");
    } while (mode != 1 && mode != 2);

    int vsComputer = (mode == 2);

    char tmp[32];
    readName("Enter name for X: ", tmp, sizeof tmp);
    if (tmp[0]) strcpy(name1, tmp);

    if (vsComputer) {
        strcpy(name2, "Computer");
    } else {
        readName("Enter name for O: ", tmp, sizeof tmp);
        if (tmp[0]) strcpy(name2, tmp);
    }

    char again = 'y';
    while (again == 'y' || again == 'Y') {
        char result = playGame(vsComputer, name1, name2);

        if (result == 'X') {
            printf("*** %s (X) wins! ***\n", name1);
            scoreX++;
        } else if (result == 'O') {
            printf("*** %s (O) wins! ***\n", name2);
            scoreO++;
        } else {
            printf("*** It's a draw! ***\n");
            draws++;
        }

        printf("\nScore -> %s: %d | %s: %d | Draws: %d\n",
               name1, scoreX, name2, scoreO, draws);

        printf("Play again? (y/n): ");
        char line[16];
        if (!fgets(line, sizeof line, stdin)) break;
        again = line[0];
    }

    printf("\nThanks for playing!\n");
    return 0;
}
