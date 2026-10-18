# Tic Tac Toe in C

A simple command-line Tic Tac Toe game written in C. Play against a friend or against the computer.

## Features

- Two modes: **Player vs Player** and **Player vs Computer**
- Computer opponent that wins when it can, blocks your winning move, and prefers the centre and corners
- Input validation (rejects letters, out-of-range numbers and already-taken cells)
- Score tracking across multiple rounds (X wins, O wins, draws)
- Custom player names
- Play again without restarting the program

## Requirements

- A C compiler such as `gcc` or `clang`
- Works on Linux, macOS and Windows (MinGW / WSL)

## Build and Run

```bash
gcc tictactoe.c -o tictactoe
./tictactoe
```

On Windows (MinGW):

```bash
gcc tictactoe.c -o tictactoe.exe
tictactoe.exe
```

## How to Play

The board cells are numbered 1 to 9:

```
     1 | 2 | 3
    ---+---+---
     4 | 5 | 6
    ---+---+---
     7 | 8 | 9
```

1. Choose a mode (1 = two players, 2 = vs computer).
2. Enter player name(s).
3. On your turn, type the number of the cell where you want to place your mark and press Enter.
4. Get three marks in a row (horizontal, vertical or diagonal) to win.
5. If all nine cells fill up with no winner, the game is a draw.
6. After each round, enter `y` to play again or `n` to quit.

## Sample Output

```
=====================================
         TIC  TAC  TOE  (C)
=====================================
  1. Player vs Player
  2. Player vs Computer
Select mode (1 or 2): 2
Enter name for X: Deval

     1 | 2 | 3
    ---+---+---
     4 | 5 | 6
    ---+---+---
     7 | 8 | 9

Deval (X), choose a cell (1-9): 5
```

## Project Structure

```
tictactoe/
├── tictactoe.c   # Game source code
└── README.md     # This file
```

## How the Code Works

| Function | Purpose |
|----------|---------|
| `resetBoard()` | Fills the board with the numbers 1-9 |
| `printBoard()` | Draws the current board |
| `checkWinner()` | Checks rows, columns and both diagonals |
| `isDraw()` | Returns true when no free cells remain |
| `getHumanMove()` | Reads and validates a move from the player |
| `getComputerMove()` | Picks a move: win, block, centre, corner, then random |
| `playGame()` | Runs one full round and returns the result |

## Possible Improvements

- Unbeatable computer using the Minimax algorithm
- Larger boards (4x4, 5x5)
- Colored output using ANSI escape codes

## License

Free to use and modify for learning purposes.
