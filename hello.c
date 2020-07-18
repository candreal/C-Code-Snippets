//A slight twist on the typical "Hello World" program
  
#include <stdio.h>
#include <cs50.h>                                       //include the cs50 library for definition of function get_string

int main(void)
{
    string name = get_string("What is your name?\n");   //prints "What is your name?\n", and stores input in a string variable "name"
    printf("hello, %s\n", name);                        //prints "hello, " followed by the value of the variable "name"
}
