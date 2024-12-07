#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // here the variable 'name' with the fonction get_string returns here the name of user
    string name = get_string("What's your name? ");
    // 'name' <- the name of user
    printf("Hello, %s\n", name);
    // Hello, 'name'!
}