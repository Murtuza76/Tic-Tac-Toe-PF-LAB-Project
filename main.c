#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printGuide() {
    printf("HOW TO PLAY:\n");
    printf("\n--- POSITION GUIDE ---\n");
    printf(" 1 | 2 | 3 \n");
    printf("---|---|---\n");
    printf(" 4 | 5 | 6 \n");
    printf("---|---|---\n");
    printf(" 7 | 8 | 9 \n");
    printf("----------------------\n\n");
}

// for printing the board
void printBoard(char board[3][3]) {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|"); 
        }
        printf("\n");
        if (i < 2) printf("---|---|---\n");
    }
    printf("\n");
}

// checking if someone won team "X" or team "O"
int checkWin(char board[3][3], char player) {
    // checking rows and columns
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return 1; // returning 1 means someone won, will be useful later
        }
    }
    // checking diagonals asw
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return 1;
    }
    return 0; // no one won, used to identify a tie
}

// how the ai will move
void computerMove(char board[3][3]) {
    int index, row, col;
    
    do {
        index = rand() % 9;
        row = index / 3;
        col = index % 3;
    } while (board[row][col] != '_'); 
    
    board[row][col] = 'O';
    printf("Computer chose position %d\n", index + 1);
}

// player vs comp function
void playVsComputer(char board[3][3]) {
    int turns = 0;
    
    // initializing array with "_"
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = '_';
        }
    }

    while (turns < 9) {
        printBoard(board);

        int choice;
        printf("Your turn (1-9): ");
        scanf("%d", &choice);
        
        int index = choice - 1;
        int row = index / 3;
        int col = index % 3;

        // check to see if the spot is taken
        if (choice < 1 || choice > 9 || board[row][col] != '_') {
            printf("Invalid move or spot already taken! Try again.\n");
            continue; 
        }

        board[row][col] = 'X';
        turns++;

        // Check if 'X' won
        if (checkWin(board, 'X')) {
            printBoard(board);
            printf("Congrats! You win!\n");
            return;
        }

        if (turns == 9) break; // Tie game
        
        // Computer's turn  
        computerMove(board);
        turns++;

        // Check if computer won
        if (checkWin(board, 'O')) {
            printBoard(board);
            printf("Computer wins! Better luck next time.\n");
            return;
        }
    }

    printBoard(board);
    printf("It's a tie!\n");
}

void playvsplay(char board[3][3]){
    int turns = 0;
    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            board[i][j] = '_';
        }
    }
     while(turns<9){
//player 1's turn
        printBoard(board);
        int choice1, row1, col1;

        while(1) {
            printf("Player 1's turn (1-9): ");
            scanf("%d", &choice1);

        // valid checks
            if (choice1 < 1 || choice1 > 9) {
                printf("Invalid choice! Please enter a number between 1 and 9.\n");
                continue;
            }

            int index1 = choice1 - 1;
            row1 = index1 / 3;
            col1 = index1 % 3;

            // Check if spot is already taken
            if (board[row1][col1] != '_') {
                printf("Spot already taken! Choose an empty spot.\n");
                continue;
            }
            break;
        }

        board[row1][col1] = 'X';
        turns++;

        // Check if Player 1 won
        if (checkWin(board, 'X')) {
            printBoard(board);
            printf("Player 1 Wins!\n");
            return;
        }

        // Check for tie
        if (turns == 9) {
            printBoard(board);
            printf("It's a tie!\n");
            return;
        }

        // Player 2's turn
        printBoard(board); // Print board after Player 1's move so Player 2 can see it
        int choice2, row2, col2;

        while(1) {
            printf("Player 2's turn (1-9): ");
            scanf("%d", &choice2);

            // validation check
            if (choice2 < 1 || choice2 > 9) {
                printf("Invalid choice! Please enter a number between 1 and 9.\n");
                continue;
            }

            int index2 = choice2 - 1;
            row2 = index2 / 3;
            col2 = index2 % 3;

            // Check if spot is already taken
            if (board[row2][col2] != '_') {
                printf("Spot already taken! Choose an empty spot.\n");
                continue;
            }
            break; // Valid move, exit Player 2's input loop
        }

        board[row2][col2] = 'O';
        turns++;

        // Check if Player 2 won
        if (checkWin(board, 'O')) {
            printBoard(board);
            printf("Player 2 wins!\n");
            return;
        }
    }

    printBoard(board);
    printf("It's a tie!\n");
     }

int main() {
    srand(time(0));
    char board[3][3];
    int input;

    printGuide();

    do {
        printf("\n-- Tic Tac Toe --\n");
        printf("1. Player vs Player\n");
        printf("2. Player vs Computer\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &input);

        switch(input) {
            case 1:
                playvsplay(board);
                break;
            case 2:
                playVsComputer(board);
                break;
            case 3:
                printf("\nExiting.\n");
                break;
            default:
                printf("\nInvalid choice! Enter 1, 2, or 3.\n");
        }
    } while(input != 3);

    return 0;
}