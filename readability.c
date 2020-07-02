#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

int countletters(string text);
int countwords(string text);
int countsentences(string text);
int calcindexnum(int letters, int words, int sentences);

int main(void)
{
    
    
    string text = get_string("Text: ");
    int letters = countletters(text);
    int words = countwords(text);
    int sentences = countsentences(text);
    //printf("letters: %i\n", letters);
    //printf("words: %i\n", words);
    //printf("sentences: %i\n", sentences);
    int grade = calcindexnum(letters, words, sentences);
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    } 
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    } 
    else
    {
        printf("Grade %i\n", grade);
    }
    
}

//get amoutn of letters
int countletters(string text)
{
    int lettercount = 0;
    for (int i = 0; i < strlen(text); i++)
        if (isalpha(text[i]))
        {
            lettercount++;
        }
    return lettercount;
}
//get amount of words
int countwords(string text)
{
    int wordcount = 1;
    for (int i = 0; i < strlen(text); i++)
        if (isblank(text[i]))
        {
            wordcount++;
        }
    return wordcount;
}
//get amount of sentences
int countsentences(string text)
{
    int sentencescount = 0;
    for (int i = 0; i < strlen(text); i++)
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentencescount++;
        }
    return sentencescount;
}





//calculate grade
int calcindexnum(int letters, int words, int sentences)
{
    float L = (letters / words) * 100 ;
    float S = (sentences / words) * 100;
    float indexraw = (0.0588 * L) - (0.296 * S) - 15.8;
    int index = round(indexraw);
    return index;
}
