#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float change = get_float("Change owed:\n");         //asks for input the first time, stores input in integer variable "change"

    int coins = 0;                                      //variable to count the number of coins needed

    if (change < 0)                                     //checks for invalid change input, runs only if first input was invalid
    {
        do                                              //this loop will run at least once and check for invalid input at the end 
        {                                               
            change = get_float("Change owed:\n");       //the first input has already been confirmed to be invalid from the if statement
        }
        while (change < 0);
    }

    int cents = round(change * 100);                    //converts change needed to cents

    if (cents >= 25)                                    //check if the change is greater than or equal to one quarter
    {
        do
        {
            cents = cents - 25;                         //subtract the value of one quarter from change owed
            coins++;                                    //add 1 to the coin count
        }
        while (cents >= 25);                           //check if change owed is still greater than or equal to one quarter
    }

    if (cents >= 10)                                   //check if the change is greater than or equal to one dime
    {
        do
        {
            cents = cents - 10;                        //subtract the value of one dime from change owed
            coins++;                                    //add 1 to the coin count
        }
        while (cents >= 10);                         //check if change owed is still greater than or equal to one dime
    }

    if (cents >= 5)                                 //check if the change is greater than or equal to one nickel
    {
        do
        {
            cents = cents -5;                     //subtract the value of one nickel from change owed
            coins++;                                    //add 1 to the coin count
        }
        while (cents >= 5);                         //check if change owed is still greater than or equal to one nickel
    }

    if (cents >= 1)                                 //check if the change is greater than or equal to one penny
    {
        do
        {
            cents = cents - 1;                     //subtract the value of one penny from change owed
            coins++;                                    //add 1 to the coin count
        }
        while (cents >= 1);                         //check if change owed is still greater than or equal to one penny
    }

    printf("%d\n", coins);                      //print out number of coins

}