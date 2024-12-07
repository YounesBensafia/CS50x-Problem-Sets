#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int start;
    int end;

    // TODO: Prompt for start size
    do
    {
        start = get_int("Start size: ");
    }
    while (start < 9);

    // TODO: Prompt for end size
    do
    {
        end = get_long("End size: ");
    }
    while (end < start);
    // TODO: Calculate number of years until we reach threshold
    //'years' is a variable for counting years, here the compiler will entre the loop until the 'end' will be > than 'start' in
    // parallel the variable 'years' will be increment with 1
    int years = 0;
    while (start < end)
    {
        start = start + (start / 3) - (start / 4);
        years += 1;
    }
    // TODO: Print number of years
    printf("Years: %i.\n", years);
}
