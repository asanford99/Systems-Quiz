#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>

/*first i am going declare the various variable i will need

second, i will create a system that takes takes the user input from the command line

third, i will make functions that take the various inputs from the random number generator and the user that return necessary values such as tip amount, tax amount, and total amount

lastly, i will output the results from thos functions to the user
*/

//function to find tax amoutn based on meal price
float taxFinder(float taxRatePar, float mealPricePar){

    return ((taxRatePar / 100) * mealPricePar);

}

//function to find tax amoutn based on meal price
float tipFinder(float tipRatePar, float mealPricePar){

    return ((tipRatePar / 100) * mealPricePar);

}

int main(int argc, char *argv[]){

 //declaring variables   
    const float salad = 9.95;
    const float soup = 4.55;
    const float sandwich = 13.25;
    const float pizza = 22.35;
    float mealAmount;
    float tipRate;
    float taxRate;
    float tipAmount;
    float taxAmount;
    float totalAmount;

    char mealType[9];

    time_t t;

    srand((unsigned) time(&t));

    int mealNumber = rand() % 4;

    //taking input from user
    if (argc < 3){
        printf("Too few arguments. Tax rate and tip rate are needed.");

        exit(0);
    }

    if (argc > 3){
        printf("Too many arguments. Tax rate and tip rate are needed.");

        exit(0);
    }

    if (!strtof(argv[1], NULL)){

        printf("Invalid input. Values must be float.");

        exit(0);

    }

    if (!strtof(argv[2], NULL)){

        printf("Invalid input. Values must be float.");

        exit(0);
        
    }

    taxRate = strtof(argv[1], NULL);

    tipRate = strtof(argv[2], NULL);
    
    //determining meal price by mealNumber
    switch(mealNumber){

        case 0:
            mealAmount = salad;
            strcat(mealType, "salad");
            break;
        
        case 1:
            mealAmount = soup;
            strcat(mealType, "soup");
            break;

        case 2:
            mealAmount = sandwich;
            strcat(mealType, "sandwich");
            break;

        case 3:
            mealAmount = pizza;
            strcat(mealType, "pizza");
            break;

    }

    //finds tax and tip value and stores into variables with 2 decimal place accuracy
    taxAmount = taxFinder(taxRate, mealAmount);

    tipAmount = tipFinder(tipRate, mealAmount);

    taxAmount = roundf(taxAmount * 100) / 100;

    tipAmount = roundf(tipAmount * 100) / 100;

    //finds total cost of meal
    totalAmount = mealAmount + taxAmount + tipAmount;

    //displays information to the user
    printf("Meal cost for %s: $%.2f\n", mealType, mealAmount);

    printf("Tax for meal: $%.2f\n", taxAmount);

    printf("Tip for meal: $%.2f\n", tipAmount);

    printf("Total cost of meal: $%.2f\n", totalAmount);
    
    return 0;
}