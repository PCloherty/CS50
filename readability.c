#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

int calcindexnum(int letters, int words, int sentences);

int main(void)
{
    int lettercount = 0;
    int wordcount = 1;
    int sentencecount = 0;
    
    string text = get_string("Text: ");
    printf("Output: ");
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            lettercount++;
        }
        else if (isblank(text[i]))
        {
            wordcount++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentencecount++;
        }
        
    }
    printf("letters: %i\n", lettercount);
    printf("words: %i\n", wordcount);
    printf("sentences: %i\n", sentencecount);
    int grade = calcindexnum(lettercount, wordcount,
                            sentencecount);
    if (grade < 1)
    {
        printf("Before Grade 1");
    } 
    else if (grade > 16)
    {
        printf("Grade 16+");
    } 
    else
    {
        printf("Grade %i\n", grade);
    }
    
}


int calcindexnum(int letters, int words, int sentences)
{
    float L = (letters / words) * 100 ;
    float S = (sentences / words) * 100;
    int index = round((0.0588 * L) - (0.296 * S) - 15.8);
    return index;
}
