import random

def print_board(board):
    for i in range(9):
        if i % 3 == 0 and i != 0:
            print("- - - - - - - - - - - -")

        for j in range(9):
            if j % 3 == 0 and j != 0:
                print(" | ", end="")

            if j == 8:
                print(board[i][j])
            else:
                print(str(board[i][j]) + " ", end="")

def is_valid(board, row, col, num):
    # Check if the number is already in the current row
    if num in board[row]:
        return False
    
    # Check if the number is already in the current column
    for i in range(9):
        if board[i][col] == num:
            return False
    
    # Check if the number is already in the current 3x3 grid
    start_row = row - row % 3
    start_col = col - col % 3
    for i in range(3):
        for j in range(3):
            if board[i + start_row][j + start_col] == num:
                return False
    
    return True

def solve_sudoku(board):
    empty_cell = find_empty_cell(board)
    if not empty_cell:
        return True
    
    row, col = empty_cell
    
    for num in range(1, 10):
        if is_valid(board, row, col, num):
            board[row][col] = num
            
            if solve_sudoku(board):
                return True
            
            board[row][col] = 0
    
    return False

def find_empty_cell(board):
    for i in range(9):
        for j in range(9):
            if board[i][j] == 0:
                return (i, j)
    return None

def generate_sudoku():
    board = [[0 for _ in range(9)] for _ in range(9)]
    solve_sudoku(board)
    # Remove some numbers to create a puzzle
    for _ in range(45):  # Adjust the number of empty cells for desired difficulty
        row = random.randint(0, 8)
        col = random.randint(0, 8)
        board[row][col] = 0
    return board

if __name__ == "__main__":
    sudoku_board = generate_sudoku()
    print("Generated Sudoku Puzzle:")
    print_board(sudoku_board)
