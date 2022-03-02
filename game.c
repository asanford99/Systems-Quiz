#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/*
first, i will create a start game function that is called when the program starts, and will write my "main function code" in there. i am doing this for the sake of being able to recursively call this function after the user inputs 1 or 2

second, i will make the necassary declarations that i need throughout the program, and add to them as i see need for

third, i will make a system that outputs the menu and takes in user input

fourth, i willmake three functions based on the possibile inputs

lastly, if the user input is not 3, i will recall the start game function passing arguments that have possibly been updated

*/
static void startGame(int maxNumPar, int gamesPlayedPar, int* gamesDataPar);

void quitGame(int gamesPlayedPar, int* gamesDataPar) {
    int i;

    //checks if the game has been played and if it has, outputs the results from all games played that session
    if (gamesPlayedPar == 0){

        printf("Thanks for playing!");

    }
    else{

        printf("Thanks for playing! here are your results:\n");

        for(i = 0; i < gamesPlayedPar; i++){
        
            if (gamesDataPar[i] == 0){
            
            printf("Game %d: Loss.\n", (i + 1));

            }
            else{

            printf("Game %d: Win after %d guesses.\n", (i + 1), gamesDataPar[i]);

            }

        }

    }

    free(gamesDataPar);

    return;
}

void changeMax(int maxNumPar, int gamesPlayedPar, int* gamesDataPar) {
    int userNum;

    char userInput[2];

    //reads input from user, validates the input, and stores into maxNumPar
    printf("Enter an integer between 1-50 to change the max number to: ");

    scanf("%s", userInput);

    if (!strtod(userInput, NULL)){

        printf("Invalid input.");

        changeMax(maxNumPar, gamesPlayedPar, gamesDataPar);

        free(gamesDataPar);

        return;

    }

    userNum = atoi(userInput);

    if (userNum < 1){
        
        printf("Invalid input.");

        changeMax(maxNumPar, gamesPlayedPar, gamesDataPar);

        free(gamesDataPar);

        return;

    }

    if (userNum > 50){
        
        printf("Invalid input.");

        changeMax(maxNumPar, gamesPlayedPar, gamesDataPar);

        free(gamesDataPar);

        return;

    }

    printf("Success! Max number has been changed to %d.\n", userNum);

    startGame(userNum, gamesPlayedPar, gamesDataPar);

    free(gamesDataPar);

    return;
}

void playGame(int maxNumPar, int gamesPlayedPar, int* gamesDataPar) {
    //declares random number between 0 and maxNumPar-1
    time_t t;
    char userInput[sizeof(maxNumPar)];
    int userNum;
    int realNum;
    int guessCount = 0;

    srand((unsigned)time(&t));

    realNum = ((rand() % maxNumPar) + 1);

    goto start;

    //creates the game mechanics and a starting place to call back to after each guess, also validates and stores input
start:

    //validates and stores input
    printf("Enter an integer 1-%d (or press q to quit): ", maxNumPar);

    scanf("%s", userInput);

    if (userInput[0] == 'q') {

        gamesPlayedPar++;

        gamesDataPar = (int*)realloc(gamesDataPar, gamesPlayedPar * sizeof(int));

        gamesDataPar[gamesPlayedPar - 1] = 0;

        startGame(maxNumPar, gamesPlayedPar, gamesDataPar);

        free(gamesDataPar);

        return;
    }

    if (!atoi(userInput)) {

        printf("Please enter an integer between 1 and %d.\n", maxNumPar);

        goto start;
    }

    userNum = atoi(userInput);

    if (userNum < 1) {

        printf("Integer not valid. Please enter an integer between 1 and %d.\n", maxNumPar);

        goto start;

    }

    if (userNum > maxNumPar) {

        printf("Integer not valid. Please enter an integer between 1 and %d.\n", maxNumPar);

        goto start;

    }

    //creates mechanics of the game and keeps track of games played and game data
    if (userNum < realNum) {

        printf("Too low, guess again!\n");

        guessCount++;

        goto start;

    }

    if (userNum > realNum) {

        printf("Too high, guess again!\n");

        guessCount++;

        goto start;

    }

    guessCount++;

    printf("Success! The number was %d. You won after %d guesses.\n", realNum, guessCount);

    gamesPlayedPar++;

    gamesDataPar = (int*)realloc(gamesDataPar, gamesPlayedPar * sizeof(int));

    gamesDataPar[gamesPlayedPar - 1] = guessCount;

    startGame(maxNumPar, gamesPlayedPar, gamesDataPar);

    free(gamesDataPar);

    return;

}

void startGame(int maxNumPar, int gamesPlayedPar, int* gamesDataPar) {

    int userNum;

    char userInput[1];

    //this displays the menu
    printf("Press 1 to play a game\n");
    printf("Press 2 to change the max number\n");
    printf("Press 3 to quit\n");

    scanf("%s", userInput);

    //validates input and stores into userInput
    if (!strtod(userInput, NULL)) {

        printf("Invalid input. Must be 1, 2, or 3.\n");

        startGame(maxNumPar, gamesPlayedPar, gamesDataPar);

    }

    userNum = atoi(userInput);

    if (userNum < 1) {

        printf("Invalid input. Must be 1, 2, or 3.\n");

        startGame(maxNumPar, gamesPlayedPar, gamesDataPar);

    }

    if (userNum > 3) {

        printf("Invalid input. Must be 1, 2, or 3.\n");

        startGame(maxNumPar, gamesPlayedPar, gamesDataPar);

    }

    //chooses function based on userInput
    switch (userNum) {

    case 1:
        playGame(maxNumPar, gamesPlayedPar, gamesDataPar);
        break;

    case 2:
        changeMax(maxNumPar, gamesPlayedPar, gamesDataPar);
        break;

    case 3:
        quitGame(gamesPlayedPar, gamesDataPar);
        break;

    }

    free(gamesDataPar);

    return;
}

int main() {

    int* gamesData;

    gamesData = (int*)malloc(0 * sizeof(int));

    startGame(10, 0, gamesData);

    free(gamesData);

    exit(0);

    return 0;
}