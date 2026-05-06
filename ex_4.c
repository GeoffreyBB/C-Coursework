/***********************************************************************************************************************
Student name: Geoffrey Baum
Student ID: 345184378
Exercise name: ex_4 (exercise 4)
***********************************************************************************************************************/
#include <stdio.h>

#define ROWS 4
#define COLUMNS 4
#define LAYERS 4

char playerX = 'X';
char playerO = 'O';

char board[ROWS][COLUMNS][LAYERS];

void resetBoard(); int freeSpaces(); void printBoard(); int userInput(); char checkWinner(); char userReplay();

int main() {
    printf("Would you like to start? (y/n)\n");
    char userEnter, winner;
    int tie, valid;
    scanf("%c", &userEnter);

    //tried switching to switch cases, but it messed up with certain inputs.
    //if the user doesn't want to continue the program exits
    if(userEnter == 'n'){
        printf("YEET");
        return 0;
    //user wants to continue the program forwards them on to the next functions.
    }else{
        resetBoard();
        //valid checks if the input was correct
        valid = userInput();
        if(valid == 1){
            //tie checks if there are empty spaces (i.e. winning board), or if the board is filled and resulting a tie.
            tie = freeSpaces();
            if(tie == 0){
                //winner checks the board to see where there is 4 identical symbols consecutively and prints the winner.
                winner = checkWinner();
                if(winner == 'X'){
                    printf("X is the winner.\n");

                }else{
                    printf("O is the winner.\n");
                }
                //prints the game board and forwards the user on to a new game.
                printBoard();
                userReplay();
            }else{
                printBoard();
                userReplay();
            }
        //if valid=0 there was an input error and forwards the user to a new game.
        }else{
            printf("Input incorrect.\n");
            userEnter = getchar();
            printf("Would you like to continue? (y/n)\n");
            if(userEnter == 'y'){
                userReplay();
            }else{
                printf("YEET");
                return 0;
            }
        }
    }
}

/***********************************************************************************************************************
Function name: userReplay
The Input: none
The Output: prints basic lines (like continuing playing, winner, etc.) that is a result of other functions.
The Function operation: after one play of the input the user receives the option to continue playing. If the user
 responds in the affirmative userReplay goes through the necessary functions resulting in game progression and the
 printing of the game board.
***********************************************************************************************************************/
char userReplay(){
    char userEnter = 0, winner;
    int tie, valid;

    printf("Would you like to continue? (y/n)\n");
    scanf("%c", &userEnter);

    //user wants to continue the program forwards them on to the next functions.
    if(userEnter == 'y'){
        resetBoard();
        //valid checks if the input was correct
        valid = userInput();
        if(valid == 1){
            //tie checks if there are empty spaces (i.e. winning board), or if the board is filled and resulting a tie.
            tie = freeSpaces();
            if(tie == 0){
                //winner checks the board to see where there is 4 identical symbols consecutively and prints the winner.
                winner = checkWinner();
                if(winner == 'X'){
                    printf("X is the winner.\n");
                }else{
                    printf("O is the winner.\n");
                }
                //prints the game board and forwards the user on to a new game.
                printBoard();
                userReplay();
            }else{
                printBoard();
                userReplay();
            }
        //if valid=0 there was an input error and forwards the user to a new game.
        }else{
            printf("Input incorrect.\n");
            userReplay();
        }
    //if the user doesn't want to continue the program exits
    }else if(userEnter == 'n'){
        printf("YEET");
        return 0;
    }
}

/***********************************************************************************************************************
Function name: resetBoard
The Input: none
The Output: none
The Function operation: After each play (which results in an X win, O win, tie, or incorrect input) the user has the
 choice to play again, which needs a new and clean board. Here the function resets every space in the board to its
 predetermined empty value of *.
***********************************************************************************************************************/
void resetBoard(){
    //iterating through each axis (x, y, & z) and resetting it to '*'
    for(int i = 0; i < COLUMNS; i++){
        for(int j = 0; j < LAYERS; j++){
            for(int k = 0; k < ROWS; k++){
                board[i][j][k] = '*';
            }
        }
    }
}

/***********************************************************************************************************************
Function name: userInput
The Input: Whatever the user inputs.
The Output: 0 or 1, dictating if the user input was valid or not.
The Function operation: The function breaks down the code character by character checking each value. It saves each
 value as and integer represented as x, y, or z, then checks if that space (x,y,z) is empty on the board and fills it in
 with the designated symbol (every 3 integer inputs the function checks the validity adds it to the board and checks the
 next 3 integer inputs as the other player). Once the numbers run out the returns the validity to the main which
 preforms the necessary functions next.
***********************************************************************************************************************/
int userInput(){

    printf("Please enter your game sequence.\n");
    int x, y, z;
    //spaceFiller clears the spaces in between the number co-ordinates.
    int spaceFiller;

    scanf("%d", &x);
    while(x != '\n'){
        //each "if" checks if the variable is less than 4 and therefore a co-ordinate in the array (on the board).
        if(x < 4){
            spaceFiller = getchar();
            y = getchar() - 48;
            if(y < 4){
                spaceFiller = getchar();
                z = getchar() - 48;
                if(z < 4){
                    //checking if the (x,y,z) co-ordinate is filled, if not it fills it with 'X'.
                    if(board[x][y][z] != '*'){
                        return 0;
                    }else{
                        board[x][y][z] = playerX;
                    }
                }else{
                    return 0;
                }
            }else{
                return 0;
            }
        }else{
            return 0;
        }
        //clearing the space in between numbers, if the char != a space then it's the end of an input string and breaks.
        spaceFiller = getchar();
        if(spaceFiller != 32){
            break;
        }
        //preparing the variables for the next co-ordinate input.
        x = 0, y = 0, z = 0;
        scanf("%d", &x);
        //each "if" checks if the variable is less than 4 and therefore a co-ordinate in the array (on the board).
        if(x < 4){
            spaceFiller = getchar();
            y = getchar() - 48;
            if(y < 4){
                spaceFiller = getchar();
                z = getchar() - 48;
                if(z < 4){
                    //checking if the (x,y,z) co-ordinate is filled, if not it fills it with 'O'.
                    if(board[x][y][z] != '*'){
                        return 0;
                    }else{
                        board[x][y][z] = playerO;
                    }
                }else{
                    return 0;
                }
            }else{
                return 0;
            }
        }else{
            return 0;
        }
        //clearing the space in between numbers, if the char != a space then it's the end of an input string and breaks.
        spaceFiller = getchar();
        if(spaceFiller != 32){
            break;
        }
        //preparing the variables for the next co-ordinate input.
        x = 0, y = 0, z = 0;
        x = getchar() - 48;

    }
    //end of a co-ordinate input string, without input errors.
    return 1;
}

/***********************************************************************************************************************
Function name: printBoard
Input: none
Output: The board with each co-ordinate and if it is filled or not.
Function operation: Each print line goes through the the required co-ordinate on the board, prints the co-ordinate and
 what it is filled with (X, O, * -> i.e. empty).
***********************************************************************************************************************/
void printBoard(){

    //first layer of tic-tac-toe (x=0)
    printf("(0 0 0) (0 0 1) (0 0 2) (0 0 3) ");
    printf("%c %c %c %c\n", board [0][0][0], board [0][0][1], board [0][0][2], board [0][0][3]);
    printf("(0 1 0) (0 1 1) (0 1 2) (0 1 3) ");
    printf("%c %c %c %c\n", board [0][1][0], board [0][1][1], board [0][1][2], board [0][1][3]);
    printf("(0 2 0) (0 2 1) (0 2 2) (0 2 3) ");
    printf("%c %c %c %c\n", board [0][2][0], board [0][2][1], board [0][2][2], board [0][2][3]);
    printf("(0 3 0) (0 3 1) (0 3 2) (0 3 3) ");
    printf("%c %c %c %c\n\n", board [0][3][0], board [0][3][1], board [0][3][2], board [0][3][3]);

    //second layer of tic-tac-toe (x=1)
    printf("(1 0 0) (1 0 1) (1 0 2) (1 0 3) ");
    printf("%c %c %c %c\n", board [1][0][0], board [1][0][1], board [1][0][2], board [1][0][3]);
    printf("(1 1 0) (1 1 1) (1 1 2) (1 1 3) ");
    printf("%c %c %c %c\n", board [1][1][0], board [1][1][1], board [1][1][2], board [1][1][3]);
    printf("(1 2 0) (1 2 1) (1 2 2) (1 2 3) ");
    printf("%c %c %c %c\n", board [1][2][0], board [1][2][1], board [1][2][2], board [1][2][3]);
    printf("(1 3 0) (1 3 1) (1 3 2) (1 3 3) ");
    printf("%c %c %c %c\n\n", board [1][3][0], board [1][3][1], board [1][3][2], board [1][3][3]);

    //third layer of tic-tac-toe (x=2)
    printf("(2 0 0) (2 0 1) (2 0 2) (2 0 3) ");
    printf("%c %c %c %c\n", board [2][0][0], board [2][0][1], board [2][0][2], board [2][0][3]);
    printf("(2 1 0) (2 1 1) (2 1 2) (2 1 3) ");
    printf("%c %c %c %c\n", board [2][1][0], board [2][1][1], board [2][1][2], board [2][1][3]);
    printf("(2 2 0) (2 2 1) (2 2 2) (2 2 3) ");
    printf("%c %c %c %c\n", board [2][2][0], board [2][2][1], board [2][2][2], board [2][2][3]);
    printf("(2 3 0) (2 3 1) (2 3 2) (2 3 3) ");
    printf("%c %c %c %c\n\n", board [2][3][0], board [2][3][1], board [2][3][2], board [2][3][3]);

    //fourth layer of tic-tac-toe (x=3)
    printf("(3 0 0) (3 0 1) (3 0 2) (3 0 3) ");
    printf("%c %c %c %c\n", board [3][0][0], board [3][0][1], board [3][0][2], board [3][0][3]);
    printf("(3 1 0) (3 1 1) (3 1 2) (3 1 3) ");
    printf("%c %c %c %c\n", board [3][1][0], board [3][1][1], board [3][1][2], board [3][1][3]);
    printf("(3 2 0) (3 2 1) (3 2 2) (3 2 3) ");
    printf("%c %c %c %c\n", board [3][2][0], board [3][2][1], board [3][2][2], board [3][2][3]);
    printf("(3 3 0) (3 3 1) (3 3 2) (3 3 3) ");
    printf("%c %c %c %c\n\n", board [3][3][0], board [3][3][1], board [3][3][2], board [3][3][3]);
}

/***********************************************************************************************************************
Function name: freeSpaces
The Input: none
The Output: 0 or 1, dictating if there aren't  any empty spaces left over resulting in a tie. (0 is a tie, 1 is a winner
 or an invalid input.)
The Function operation: checks every space on the board (array) and for every space that isn't equal to * the variable
 emptySpaces (64 total spaces, 16 spaces per plane X 4 planes) is reduced by 1 until it reaches 0. Once it reaches 0 the
 function prints tie, returns 0 to the main, and proceeds with the users further input.
***********************************************************************************************************************/
int freeSpaces(){
    int emptySpaces = 64;

    //coding style says no counters in for loops, here its checking for empty spaces, and a number, not a T or F value
    //of consecutive symbols. Couldn't figure out a way to track that without a counter.
    for (int x = 0; x < 4; x++){
        for (int y = 0; y < 4; y++){
            for (int z = 0; z < 4; z++){
                if(board[x][y][z] != '*'){
                    emptySpaces--;
                }
            }
        }
    }
    //if emptySpaces = 0 then the game ends in a tie
    if(emptySpaces == 0){
        printf("Tie.\n");
        return 1;
    }else{
        return 0;
    }
}

/***********************************************************************************************************************
Function name: checkWinner
The Input: none
The Output: the symbol of the board space from the winner string.
The Function operation: goes through each possible win sequence and checks if there is a win there. Possible win
 sequences are broken up into straight lines on each axis (3 total, one for each axis), diagonals on each axis (6 total,
 2 each, one symmetrical, and one asymmetrical), and finally corner to corner crossing the whole cube (4 total, one for
 each corner).
***********************************************************************************************************************/
char checkWinner(){

    //first three are checking for straight line wins on each axis
    //x-axis
    for(int i = 0; i < COLUMNS; i++){
        for(int j = 0; j < LAYERS; j++){
            int k = 0;
            if(board[i][j][k] != '*' && board[i][j][k] == board[i][j][k + 1] && board[i][j][k]
            == board[i][j][k + 2 && board[i][j][k] == board[i][j][k + 3]]){
                return board[i][j][k];
            }
        }
    }

    //y-axis
    for(int j = 0; j < LAYERS; j++){
        for(int k = 0; k < ROWS; k++){
            int i = 0;
            if(board[i][j][k] != '*' && board[i][j][k] == board[i + 1][j][k] && board[i][j][k]
            == board[i + 2][j][k] && board[i][j][k] == board[i + 3][j][k]){
                return board[i][j][k];
            }

        }
    }

    //z-axis
    for(int k = 0; k < ROWS; k++){
        for(int i = 0; i < COLUMNS; i++){
            int j = 0;
            if (board[i][j][k] != '*' && board[i][j][k] == board[i][j + 1][k] && board[i][j][k]
            == board[i][j + 2][k] && board[i][j][k] == board[i][j + 3][k]){
                return board[i][j][k];
            }
        }
    }

    //checking for diagonal wins on each axis
    //note: symmetrical means the other 2 variables (the ones excluding the axis) equal the same.
    //asymmetrical means the other 2 variables equal 3 when added together (i.e modulo opposites).

    //symmetrical diagonals on the x-axis
    for(int i = 0; i < COLUMNS; i++){
        int j = 0;
        int k = 0;
        if(board[i][j][k] != '*' && board[i][j][k] == board[i][j + 1][k + 1] && board[i][j][k]
        == board[i][j + 2][k + 2] && board[i][j][k] == board[i][j + 3][k + 3]){
            return board[i][j][k];
        }
    }

    //asymmetrical diagonals on x-axis
    for(int i = 0; i < COLUMNS; i++){
        int j = 0;
        int k = 3;
        if(board[i][j][k] != '*' && board[i][j][k] == board[i][j + 1][k - 1] && board[i][j][k]
        == board[i][j + 2][k - 2] && board[i][j][k] == board[i][j + 3][k - 3]){
            return board[i][j][k];
        }
    }

    //symmetrical diagonals on y-axis
    for(int j = 0; j < LAYERS; j++){
        int i = 0;
        int k = 0;
        if(board[i][j][k] != '*' && board[i][j][k] == board[i + 1][j][k + 1] && board[i][j][k]
        == board[i + 2][j][k + 2] && board[i][j][k] == board[i + 3][j][k + 3]){
            return board[i][j][i];
        }
    }

    //asymmetrical diagonals y-axis
    for(int j = 0; j < LAYERS; j++){
        int i = 3;
        int k = 0;
        if(board[i][j][k] != '*' && board[i][j][k] == board[i - 1][j][k + 1] && board[i][j][k]
        == board[i - 2][j][k + 2] && board[i][j][k] == board[i - 3][j][k + 3]){
            return board[i][j][k];
        }
    }

    //symmetrical diagonals z-axis
    for(int k = 0; k < ROWS; k++){
        int i = 0;
        int j = 0;
        if(board[i][j][k] != '*' && board[i][j][k] == board[i + 1][j + 1][k] && board[i][j][k]
        == board[i + 2][j + 2][k] && board[i][j][k] == board[i + 3][j + 3][k]){
            return board[i][j][k];
        }
    }

    //asymmetrical diagonal on z-axis
    for(int k = 0; k < ROWS; k++){
        int i = 3;
        int j = 0;
        if(board[i][j][k] != '*' && board[i][j][k] == board[i - 1][j + 1][k] && board[i][j][k]
        == board[i - 2][j + 2][k] && board[i][j][k] == board[i - 3][j + 3][k]){
            return board[i][j][k];
        }
    }

    //checking cross-plane corner to corner diagonals
    //checking from (0,0,0)
    for(int j = 0; j < LAYERS; j++){
        int i = 0, k = 0;
        if(board[i][j][k] != '*' && board[i][j][k] == board[i + 1][j + 1][k + 1] && board[i][j][k]
        == board[i + 2][j + 2][k + 2] && board[i][j][k] == board[i + 3][j + 3][k + 3]){
            return board[i][j][k];
        }
    }

    //checking from (3,0,0)
    for(int j = 0; j < LAYERS; j++){
        int i = 3, k = 0;
        if(board[i][j][k] != '*' && board[i][j][k] == board[i - 1][j + 1][k + 1] && board[i][j][k]
        == board[i - 2][j + 2][k + 2] && board[i][j][k] == board[i - 3][j + 3][k + 3]){
            return board[i][j][k];
        }
    }

    //checking from (0,0,3)
    for(int j = 0; j < LAYERS; j++){
        int i = 0, k = 3;
        if(board[i][j][k] != '*' && board[i][j][k] == board[i + 1][j + 1][k - 1] && board[i][j][k]
        == board[i + 2][j + 2][k - 2] && board[i][j][k] == board[i + 3][j + 3][k - 3]){
            return board[i][j][k];
        }
    }

    //checking from (3,0,3)
    for(int j = 0; j < LAYERS; j++){
        int i = 3, k = 3;
        if(board[i][j][k] != '*' && board[i][j][k] == board[i - 1][j + 1][k - 1] && board[i][j][k]
        == board[i - 2][j + 2][k - 2] && board[i][j][k] == board[i - 3][j + 3][k - 3]){
            return board[i][j][k];
        }
    }
}