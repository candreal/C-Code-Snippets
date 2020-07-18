#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int main(void)
{
    //Step 1. Prompt user for some text, and store it in a string variable named 'text'

    string text = get_string("Text: \n");


    //Step 2. Iterate through the text, counting the number of letter, words, and sentences.

    int letters = 0;
    int words = 0;
    int sentences = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        //Count the total number of letters in the string. In ASCII values, uppercase letters are 65-90, and lowercase are 97-122

        if ((text[i] > 64 && text[i] < 91) || (text[i] > 96 && text[i] < 123))
        {
            letters++;
        }

        //Count the total number of words in the string. expect a space after each word, except the very last word. so after the count of spaces, add 1.

        if (text[i] == ' ')
        {
            words++;
        }

        //Count the total number of sentences. Expect that every time a "." "!" "?" are shown, it is the end of a sentence

        if (text[i] == '.' || text[i] ==  '!' || text[i] ==  '?')
        {
            sentences++;
        }
    }
    words++;


    //Step 3. Calculate the index with this formula: index = (5.88 * letters / words) - (29.6 * sentences / words) - 15.8

    float index = (5.88 * letters / words) - (29.6 * sentences / words) - 15.8;


    //Step 4. format the output. if index < 1, print "Before Grade 1" and if index > 15, print "Grade 16+"

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 15)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int)round(index));
    }
}