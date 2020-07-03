#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct //like object
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];//candidate= singular element of the candidates array

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)  //loop the candidates array to match with the input names, if found candidate.votes++ and return true
{                       //if no match, leave votes alone and return false
    for(int i = 0 ; i <candidate_count ; i++ )
    {
        if(strcmp(name,candidates[i].name)==0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void) //loop through to get record of highest vote
{                       //then loop again to check if the candidates[j].votes match the highest vote, if yes then print .name 
    int highest_vote = 0;
    for (int i = 0 ; i <candidate_count ; i++ )
    {
        if (candidates[i].votes > highest_vote)
        {
            highest_vote = candidates[i].votes;
        }
    }
    for (int j = 0 ; j <candidate_count ; j++ )
    {
        if (candidates[j].votes == highest_vote)
        {
            printf("%s\n",candidates[j].name);
        }
    }
            
   
    
        
    // TODO
    return;
}

