
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
//psuedocode
//check there are 2 arguments in the command line, no more, no less
//  if there isnt reply usage syntax and end
//check each char in argv for a nondigit
//  if there isnt reply usage syntax and end
//passing those to requirements, get the plaintext from user
//turn the string into an intiger
//loop through the plaintext 1 char at a time
//  if the char isnt a letter, leave as is
//  if it is check, is it upper or lowercase
//      edit ascii depending on outcome 
//  print edited ascii in char form
//end with \n

//argc is how many arguments
//argv[] is the array of arguments
int main(int argc, string argv[])
{
   
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    } 
    else
    { 
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            if (isdigit(argv[1][i]) == 0)
            {   
                printf("Usage: ./caesar key\n");
                return 1;
            } 
        }
    }
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");
    int key = atoi(argv[1]);
    for (int j = 0; j < strlen(plaintext); j++)
    {   
        char letter = plaintext[j];
        if (isalpha(letter) == 0)
        {
            printf("%c", letter);
        } 
        else
        {
            if (isupper(letter))
            {
                printf("%c", ((letter + key - 65) % 26) + 65);
            }
            else if (islower(letter))
            {
                printf("%c", ((letter + key - 97) % 26) + 97);
            }
        }    
    }
    printf("\n");
}
