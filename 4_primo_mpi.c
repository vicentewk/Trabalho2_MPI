#include "mpi.h"
#include <stdio.h>
#include "tempo.h"
#include <stdlib.h>

int fprimo(int);

int main(int argc, char *argv[])
{
	int j = 0;
	int total2 = 0;
	int total3 = 0;
	int totalf = 0;
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

		int total = 0;

		printf("\nDigite um numero limite: ");
		scanf("%d", &n);

		//int parte = n / numprocs;

		//printf("\nNumero total de processos: %d\n\n", numprocs);
		//mestre 0 envia para todos (1 ate n-1) escravos em ordem de i
		while (j < n)
		{

			j++;

			total = fprimo(j);
			total2 = total2 + total;
			printf("\n Mestre calculou %d ", j);
			while (i < numprocs)
			//for (i = 1; i < numprocs; i++)
			{
				if (j == n)
				{
					break;
				}
				else
				{
					j++;
					MPI_Send(&j, 1, MPI_INT, i, 4, MPI_COMM_WORLD);
					//printf("\n escravo %d recebeu  ---  %d\n", i, j);

					i++;
				}
			}
			i = 1;
		}

		tempo2();
		//tempoFinal("mili segundos", argv[0], MSGLOG);

		//mestre recebe de todos os escravos em qualquer ordem
		for (i = 1; i < numprocs; i++)
		{

			MPI_Recv(&m, 1, MPI_INT, MPI_ANY_SOURCE, 4, MPI_COMM_WORLD, &status);
			printf("\n mestre recebeu = %d  do slave %d\n", m, status.MPI_SOURCE);
		}
		totalf = total2 + m;
		printf("\n\nTOTAL de primos é %d \n\n", totalf);
	}
	else
	{
		int numero;
		int i = 1;
		int x = 0;
		int z = 0;
		int w = 1;

		while (z < n)
		{

			while (w < numprocs)
			//for (i = 1; i < numprocs; i++)
			{
				if (z == n)
				{
					break;
				}
				else
				{
					z++;
					MPI_Recv(&numero, 1, MPI_INT, 0, 4, MPI_COMM_WORLD, &status);
					printf("\n escravo %d recebeu = %6d \n", myid, numero);
					x = x + fprimo(numero);

					w++;
				}
			}
			w = 1;
		}

		total3 = total3 + x;
		MPI_Send(&total3, 1, MPI_INT, 0, 4, MPI_COMM_WORLD);

		tempo2();
		//tempoFinal("mili segundos", argv[0], MSGLOG);

		/**for (i = 1; i < numprocs; i++)
		{
			MPI_Recv(&numero, 1, MPI_INT, 0, 4, MPI_COMM_WORLD, &status);
			printf("\n escravo %d recebeu = %6d \n", myid, numero);
			x = x + fprimo(numero);
		}
			total3 = total3 + x;
		MPI_Send(&total3, 1, MPI_INT, 0, 4, MPI_COMM_WORLD);
		i = 1;
		tempo2();
		tempoFinal("mili segundos", argv[0], MSGLOG);**/
	}

	MPI_Finalize();

	return 0;
}

//int fprimo(int inicio, int fim)
int fprimo(int numero)
{
	int i;
	int x = numero;
	int primo;
	int div;
	int total = 0;

	//printf("\nNumeros primos: ");

	//for ( x = inicio; x <= fim; x++ )
	//{
	div = 0;
	for (i = 1; i <= x; i++)
	{
		if (x % i == 0)
		{
			div++;
		}
	}

	if (div == 2)
	{
		//printf("%d ", x);
		total = total + 1;
	}
	//}
	//printf("\n função de teste executada com o número %d  ", x);
	//printf("\n\nQtde de primos entre %d e %d é %d \n", inicio, fim, total);

	return total;
}
