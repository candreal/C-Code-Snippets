#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    //check if voter has already voted
    if (preferences[voter][rank] != 0)
    {
        return false;
    }

    //Step 1: search the lost of candidates for the name recorded on the ballot
    for (int i = 0; i < candidate_count; i++)
    {
        //if the name is found in the list of candidate names, record it on the ballot
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    //else, return false
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    //iterate through the preferences, paying attention only to the first preference
    for (int i = 0; i < voter_count; i++)
    {
        //check if that candidate has been eliminated
        if (candidates[preferences[i][0]].eliminated)
        {
            //first choice has been eliminated, check next choice
            if (candidates[preferences[i][1]].eliminated)
            {
                //second choice has been eliminated, check third
                if (!candidates[preferences[i][2]].eliminated)
                {
                    //third choice has not been eliminated, record a vote for them
                    candidates[preferences[i][2]].votes++;
                }
            }
            else
            {
                //first choice has been eliminated, but second choice has not, so record a vote for them
                candidates[preferences[i][1]].votes++;
            }
        }
        else
        {
            //first choice has not been eliminated, so record a vote for them
            candidates[preferences[i][0]].votes++;
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    //check candidates for a winner
    for (int i = 0; i < candidate_count; i++)
    {
        if ((float)candidates[i].votes > (float)voter_count / 2.0)
        {
            //candidate has gained more than half of the votes, so (s)he is the winner of the election
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    //initalize a variable to keep track of the minimum number of votes
    int m = MAX_VOTERS;

    //iterate through the candidates. if they have not been eliminated, compare their number of votes to the current minimum m
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            if (candidates[i].votes < m)
            {
                m = candidates[i].votes;
            }
        }
    }
    return m;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    //iterate through the candidates, and compare their number of votes to the min
    for (int i = 0; i < candidate_count; i++)
    {
        //check only candidates who have not yet been eliminated
        if (!candidates[i].eliminated)
        {
            if (candidates[i].votes != min)
            {
                //if any candidate has an amount of votes other than the min, it cannot be a tie
                return false;
            }
        }
    }
    //if no value has yet been returned, then all candidates have the same number of votes (and they all equal min)
    return true;
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    //iterate through candidates. if their voter count equals 'min', set 'eliminated' to true
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}