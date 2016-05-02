#include <stdio.h>
#include <stdlib.h>

#define MATRIX_SIZE 1000 /* размер матриц по умолчанию */

/* герерирует случайное дробное число */
double genDoubleRand(double min, double max)
{
	double f = (double)rand() / RAND_MAX;
	return min + f * (max - min);
}

/* выделяет память под матрицу */
void allocateMemoryMatrix(double*** ptrMatrix, size_t mtSize)
{
	unsigned int i;

	/* выделение памяти под матрицу */
	(*ptrMatrix) = (double**)malloc(mtSize * sizeof(double*));
	for (i = 0; i < mtSize; i++) {
		(*ptrMatrix)[i] = (double*)malloc(mtSize * sizeof(double));
	}
}

/* заполняет матрицу случайными числами */
void generateRandomMatrix(double*** ptrMatrix, size_t mtSize)
{
	unsigned int i, j;

	/* заполнение матрицы */
	for (i = 0; i < mtSize; i++) {
		for (j = 0; j < mtSize; j++) {
			(*ptrMatrix)[i][j] = genDoubleRand(0, 100);
		}
	}
}

/* освобождает память от матрицы */
void freeMemoryMatrix(double*** ptrMatrix, size_t mtSize)
{
	unsigned int i;

	for (i = 0; i < mtSize; i++) {
		free((*ptrMatrix)[i]);
	}
	free(*ptrMatrix);
}

/* выводит матрицу на экран */
void printMatrix(double** ptrMatrix, size_t mtSize)
{
	unsigned int i, j;
	
	/* вывод на экран */
	for (i = 0; i < mtSize; i++) {
		for (j = 0; j < mtSize; j++) {
			printf("%4.2f\t", ptrMatrix[i][j]);
		}
		printf("\n");
	}
}

/* умножение матриц */
void matrixMul(double* a, double* b, double** c, long mtSize)
{
	unsigned int i, j, k;
	for (i = 0; i < mtSize; i++) {
		for (j = 0; j < mtSize; j++) {
			(*c)[i * mtSize + j] = 0;
			for (k = 0; k < mtSize; k++) {
				(*c)[i * mtSize + j] += a[i * mtSize + k] * b[j * mtSize + k];
			}
		}
	}
}

int main(int argc, char* argv[])
{
	unsigned int i, j, size; /* счетчики и размер матриц */
	unsigned long int n = 0; /* размер всей матрицы(строки * столбцы) */

	/* проверка передачи размера в параметре */
	if (argv[1] == NULL) {
		size = MATRIX_SIZE;
	}
	else {
		size = atoi(argv[1]);
	}

	/* матрицы */
	double** a;
	double** b;
	double** c;

	double* mtA;
	double* mtB;
	double* mtC;

	/* формируем исходные матрицы */
	allocateMemoryMatrix(&a, size);
	generateRandomMatrix(&a, size);

	allocateMemoryMatrix(&b, size);
	generateRandomMatrix(&b, size);

	allocateMemoryMatrix(&c, size);
	
	mtA = (double*)malloc(size * size * sizeof(double)); 
	mtB = (double*)malloc(size * size * sizeof(double)); 
	mtC = (double*)malloc(size * size * sizeof(double)); 

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			mtA[n] = a[i][j];
			mtB[n] = b[j][i];
			n++;
		}
	}

	/* вывод матриц на экран */
	/*printf("A:\n");
	printMatrix(a, size);

	printf("\nB:\n");
	printMatrix(b, size);

	printf("\nA: ");
	for (i = 0; i < n; i++) {
		printf("%4.2f ", mtA[i]);
	}
	printf("\n");

	printf("\nB: ");
	for (i = 0; i < n; i++) {
		printf("%4.2f ", mtB[i]);
	}
	printf("\n");*/

	/* умножение матриц */
	matrixMul(mtA, mtB, &mtC, size);

	/*printf("\nC: ");
	for (i = 0; i < n; i++) {
		printf("%4.2f ", mtC[i]);
	}
	printf("\n");*/

	/* освобождение памяти */
	free(mtA);
	free(mtB);
	free(mtC);

	freeMemoryMatrix(&a, size);
	freeMemoryMatrix(&b, size);
	freeMemoryMatrix(&c, size);

	return 0;
}
