#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //step 0: check string variable 'key' for invalid input
    //no command line argument
    if (argc == 1)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];

    //invalid length
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    bool isPresent = false;
    //search for invalid characters
    for (int i = 0; i < 26; i++)
    {
        isPresent = false;
        if (!isalpha(key[i]))
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
        for (int j = 0; j < 26; j++)
        {
            if ((isupper(key[j]) && key[j] == (i + 65)) || (islower(key[j]) && key[j] == (i + 97)))
            {
                isPresent = true;
                //printf("%c exists at %i\n", (char)(i + 65), j);
                break;
            }
        }
        if (!isPresent)
        {
            printf("Key must not have duplicate letters.\n");
            return 1;
        }
    }


    //Step 1: prompt user to enter plaintext and store it in a string variable named 'ptext'

    string ptext = get_string("plaintext: ");
    int plength = (int)strlen(ptext);
    char ctext[plength];

    for (int i = 0; i < plength; i++)
    {
        ctext[i] = 0;
    }
    //Step 2: iterate through argv[1]

    for (int i = 0; i < plength; i++)
    {
        //check if plaintext character is a letter
        if (isalpha(ptext[i]))
        {
            //if the character is a letter, check if it is an uppercase letter
            if (isupper(ptext[i]))
            {
                //add the corresponding uppercase character to the same spot in ctext, using the key
                ctext[i] = toupper(key[ptext[i] - 65]);
            }
            else
            {
                //add the corresponding lowercase character to the same spot in ctext, using the key
                ctext[i] = tolower(key[ptext[i] - 97]);
            }
        }
        else
        {
            //if the character is not a letter, just add as it is to ctext
            ctext[i] = ptext[i];
        }
    }

    //Step 3: output the ciphertext
    printf("ciphertext: ");
    for (int i = 0; i < plength; i++)
    {
        printf("%c", ctext[i]);
    }
    printf("\n");
    return 0;
}