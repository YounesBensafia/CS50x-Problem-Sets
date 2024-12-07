#include <cs50.h>
#include <stdio.h>

// fonctions:
void dots(int var, int i);
void hash(int i);
// main:
int main(void)
{
    int height;
    // do while for prompts tne user for the pyramid's height
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    // printing our pyramid of #.
    for (int i = 0; i < height; i++)
    {
        dots(height, i);
        hash(i);
        printf("\n");
    }
}
// fonction for printing dots with i and the height as arguments
void dots(int var, int i)
{
    for (int k = i; k < var - 1; k++)
    {
        printf(" ");
    }
}
// fonction for printing dots with i and the height as arguments
void hash(int i)
{
    for (int j = 0; j < i + 1; j++)
    {
        printf("#");
    }
}
