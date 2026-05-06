#include <stdio.h>
#include <math.h>

int baseDec = 10;

int digitAppearance(int digitInt, int number, int rem, int appearance);
int greatestCD(int num1, int num2, char choice);
int logicCalculator(char choice);
int phraseCheck(char not, char insideOperand, char variable1, char variable2);

int main() {
    printf("Choose an option:\n \t1: Logical Statement Calculator\n \t2: Count digit in a number\n \t3: GCD Calculator\n"
           "\t4: Exit\n");
    char choice;
    scanf("%c", &choice);

    if(choice == 49){
        int valid = 3;
        choice = getchar();

        valid = logicCalculator(choice);

        /*if valid == 0 there was an error, == 1 it was T, == 2 it was F, then checks to see if there are more
        characters in the string.*/
        if(valid == 0){
            choice = getchar();
            if(choice == '\n'){
                main();
            }else{
                while (choice != ' '){
                    choice = getchar();
                }
                if (choice == ' '){
                    main();
                }
            }
        }else if(valid == 1){
            printf("The statement is true.\n");
            choice = getchar();
            if(choice == ' '){
                main();
            }else if(choice == '&' || choice == '|'){
                valid = logicCalculator(choice);
            }else{
                fflush(stdin);
                main();
            }
        }else{
            printf("The statement is false.\n");
            choice = getchar();
            if(choice == ' '){
                main();
            }else if(choice == '&' || choice == '|'){
                valid = logicCalculator(choice);
            }else{
                fflush(stdin);
                main();
            }
        }

    }else if(choice == 50){
        printf("\nEnter a number and a digit: ");
        int number, rem = 0, counter = 0, digitInt;
        char digit;
        scanf("%d %c", &number, &digit);
        if(digit < 48 || digit > 57){
            printf("You should stay positive, and so should your input.\n");
            main();
        }else{
            digitInt = digit - 48;
        }
        int appearance = 0;
        if(number < 0){
            printf("You should stay positive, and so should your input.\n");
            main();
        }else{
            counter = digitAppearance(digitInt, number, rem, appearance);
            printf("The digit %d appears %d times in the number %d\nֿ", digitInt, counter, number);
        }
        choice = getchar();
        if (choice == ' '){
            main();
        }
    }else if(choice == 51){
        printf("\nEnter two positive numbers: ");
        int num1, num2;
        scanf("%d %d",&num1, &num2);
        printf("GCD = %d\n", greatestCD(num1, num2, choice));
        choice = getchar();
        if(choice == '\n'){
            fflush(stdin);
            main();
        }else{
            main();
        }
    }else if(choice == 52){
        fflush(stdin);
        printf("So Long, and Thanks for All the Fish!");
        //no new line created, in submit it prints a new line
    }else if(choice == ' '){
        choice = getchar();
        if(choice != '\n'){
            main();
        }
    }else{
        printf("Fool of a Took!\nThis is a serious journey, not a hobbit walking-party.\n"
               "Throw yourself in next time, and then you will be no further nuisance.\n");
        choice = getchar();
        main();
    }

}

/***********************************************************************************************************************
Function name: digitAppearance
Input: int digit (the digit that the user inputs), int number (the number the user inputs), int rem (the remainder of
 the number modulu base 10).
Output: int appearance (the amount of times the digit appeared in the number).
Function operation: The function checks if the remainder of the number == digit, if so it adds 1 to the appearance
 counter, divides the number by 10, and then returns to the start of the function. If the remainder != digit
 digit then the number gets divided by 10, and returns to the function. In the case that the number == 0 then the
 function returns int appearance, and takes on the form of int counter in the main function.
***********************************************************************************************************************/
int digitAppearance(int digitInt, int number, int rem, int appearance){
    rem = number % baseDec;
    //checks if the digit is the same as the remainder until the number is 0
    if(rem == digitInt && number != 0){
        appearance++;
        number = number / baseDec;
        return digitAppearance(digitInt, number, rem, appearance);
    }else if(rem != digitInt && number != 0){
        number = number / baseDec;
        return digitAppearance(digitInt, number, rem, appearance);
    }else{
        return appearance;
    }
}

/***********************************************************************************************************************
Function name: greatestCD
Input: int num1, int num2. (the two numbers inputted by the user in the main)
Output: int (the greatest common denominator)
Function operation: The function receives the two numbers determines which greater then proceeds to take the output of
 big number % small number, and returns to the function until one of the numbers == 0. At that point the function
 returns whichever number != 0 to the main. (While the function is completing all these operations it prints out the
 logic)
***********************************************************************************************************************/
int greatestCD(int num1, int num2, char choice){
    if(num1 < 0 || num2 < 0){
        printf("You should stay positive, and so should your input.\n");
        choice = getchar();
        main();
    }
    //If the number is zero it can be divided by any number
    int bigNum = 0, smallNum = 0, quotient = 0, remainder = 0;
    if(num1 > num2){
        bigNum= num1;
        smallNum = num2;
    }
    else if(num2 > num1){
        bigNum = num2;
        smallNum = num1;
    }
    if(bigNum != 0 && smallNum != 0){
        quotient = bigNum / smallNum;
        remainder = bigNum % smallNum;
    }else{
        if(num1 == 0){
            return num2;
        }
        if(num2 == 0){
            return num1;
        }
    }
    //prints out the logic
    printf("%d*%d+%d = %d ", smallNum, quotient, remainder, bigNum);
    printf("(num1=%d, num2=%d)\n", bigNum, smallNum);

    //takes the remainder of the big number % small number
    if(num1 > num2){
        return greatestCD(num1 % num2, num2, choice);
    }else{
        return greatestCD(num1, num2 % num1, choice);
    }
}

/***********************************************************************************************************************
Function name: logicCalculator
Input: char userInput
Output: int (valid)
Function operation: checks the validity of each phrase, if there is a syntax error it prints an error and returns a 0
 to the main function. In the case of no syntax error the function passes the values onto the phraseCheck function, and
 receives back a value from phraseCheck, assigns it the correct value in accordance with the valid checker. 1 is T,
 and 2 is F.
***********************************************************************************************************************/
int logicCalculator(char choice){
    printf("\nPlease write your logical statement: ");

    if(choice == ' '){
        choice = getchar();
    }

    char previousChar;

    char open = 0, close = 0, not = 0, insideOperand = 0, outsideOperand = 0, number1 = 0, number2 = 0;
    int phrase = 2;
    char variable1 = '#', variable2 = '#';

    //checking user input character by character
    while(choice != '\n' || choice != ' '){
        switch (choice) {
            case '~':
                number1 = 0;
                if(not != 0){
                    printf("You have a syntax error in your statement.\n");
                    return 0;
                }else{
                    not = 1;
                }
                break;
            case '(':
                number1 = 0;
                if(open != 0){
                    printf("You have a syntax error in your statement.\n");
                    return 0;
                }else{
                    open = 1;
                }
                break;
            case ')':
                number1 = 0;
                if(close != 0){
                    printf("You have a syntax error in your statement.\n");
                    return 0;
                }else{
                    close = 1;
                }
                break;
            case '>':
                number1 = 0;
                if(insideOperand != 0){
                    printf("You have a syntax error in your statement.\n");
                    return 0;
                }else{
                    insideOperand = '>';
                }
                break;
            case '<':
                number1 = 0;
                if(insideOperand != 0){
                    printf("You have a syntax error in your statement.\n");
                    return 0;
                }else{
                    insideOperand = '<';
                }
                break;
            case '=':
                number1 = 0;
                if(insideOperand != 0){
                    printf("You have a syntax error in your statement.\n");
                    return 0;
                }else{
                    insideOperand = '=';
                }
                break;
            case '&':
                open = 0, close = 0, number1 = 0;
                if(outsideOperand != 0){
                    printf("You have a syntax error in your statement.\n");
                    return 0;
                }else{
                    outsideOperand = '&';
                    if(phrase == 0){
                        // if the first phrase is wrong the whole statement is wrong
                        return 2;
                    }else if (phrase == 1){
                        //calling the function again to check the next phrase
                        phrase = logicCalculator(choice);
                        if(phrase == 0){
                            return 2;
                        }else{
                            return phrase;
                        }
                    }
                }
                break;
            case '|':
                open = 0, close = 0, number1 = 0;
                if(outsideOperand != 0){
                    printf("You have a syntax error in your statement.\n");
                    return 0;
                }else{
                    outsideOperand = '|';
                    if(phrase == 0){
                        //calling the function again to check the next phrase
                        phrase = logicCalculator(choice);
                        if (phrase == 0){
                            return 2;
                        }else{
                            return phrase;
                        }
                    }else if(phrase == 1){
                        //if the first phrase is correct the whole statement is correct
                        return 1;
                    }
                }
                break;
            case ' ':
                //resets the statement while keeping the T or F value of the previous one
                not = 0, open = 0, close = 0, variable1 = 0, variable2 = 0, insideOperand = 0;
                choice = getchar();
                if((choice >= 49 && choice <= 52) && previousChar == 1){
                    main();
                }else{
                    previousChar = 0;
                    logicCalculator(choice);
                }

                break;
            default:
                if((choice >= 'A' && choice <= 'Z')||(choice >= 'a' && choice <= 'z')
                   ||(choice >= '0' && choice <= '9')){
                    //assigning the user inputted variables their respective variables
                    //number counter to check if the previous user input was a number, if so it's added to its
                    //respective variable.
                    if(variable1 == '#' && number1 == 0){
                        number1 = 1;
                        variable1 = choice;
                    }else if (variable2 == '#' && number2 == 0){
                        number2 = 1;
                        variable2 = choice;
                    }else if (variable1 != '#' && variable2 != '#' && number1 == 0 && number2 == 0){
                        printf("You have a syntax error in your statement.\n");
                        return 0;
                    }else if(number1 == 1){
                        variable1 = ((variable1 - 48)* baseDec) + (choice - 48);

                    }else if(number2 == 1){
                        variable2 = ((variable2 - 48) *baseDec) + (choice - 48);
                    }
                }else{
                    printf("You have a syntax error in your statement.\n");
                    choice = getchar();
                    while(choice != ' '){
                        choice = getchar();
                    }
                    if (choice == ' '){
                        main();
                    }
                }
                break;
        }
        //checks to see if there is a full statement in the brackets and not a partial one
        if(close == 1){
            if(open == 1 && close == 1 && (insideOperand == 0 || variable1 == 0 || variable2 == 0)){
                printf("You have a syntax error in your statement.\n");
                return 0;
            }
            phrase = phraseCheck(not, insideOperand, variable1, variable2);
            if(phrase == 0){
                return 2;
            }else{
                return 1;
            }
        }else{
            choice = getchar();
        }
    }
}

/***********************************************************************************************************************
Function name: phraseCheck
Input: char not, char insideOperand, char variable1, char variable2
Output: int
Function operation: assigns each variable its correct ASCII value according to the targil (a=A), checks if the
 whole statement is T or F, then returns a value of 0 (F) or 1 (T) to the logicCalculator function.
***********************************************************************************************************************/
int phraseCheck(char not, char insideOperand, char variable1, char variable2){
    //assigns each variable its correct ASCII value according to the targil
    if(variable1 >= 'A' && variable1 <= 'Z'){
        variable1 = variable1 + 32;
    }
    if(variable2 >= 'A' && variable2 <= 'Z'){
        variable2 = variable2 + 32;
    }
    if(variable1 >= 0 && variable1 <= 9){
        variable1 = variable1 - 48;
    }
    if(variable2 >= 0 && variable2 <= 9){
        variable2 = variable2 - 48;
    }
    //determines if the phrase is T or F taking into account the not.
    if(not == 0) {
        if (insideOperand == '>') {
            if (variable1 > variable2) {
                return 1;
            } else {
                return 0;
            }
        } else if (insideOperand == '<') {
            if (variable1 < variable2) {
                return 1;
            } else {
                return 0;
            }
        } else if (insideOperand == '=') {
            if (variable1 == variable2) {
                return 1;
            } else {
                return 0;
            }
        }
    }else{
        if (insideOperand == '>') {
            if (variable1 > variable2) {
                return 0;
            } else {
                return 1;
            }
        } else if (insideOperand == '<') {
            if (variable1 < variable2) {
                return 0;
            } else {
                return 1;
            }
        } else if (insideOperand == '=') {
            if (variable1 == variable2) {
                return 0;
            } else {
                return 1;
            }
        }
    }

}