#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct person
{
    struct person *parents[2];
    char alleles[2];
} person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *t, int gen);
void free_family(person *t);
char random_allele();

int main(void)
{
    srand(time(0));

    person *t = create_family(GENERATIONS);

    print_family(t, 0);

    free_family(t);
}

person *create_family(int generations)
{
    person *n = malloc(sizeof(person));
    if (n == NULL)
    {
        return NULL;
    }

    if (generations > 1)
    {
        n->parents[0] = create_family(generations - 1);
        n->parents[1] = create_family(generations - 1);

        n->alleles[0] = n->parents[0]->alleles[rand() % 2];
        n->alleles[1] = n->parents[1]->alleles[rand() % 2];
    }

    else
    {
        n->parents[0] = NULL;
        n->parents[1] = NULL;

        n->alleles[0] = random_allele();
        n->alleles[1] = random_allele();
    }

    return n;
}

void free_family(person *t)
{
    if (t == NULL)
    {
        return;
    }

    free_family(t->parents[0]);
    free_family(t->parents[1]);

    free(t);
}

void print_family(person *t, int gen)
{
    if (t == NULL)
    {
        return;
    }

    for (int i = 0; i < gen * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    printf("gen %i, blood type %c%c\n", gen, t->alleles[0], t->alleles[1]);
    print_family(t->parents[0], gen + 1);
    print_family(t->parents[1], gen + 1);
}

char random_allele()
{
    int a = rand() % 3;
    if (a == 0)
    {
        return 'A';
    }
    else if (a == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}