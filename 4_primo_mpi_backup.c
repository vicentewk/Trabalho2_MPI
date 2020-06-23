#include "mpi.h"
#include <stdio.h>
#include "tempo.h"
#include <stdlib.h>

int fprimo(int);

int main(int argc, char *argv[])
{

	int n;

	MPI_Status status;
	int myid, numprocs;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);

	tempo1();

	if (myid == 0)
	{

		int numero = 0;
		int fim;
		int m;
		int i = 1;
		int num_calculado = 0;
		int total = 0;
		int total_mestre;
		int totale = 0;

		printf("\nDigite um numero limite: ");
		scanf("%d", &n);

		//int parte = n / numprocs;

		//printf("\nNumero total de processos: %d\n\n", numprocs);
		//mestre 0 envia para todos (1 ate n-1) escravos em ordem de i
		while (num_calculado < n)
		{
			num_calculado++;
			total = fprimo(num_calculado);
			total_mestre = total_mestre + total;
			printf("\n Mestre calculou %d ", num_calculado);
			while (i < numprocs)
			{
				if (num_calculado >= n)
				{
					break;
				}
				else
				{
					num_calculado++;

					MPI_Send(&num_calculado, 1, MPI_INT, i, 4, MPI_COMM_WORLD);
					printf("\n escravo %d recebeu  ---  %d\n", i, num_calculado);

					i++;
				}
			}
			i = 1;
		}

		tempo2();
		tempoFinal("mili segundos", argv[0], MSGLOG);

		//mestre recebe de todos os escravos em qualquer ordem
		for (i = 1; i < numprocs; i++)
		{
			//printf("\n total de primos do mestre: %d", total_mestre);
			MPI_Recv(&m, 1, MPI_INT, MPI_ANY_SOURCE, 4, MPI_COMM_WORLD, &status);
			//printf("\n mestre recebeu = %d  do slave %d\n", m, status.MPI_SOURCE);

			totale += m;
		}
		//totalf = totale + total_mestre;
		printf("\n\nTOTAL de primos é %d \n\n", totale + total_mestre);
	}
	else
	{
		int x = 0;
		int numero_recebido;
		int count;
		int z = 0;

		while (z <= numprocs)
		{
			MPI_Recv(&numero_recebido, 1, MPI_INT, 0, 4, MPI_COMM_WORLD, &status);
		//	printf("\n escravo %d recebeu = %6d \n", myid, numero_recebido);
			x = fprimo(numero_recebido);
			if (x == 1)
			{
				count++;
			}
			z++;
		}

		z = 1;

		//for (int z = 1; z <= numprocs; z++)

		MPI_Send(&count, 1, MPI_INT, 0, 4, MPI_COMM_WORLD);
		printf("\n total de primos %d do escravo %d ", count, myid);
		tempo2();
		tempoFinal("mili segundos do escravo", argv[0], MSGLOG);
	}

	MPI_Finalize();

	return 0;
}

//int fprimo(int inicio, int fim)
int fprimo(int numero_testado)
{
	int i;
	int div;
	int total = 0;

	div = 0;
	//printf("\n função de teste executada com o número %d  ", numero_testado);
	for (i = 1; i <= numero_testado; i++)
	{
		if (numero_testado % i == 0)
		{
			div++;
		}
	}

	if (div == 2)
	{

		return 1;
	}

	return 0;
}

/*
                N  PRIME_NUMBER
                1           0
               10           4
              100          25
            1,000         168
           10,000       1,229
          100,000       9,592
        1,000,000      78,498
       10,000,000     664,579
      100,000,000   5,761,455
    1,000,000,000  50,847,534
*/