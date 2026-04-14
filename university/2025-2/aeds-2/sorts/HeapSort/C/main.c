#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int numero;
    struct No dir;
    struct No esq;
}No;

No* newNo(int x)
{
    No* temp =(No*) malloc(sizeof(No));
    No
}