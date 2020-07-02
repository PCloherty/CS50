
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
//psuedocode
//check there are 2 arguments in the command line, no more, no less
//if there isnt reply usage syntax and end
//get plaintext from user
//argc is how many arguments
//argv[] is the array of arguments
int main(int argc, string argv[])
{
   
    if (argc != 2){
        printf("Usage: ./caesar key\n");
        return 1;
    } 
    else
    { 
        for (int i=0; i < strlen(argv[1]); i++)
        if (isdigit(argv[1][i])== 0)
        {   
            printf("Usage: ./caesar key\n");
            return 1;
        } else {
            string plaintext = get_string("plaintext: ");
            printf("ciphertext: ");
            int key = atoi(argv[1]);
            for (int j=0; j < strlen(plaintext); j++)
            {   
                char letter= plaintext[j];
                if(isalpha(letter)== 0)
                {
                    printf("%c",letter);
                } 
                else
                {
                    if(isupper(letter)){
                        printf("%c",((letter+key-65)%26)+65);
                    }
                    else if(islower(letter))
                    {
                        printf("%c",((letter+key-97)%26)+97);
                    }
                }    
            }
        printf("\n");
        }
    
    }
}
