#include <stdio.h>
#include <math.h>

//con is short for convert
//rem is short for remainder
//num is short for number
//dec is short for decimal
//oct is short for octal
//hex is short for hexadecimal

int main() {

    // global variables
    int baseDec = 10;
    int baseOct = 8;
    int baseHex = 16;
    int baseBin = 2;

    int number;
    printf("Choose an option:\n1. octal to hex\n2. binary addition\n3. print HI\n4. count bits\n"
           "5. decimal to binary\n6. Zig-Zag bits\n7. exit\n");
    scanf("%d", &number);

    switch (number) {
        //converting octal to hexadecimal
        case 1:
            // receiving and flipping the octal number
            printf("Please enter number in octal base: ");
            int octalDig, remOct, revOct = 0, error = 0;
            scanf("%d", &octalDig);
            while(octalDig != 0 && error == 0){
                remOct = octalDig % baseDec;
                revOct = (revOct * baseDec) + remOct;
                octalDig = octalDig / baseDec;
                if(remOct >= baseOct){
                    printf("Invalid input!");
                    error++;
                }
            }
            //converting the octal to decimal
            int remDec, conDec = 0, i = 0;
            while(octalDig == 0 && revOct != 0 && error == 0){
                remDec = revOct % baseDec;
                conDec = conDec + remDec * pow(baseOct, i);
                revOct = revOct / baseDec;
                i++;
            }

            //converting decimal to hexadecimal
            int remHex, m = 0;
            char hex, conHex; // char is a problem it isn't printing
            while(conDec != 0){
                remHex = conDec % baseHex;
                conDec = conDec / baseHex;
                if(remHex == 0){
                    hex = 48;
                }else if(remHex == 1){
                    hex = 49;
                }else if(remHex == 2){
                    hex = 50;
                }else if(remHex == 3){
                    hex = 51;
                }else if(remHex == 4){
                    hex = 52;
                }else if(remHex == 5){
                    hex = 53;
                }else if(remHex == 6){
                    hex = 54;
                }else if(remHex == 7){
                    hex = 55;
                }else if(remHex == 8){
                    hex = 56;
                }else if(remHex == 9){
                    hex = 57;
                }else if(remHex == 10){
                    hex = 65;
                }else if(remHex == 11){
                    hex = 66;
                }else if(remHex == 12){
                    hex = 67;
                }else if(remHex == 13){
                    hex = 68;
                }else if(remHex == 14){
                    hex = 69;
                }else if(remHex == 15){
                    hex = 70;
                }
                //conHex = conHex + hex * pow(baseDec, m);
                //m++;
                printf("%c", hex);
            }printf("\n");


            main();

                break;
                // Adding two binary numbers
                case 2:
                    printf("Please enter two binary numbers: ");
                    unsigned long long num1, num2, bigNum, smallNum, partial, bigNum2, smallNum2;
                    scanf("%llu %llu", &num1, &num2);

                    // determining which input is larger
                    if(num1 > num2){
                        bigNum = num1;
                        smallNum = num2;
                    }else{
                        bigNum = num2;
                        smallNum = num1;
                    }
                    int bigCounter = 0, smallCounter = 0;
                    bigNum2 = bigNum;
                    smallNum2 = smallNum;

                    while(bigNum2 != 0){
                        bigNum2 = bigNum2 / 10;
                        bigCounter++;
                    }
                    while(smallNum2 != 0){
                        smallNum2 = smallNum2 / 10;
                        smallCounter++;
                    }
                    int leadingZeroes;
                    leadingZeroes = bigCounter - smallCounter;

                    //adding the two inputs based on the possible outcomes of singular bits including carry over
                    int bitAdd = 0, carryOver = 0, binAdd = 0, g = 0;
                    while(bigNum > 0 || smallNum > 0){
                        if(bigNum % baseDec == 0 && smallNum % baseDec == 0 && carryOver ==0){
                            bitAdd = 0;
                            carryOver = 0;
                        }else if(bigNum % baseDec == 1 && smallNum % baseDec == 0 && carryOver == 0){
                            bitAdd = 1;
                            carryOver = 0;
                        }else if(bigNum % baseDec == 0 && smallNum % baseDec == 1 && carryOver == 0){
                            bitAdd = 1;
                            carryOver = 0;
                        }else if(bigNum % baseDec == 1 && smallNum % baseDec == 1 && carryOver == 0){
                            bitAdd = 0;
                            carryOver = 1;
                        }else if(bigNum % baseDec == 0 && smallNum % baseDec == 0 && carryOver == 1){
                            bitAdd = 1;
                            carryOver = 0;
                        }else if(bigNum % baseDec == 1 && smallNum % baseDec == 0 && carryOver == 1){
                            bitAdd = 0;
                            carryOver = 1;
                        }else if(bigNum % baseDec == 0 && smallNum % baseDec == 1 && carryOver == 1){
                            bitAdd = 0;
                            carryOver = 1;
                        }else if(bigNum % baseDec == 1 && smallNum % baseDec == 1 && carryOver == 1){
                            bitAdd = 1;
                            carryOver = 1;
                        }
                        binAdd = binAdd + (bitAdd * pow(baseDec, g));
                        g++;
                        bigNum = bigNum / baseDec;
                        smallNum = smallNum / baseDec;
                        }
                        partial = binAdd;
                    //adds the first digit of the binary with the rest of the number
                    if(carryOver != 0){
                      binAdd = pow(baseDec, g) + partial;
                        printf("%0*d%d + %0*d%d = %d\n", leadingZeroes, num1, leadingZeroes, num2, binAdd);
                    }else{
                        printf("%0*d%d + %0*d%d = %d\n", leadingZeroes, num1, leadingZeroes, num2, binAdd);
                    }
                    main();
                break;
                //printing out Hi shape
                case 3:
                    printf("Please enter size: ");
                    int size, side1 = 0, side2 = 0, space = 0, gap = 0, second = 0;
                    scanf("%d", &size);

                    // first row of HI (hashtag/ pound symbol)
                    while(size + 2 != side1 || size != space || size + 2 != side2 || gap < 2 || size + 2 != second){
                        if(size + 2 != side1){
                            printf("#");
                            side1++;
                        }else if(size != space){
                            printf(" ");
                            space++;
                        }else if(size + 2 != side2){
                            printf("#");
                            side2++;
                        }else if(gap < 2){
                            printf(" ");
                            gap++;
                        }else if(size + 2 != second){
                            printf("#");
                            second++;
                        }
                    }
                    printf("\n");

                    //first block until the bridge of H
                    gap = 2;
                    for(int row = 1; row <= size; row++){
                        printf("#");
                        for(int i = 0; i <= size - 1; i++){
                            printf("*");
                        }printf("#");
                        for(int i = 0; i <= space - 1; i++){
                            printf(" ");
                        }printf("#");
                        for(int i = 0; i <= size - 1; i++){
                            printf("*");
                        }printf("#");
                        for(int i = 0; i <= gap - 1; i++){
                            printf(" ");
                        }printf("#");
                        for(int i = 0; i <= size - 1; i++){
                            printf("*");
                        }printf("#\n");
                    }
                    // first row of the bridge of the H (the one with the pound symbols)
                    for(int row = size + 1; row <= size + 1; row++){
                        printf("#");
                        for(int i = 0; i <= size - 1; i++){
                            printf("*");
                        }printf("#");
                        for(int i = 0; i <= space - 1; i++){
                            printf("#");
                        }printf("#");
                        for(int i = 0; i <= size - 1; i++){
                            printf("*");
                        }printf("#");
                        for(int i = 0; i <= gap - 1; i++){
                            printf(" ");
                        }printf("#");
                        for(int i = 0; i <= size - 1; i++){
                            printf("*");
                        }printf("#");
                    }printf("\n");

                    //printing the bridge of the H (the input number/ size of rows)
                    for(int row = size + 2; row <= (size * 2) + 1; row++){
                        printf("#");
                        for(int i = 0; i <= size - 1; i++){
                            printf("*");
                        }printf("*");
                        for(int i = 0; i <= space - 1; i++){
                            printf("*");
                        }printf("*");
                        for(int i = 0; i <= size - 1; i++){
                            printf("*");
                        }printf("#");
                        for(int i = 0; i <= gap - 1; i++){
                            printf(" ");
                        }printf("#");
                        for(int i = 0; i <= size - 1; i++){
                            printf("*");
                        }printf("#\n");
                    }

                    //the last row of the bridge of the H (the one with the pound symbols)
                    for(int row = (size * 2) + 2; row <= (size * 2) + 2; row++){
                        printf("#");
                        for(int i = 0; i <= size - 1; i++){
                            printf("*");
                        }printf("#");
                        for(int i = 0; i <= space - 1; i++){
                            printf("#");
                        }printf("#");
                        for(int i = 0; i <= size - 1; i++){
                            printf("*");
                        }printf("#");
                        for(int i = 0; i <= gap - 1; i++){
                            printf(" ");
                        }printf("#");
                        for(int i = 0; i <= size - 1; i++){
                            printf("*");
                        }printf("#\n");
                    }

                    //printing the block under the bridge of H until the last line
                    for(int row = (size * 2) + 3; row <= (size * 3) + 3; row++){
                        printf("#");
                        for(int i = 0; i <= size - 1; i++){
                            printf("*");
                        }printf("#");
                        for(int i = 0; i <= space - 1; i++){
                            printf(" ");
                        }printf("#");
                        for(int i = 0; i <= size - 1; i++){
                            printf("*");
                        }printf("#");
                        for(int i = 0; i <= gap - 1; i++){
                            printf(" ");
                        }printf("#");
                        for(int i = 0; i <= size - 1; i++){
                            printf("*");
                        }printf("#\n");
                    }

                    // printing the last row
                    for(int row = (size * 3) + 3; row <= (size * 3) + 3; row++){
                        printf("#");
                        for(int i = 0; i <= size - 1; i++){
                            printf("#");
                        }printf("#");
                        for(int i = 0; i <= space - 1; i++){
                            printf(" ");
                        }printf("#");
                        for(int i = 0; i <= size - 1; i++){
                            printf("#");
                        }printf("#");
                        for(int i = 0; i <= gap - 1; i++){
                            printf(" ");
                        }printf("#");
                        for(int i = 0; i <= size - 1; i++){
                            printf("#");
                        }printf("#\n");
                    }

                    main();
                break;
                //counts the number of times 1 appears in a binary number
                case 4:
                    printf("Please enter a binary number: ");
                    int binary, outputBinary, counter = 0, validity = 1;
                    scanf("%u", &binary);
                    //converting the binary to decimal using remainders
                    while(binary != 0){
                        outputBinary = binary % baseDec;
                        binary = binary / baseDec;
                        if(outputBinary != 1 && outputBinary != 0){
                            printf ("Invalid input!\n");
                            binary = 0;
                            validity = 0;
                        }if(outputBinary == 1){
                            counter++;
                        }
                        }
                    //checking to see if the input was valid and printing the output
                    if (validity == 1){
                        printf("%d\n", counter);
                    }
                    main();
                break;
                //converting decimal to binary
                case 5:
                    printf("Enter a non negative decimal number: ");
                    int decToBin, rem, conBin = 0, n = 1;
                    scanf("%d", &decToBin);
                    //comverting the decimal number to binary
                    int input = decToBin;
                    while(decToBin > 0){
                        rem = decToBin % baseBin;
                        decToBin = decToBin / baseBin;
                        conBin = conBin + (rem * n);
                        n = n * baseDec;
                    }
                    //checking if the input was valid then printing the output
                    if (decToBin < 0){
                        printf("Invalid input!\n");
                    }else{
                        printf("%d => %d\n", input, conBin);
                    }

                    main();
                break;

                //checking to see if a binary number has interchanging bits.
                case 6:
                    printf("Enter a non negative decimal number: ");
                    int inputDec, remBin, outputBin = 0, k = 1;
                    scanf("%d",&inputDec);

                    //converting the decimal number to binary
                    while(inputDec > 0){
                        remBin = inputDec % baseBin;
                        inputDec = inputDec / baseBin;
                        outputBin = outputBin + (remBin * k);
                        k = k * baseDec;
                    }
                    //checking to see if two bits next to each other are the same and therefore not zig zag
                    int remOut1 = 0, remOut2 = 1;
                    while(remOut1 != remOut2 && outputBin > 0){
                        remOut1 = outputBin % baseDec;
                        outputBin = outputBin / baseDec;
                        remOut2 = outputBin % baseDec;
                        if(remOut1 == remOut2){
                            printf("false\n");
                        }else if(remOut1 != remOut2 && outputBin == 0){
                            printf("true\n");
                        }
                    }
                    main();
                break;

                case 7:
                    printf("Bye!");
                    break;

                default:
                    printf("Invalid option!\n");
            }
            return 0;
    }
