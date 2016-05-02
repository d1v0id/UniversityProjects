/*
 * Контрольная работа по архитектуре вычислительных систем
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#define MASTER_TO_SLAVE_TAG 1 /* тег для сообщений от master к slave */
#define SLAVE_TO_MASTER_TAG 4 /* тег для сообщений от slave к master */ 

#define DEBUG 0
#define VERBOSE 0 

unsigned int i, j, k; 
unsigned int mtSize; /* размер матриц */
unsigned int low_bound; /* нижний диапазон количества строк матрицы A выделенных для slave */
unsigned int upper_bound; /* верхний диапазон количества строк матрицы A выделенных для slave */
unsigned int portion; /* часть количества строк матрицы A выделенных для slave */
int rank; /* номер текущего процесса */
int size; /* количество процессов */
double* a; 
double* b; 
double* c; 
double start_time; /* время начала вычислений */
double end_time; /* время конца вычислений */
MPI_Status status; /* хранит статус MPI_Recv */
MPI_Request request; /* получает ответ MPI_Isend */

/* герерирует случайное дробное число */
double genDoubleRand(double min, double max)
{
	double f = (double)rand() / RAND_MAX;
	return min + f * (max - min);
}

/* заполняет матрицу случайными числами */
void generateRandomMatrix(double** ptrMatrix, unsigned short int mtSize)
{
	unsigned short int i, j;
	for (i = 0; i < mtSize; i++) {
		for (j = 0; j < mtSize; j++) {
			(*ptrMatrix)[i * mtSize + j] = genDoubleRand(0, 100);
		}
	}
}

/* выводит матрицы на экран */
void printMatrix(double* matrix, unsigned short int mtSize)
{
	unsigned short int i, j;
	for (i = 0; i < mtSize; i++) {
		for (j = 0; j < mtSize; j++) {
			printf("%4.2f\t", matrix[i * mtSize + j]);
		}
		printf("\n");
	}
}

int main(int argc, char *argv[])
{
	/* проверяем входные параметры */
	mtSize = 1000; /* значение по умолчанию */
	if (argc > 1) {
		if ( (strcmp(argv[1], "-s") == 0) ||
		     (strcmp(argv[1], "--size") == 0) ) {
			mtSize = atol(argv[2]);
		}
	}

	/* выделяем память под массивы для матриц */
	a = (double*)malloc(mtSize * mtSize * sizeof(double));
	b = (double*)malloc(mtSize * mtSize * sizeof(double));
	c = (double*)malloc(mtSize * mtSize * sizeof(double));

	/* инициализация параллельной библиотеки */
	MPI_Init(&argc, &argv); 
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0) {
		/* формируем исходные матрицы */
		generateRandomMatrix(&a, mtSize);
		generateRandomMatrix(&b, mtSize);
		#if (VERBOSE == 1)
		printf("A:\n");
		printMatrix(a, mtSize);
		printf("\nB:\n");
		printMatrix(b, mtSize);
		printf("\n");
		#endif

		/* засекаем время */
		start_time = MPI_Wtime();
		for (i = 1; i < size; i++) { /* для кажлого slave */
			portion = (mtSize / (size - 1)); /* вычисление части для расчета */ 
			low_bound = (i - 1) * portion;
			if (((i + 1) == size) && ((mtSize % (size - 1)) != 0)) { 
				upper_bound = mtSize; 
			} else {
				upper_bound = low_bound + portion; 
			}
			/* отправка без блокировок */
			MPI_Isend(&low_bound, 1, MPI_INT, i, MASTER_TO_SLAVE_TAG, MPI_COMM_WORLD, &request);
			MPI_Isend(&upper_bound, 1, MPI_INT, i, MASTER_TO_SLAVE_TAG + 1, MPI_COMM_WORLD, &request);
			MPI_Isend(&a[low_bound * mtSize + 0], (upper_bound - low_bound) * mtSize, MPI_DOUBLE, i, MASTER_TO_SLAVE_TAG + 2, MPI_COMM_WORLD, &request);
			#if (DEBUG == 1)
			printf("(p1)-> Rank 0 MPI_Isend low_bound = %d to %d\n", low_bound, i);
			printf("(p1)-> Rank 0 MPI_Isend upper_bound = %d to %d\n", upper_bound, i);
			printf("(p1)-> Rank 0 MPI_Isend a[%d][0] = %4.2f to %d\n", low_bound, a[low_bound * mtSize + 0], i);
			#endif
		}
	}
	MPI_Barrier(MPI_COMM_WORLD); /* еще раз подождем пока все дойдут до этого места */

	/* групповая рассылка B всем slave
	 * потому что хоть память и выделена(кстати по этому тут нет & перед b)
	 * случайно она заполнена только у rank 0, у остальных там нули */
	MPI_Bcast(b, mtSize * mtSize, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	#if (DEBUG == 1)
	printf("(p2)-> Rank %d MPI_Bcast b = %4.2f... from 0\n", rank, b[0]);
	#endif

	if (rank > 0) {
		MPI_Recv(&low_bound, 1, MPI_INT, 0, MASTER_TO_SLAVE_TAG, MPI_COMM_WORLD, &status);
		MPI_Recv(&upper_bound, 1, MPI_INT, 0, MASTER_TO_SLAVE_TAG + 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&a[low_bound * mtSize + 0], (upper_bound - low_bound) * mtSize, MPI_DOUBLE, 0, MASTER_TO_SLAVE_TAG + 2, MPI_COMM_WORLD, &status);
		#if (DEBUG == 1)
		printf("(p3)<- Rank %d MPI_Recv low_bound = %d from 0\n", rank, low_bound);
		printf("(p3)<- Rank %d MPI_Recv upper_bound = %d from 0\n", rank, upper_bound);
		printf("(p3)<- Rank %d MPI_Recv a[%d][0] = %4.2f from 0\n", rank, low_bound, a[low_bound * mtSize + 0]);
		#endif
		for (i = low_bound; i < upper_bound; i++) { 
			for (j = 0; j < mtSize; j++) { 
				for (k = 0; k < mtSize; k++) { 
					c[i * mtSize + j] += (a[i * mtSize + k] * b[k * mtSize + j]);
				}
			}
		}
		/* отправка обратно без блокировок */
		MPI_Isend(&low_bound, 1, MPI_INT, 0, SLAVE_TO_MASTER_TAG, MPI_COMM_WORLD, &request);
		MPI_Isend(&upper_bound, 1, MPI_INT, 0, SLAVE_TO_MASTER_TAG + 1, MPI_COMM_WORLD, &request);
		MPI_Isend(&c[low_bound * mtSize + 0], (upper_bound - low_bound) * mtSize, MPI_DOUBLE, 0, SLAVE_TO_MASTER_TAG + 2, MPI_COMM_WORLD, &request);
		#if (DEBUG == 1)
		printf("(p4)-> Rank %d MPI_Isend low_bound = %d to 0\n", rank, low_bound);
		printf("(p4)-> Rank %d MPI_Isend upper_bound = %d to 0\n", rank, upper_bound);
		printf("(p4)-> Rank %d MPI_Isend c[%d][0] = %4.2f to 0\n", rank, low_bound, c[low_bound * mtSize + 0]);
		#endif
	}
	MPI_Barrier(MPI_COMM_WORLD); /* еще подождем пока все дойдут до этого места */

	if (rank == 0) {
		for (i = 1; i < size; i++) { /* пока все slave не отправят вычисленные данные обрано */
			/* прием данных от slave */
			MPI_Recv(&low_bound, 1, MPI_INT, i, SLAVE_TO_MASTER_TAG, MPI_COMM_WORLD, &status);
			MPI_Recv(&upper_bound, 1, MPI_INT, i, SLAVE_TO_MASTER_TAG + 1, MPI_COMM_WORLD, &status);
			MPI_Recv(&c[low_bound * mtSize + 0], (upper_bound - low_bound) * mtSize, MPI_DOUBLE, i, SLAVE_TO_MASTER_TAG + 2, MPI_COMM_WORLD, &status);
			#if (DEBUG == 1)
			printf("(p5)<- Rank 0 MPI_Recv low_bound = %d from %d\n", low_bound, i);
			printf("(p5)<- Rank 0 MPI_Recv upper_bound = %d from %d\n", upper_bound, i);
			printf("(p5)<- Rank 0 MPI_Recv c[%d][0] = %4.2f from %d\n", low_bound, c[low_bound * mtSize + 0], i);
			#endif
		}
		#if (VERBOSE == 1)	
		printf("\nC:\n");
		printMatrix(c, mtSize);
		#endif

		end_time = MPI_Wtime();
		printf("Running Time = %f\n", end_time - start_time);
	}
	MPI_Barrier(MPI_COMM_WORLD); /* еще раз подождем пока все дойдут до этого места */
	free(a);
	free(b);
	free(c);
	MPI_Finalize(); 
	return 0;
}

