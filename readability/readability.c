#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int calculate_letters(string s);
int calculate_sentences(string s);
int calculate_spaces(string s);
int calculate_words(string s);
double number_letters_per_100(int words, int letters);
double number_sentences_per_100(int words, int sentences);

int main(void)
{
    string s = get_string("Text: ");
    int letters = calculate_letters(s);
    int words = calculate_words(s);
    int sentences = calculate_sentences(s);
    double nb100_words = number_letters_per_100(words, letters);
    double nb100_sentences = number_sentences_per_100(words, sentences);
    // calculate index for the grade
    float index = 0.0588 * nb100_words - 0.296 * nb100_sentences - 15.8;
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        if (index >= 16)
        {
            printf("Grade 16+\n");
        }
        else
        {
            printf("Grade %.0f\n", index);
        }
    }

}

// for calculate the number of sentences per 100

double number_sentences_per_100(int words, int sentences)
{
    return ((double) sentences * 100) / (double) words;
}

// for calculate the number of letters per 100
double number_letters_per_100(int words, int letters)
{
    return ((double)letters * 100) / (double)words;
}

// for calculate the number of sentences
int calculate_sentences(string s)
{
    int a = 0;
    int j = 0;
    int nbr = 0;
    while (j < strlen(s))
    {
        if ((s[j] == '.' || s[j] == '!' || s[j] == '?'))
        {
            nbr++;
        }
        j++;
    }
    return nbr;
    // return the number of sentences
}

// for calculate the number of words

int calculate_words(string s)
{
    return calculate_spaces(s) + 1;
}

// for calculate the number of sentences
int calculate_letters(string s)
{
    int a = 0;
    int j = 0;
    for (int i = j; i < strlen(s); i++)
    {
        if ((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z'))
        {
            a = a + 1;
        }
    }

    return a;
    // return the number of sentences
}

// for calculate spaces
int calculate_spaces(string s)
{
    int i = 0;
    int nb = 0;
    while (i < strlen(s))
    {
        if (s[i] == ' ')
        {
            nb++;
        }
        i++;
    }
    return nb;
    // return the number of spaces
}


