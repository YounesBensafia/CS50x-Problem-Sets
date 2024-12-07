#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[]    = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
// all english alphabets 
char ALPHABETS[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

int compute_score(string word);
// (number) is a fonction to calculate the number of score of each character.
int number(char c);
// (compare score) is a function to define the message to output (Who wins).
string compare_score(int score1, int score2);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    string s = compare_score(score1, score2);
    printf("%s\n", s);
}

int compute_score(string word)
{
    int score = 0;
    // TODO: Compute and return score for string
    for (int i = 0; i < strlen(word); i++)
    {
        word[i] = toupper(word[i]);
        score = score + number(word[i]);
    }


    return score;

}

int number(char c)
{
    for (int i = 0; i < strlen(ALPHABETS); i++)
    {
        if (c == ALPHABETS[i])
        {
            return POINTS[i];
        }
    }
    return 0;
}

string compare_score(int score1, int score2)
{
    if (score1 == score2)
    {
        return "Tie!";
    }
    else
    {
        if (score1 < score2)
        {
            return "Player 2 wins!";
        }
        else
        {
            return "Player 1 wins!";
        }
    }

    return "";

}
