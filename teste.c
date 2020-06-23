#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define TAM 100
#define PART TAM / 4
int i, j = 0;

int vet1[PART];
int vet2[PART];
int vet3[PART];
int vet4[PART];
int main(int argc, char *argv[])
{

    for (i = 0; i <= PART; i++)
    {
        if (i == 0)
        {
            vet1[i] = 1;
            vet2[i] = 2;
            vet3[i] = 3;
            vet4[i] = 4;
        }
        else
        {
            vet1[i] = (vet1[i - 1] + 4);
            vet2[i] = (vet2[i - 1] + 4);
            vet3[i] = (vet3[i - 1] + 4);
            vet4[i] = (vet4[i - 1] + 4);
        }
    }

    for (i = 0; i < PART; i++)
    {
        printf("%d  |", vet1[i]);
    }
    printf("\n");
    for (i = 0; i < PART; i++)
    {
        printf("%d  |", vet2[i]);
    }
    printf("\n");
    for (i = 0; i < PART; i++)
    {
        printf("%d  |", vet3[i]);
    }
    printf("\n");
    for (i = 0; i < PART; i++)
    {
 
        printf("%d  |", vet4[i]);
    }
    printf("\n");
}

void inicializa_vetor()
{
    for (int i = 0; i <= PART; i++)
    {
        vet1[i] = '0';
        vet2[i] = '0';
        vet3[i] = '0';
    }
}