#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

bool validate_length(string s);
bool check_alphabetic(string s);
bool check_repeated_characters(string s);

// It's like a reference

char alphabets[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

// Here is the main

int main(int argc, string argv[])
{
    string s;
    if (argc == 2)
    {
        // Validate all obligations
        bool b1 = validate_length(argv[1]);
        bool b2 = check_alphabetic(argv[1]);
        bool b3 = check_repeated_characters(argv[1]);
        if (b1 && b2 && b3)
        {
            s = get_string("Plain text: ");
            for (int i = 0; i < strlen(s); i++)
            {
                // if is it upper character
                if (isupper(s[i]))
                {
                    for (int j = 0; j < strlen(alphabets); j++)
                    {
                        if (s[i] == alphabets[j])
                        {
                            // make it uppercase
                            s[i] = toupper(argv[1][j]);
                            break;

                        }
                    }
                }
                else
                {
                    // if is it lower character
                    if (islower(s[i]))
                    {
                        for (int j = 0; j < strlen(alphabets); j++)
                        {
                            // make it uppercase
                            if (s[i] == tolower((alphabets[j])))
                            {
                                s[i] = tolower(argv[1][j]);
                                break;

                            }
                        }
                    }
                }


            }
            printf("ciphertext: %s\n", s);
        }
        else
        {
            exit(1);
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        exit(1);
    }

}

// validate length

bool validate_length(string s)
{
    if (strlen(s) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }
    return true;
}

// check alphabetic

bool check_alphabetic(string s)
{
    int i = 0;
    while (i < strlen(s))
    {
        if ((s[i] < 'A' || s[i] > 'Z') && (s[i] < 'a' || s[i] > 'z'))
        {
            printf("Key must only contain alphabetic characters.\n");
            return false;
        }
        i++;
    }
    return true;
}

// check repeated characters

bool check_repeated_characters(string s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        for (int j = 0; j < strlen(s); j++)
        {
            if (s[i] == s[j] && i != j)
            {
                printf("Key must not contain repeated characters.\n");
                return false;
            }
        }
    }
    return true;
}

// check repeated characters
// VCHPRZGJNTLSKFBDQWAXEUYMOI
// Hello, world