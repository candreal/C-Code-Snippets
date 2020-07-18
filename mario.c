#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = get_int("Enter height:\n");            //asks for input the first time, stores input in integer variable "height"

    if (height < 1 || height > 8)                       //checks for invalid height input, runs only if first input was invalid
    {
        do                                              //this loop will run at least once and check for invalid input at the end 
        {                                               
            height = get_int("Enter height:\n");        //the first input has already been confirmed to be invalid from the if statement
        }
        while (height < 1 || height > 8);
    }

    for (int i = 0; i < height; i++)                     //nested for loops to print an array of # symbols and spaces
    {
        for (int j = 0; j < height; j++)
        {
            if (height - j - 1 <= i)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("  ");
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}