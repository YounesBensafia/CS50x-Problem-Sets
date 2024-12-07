#include<cs50.h>
#include<stdio.h>

int main(void){
    string name = get_string("What's your name? ");
    int age = get_int("What's your age? ");
    string number = get_string("What's your phone number? ");
    printf("Name: %s \nAge: %i\nNumber: %s\n",name,age,number);
}