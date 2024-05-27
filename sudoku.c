#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 9

void print_board(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        if (i % 3 == 0 && i != 0) {
            printf("- - - - - - - - - - - -\n");
        }

        for (int j = 0; j < SIZE; j++) {
            if (j % 3 == 0 && j != 0) {
                printf(" | ");
            }

            if (j == SIZE - 1) {
                printf("%c\n", board[i][j]);
            } else {
                printf("%c ", board[i][j]);
            }
        }
    }
}

int is_valid(char board[SIZE][SIZE], int row, int col, char num) {
    for (int i = 0; i < SIZE; i++) {
        if (board[row][i] == num) {
            return 0;
        }
    }

    for (int i = 0; i < SIZE; i++) {
        if (board[i][col] == num) {
            return 0;
        }
    }

    int start_row = row - row % 3;
    int start_col = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + start_row][j + start_col] == num) {
                return 0;
            }
        }
    }

    return 1;
}

int find_empty_cell(char board[SIZE][SIZE], int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == '_') {
                *row = i;
                *col = j;
                return 1;
            }
        }
    }
    return 0;
}

int solve_sudoku(char board[SIZE][SIZE]) {
    int row, col;

    if (!find_empty_cell(board, &row, &col)) {
        return 1;
    }

    for (char num = '1'; num <= '9'; num++) {
        if (is_valid(board, row, col, num)) {
            board[row][col] = num;

            if (solve_sudoku(board)) {
                return 1;
            }

            board[row][col] = '_';
        }
    }

    return 0;
}

void generate_sudoku(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = '_';
        }
    }

    solve_sudoku(board);

    for (int i = 0; i < 45; i++) {
        int row = rand() % SIZE;
        int col = rand() % SIZE;
        board[row][col] = '_';
    }
}

void play_sudoku(char board[SIZE][SIZE]) {
    int row, col;
    char num;

    while (1) {
        printf("Enter row (1-9), column (1-9), and number (1-9) separated by spaces (enter 0 0 0 to exit): ");
        scanf("%d %d %c", &row, &col, &num);

        if (row == 0 && col == 0 && num == '0') {
            break;
        }

        row -= 1;
        col -= 1;

        if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && num >= '1' && num <= '9') {
            if (board[row][col] == '_') {
                if (is_valid(board, row, col, num)) {
                    board[row][col] = num;
                    print_board(board);
                } else {
                    printf("Invalid move!\n");
                }
            } else {
                printf("Cell is already filled!\n");
            }
        } else {
            printf("Invalid input!\n");
        }
    }
}

int main() {
    srand(time(0));

    char sudoku_board[SIZE][SIZE];
    generate_sudoku(sudoku_board);

    printf("Generated Sudoku Puzzle:\n");
    print_board(sudoku_board);

    play_sudoku(sudoku_board);

    return 0;
}
