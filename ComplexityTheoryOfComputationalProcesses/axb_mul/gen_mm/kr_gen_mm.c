/*
 * Вычисление произведения двух матриц A и B
 * используя алгоритм обычного умножения.
 * */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define MTRX_SIZE 4
#define MTRX_VALUE_MIN_RANGE 50
#define MTRX_VALUE_MAX_RANGE 50

#define VERBOSE 1
#define RANDOM 1

void generate_random_matrix(int **mt, int size)
{
    int i;
    int j;

    (*mt) = (int *) malloc(size * size * sizeof(int));

    #if (RANDOM == 1)
    srand(time(NULL) + rand());
    #else
    int k;
    k = 1;
    #endif

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            #if (RANDOM == 1)
            (*mt)[i * size + j] = rand() % MTRX_VALUE_MIN_RANGE -
                rand() % MTRX_VALUE_MAX_RANGE;
            #else
            (*mt)[i * size + j] = k++; 
            #endif
        }
    }
}

void allocate_matrix_memory(int **mt, int size)
{
    int i;
    int j;
    (*mt) = (int *) malloc(size * size * sizeof(int));
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            (*mt)[i * size + j] = 0;
        }
    }
}

void print_matrix(int *mt, int size)
{
    int i;
    int j;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            printf("%4d ", mt[i * size + j]);
        }
        printf("\n");
    }
    printf("\n");
}

void matrix_mul(int *a, int *b, int **c, int size)
{
    int i;
    int j;
    int k;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            (*c)[i * size + j] = 0;
            for (k = 0; k < size; k++) {
                (*c)[i * size + j] += a[i * size + k] * b[k * size + j]; 
            }
        }
    }
}

int main(int argc, char *argv[])
{
    int *mtrxA;
    int *mtrxB;
    int *mtrxC;
    int mtSize;

    if (argc > 1) {
        mtSize = atoi(argv[1]);
    }
    else {
        mtSize = MTRX_SIZE;
    }

    generate_random_matrix(&mtrxA, mtSize);
    #if (VERBOSE == 1)
    printf("A:\n");
    print_matrix(mtrxA, mtSize);
    #endif

    generate_random_matrix(&mtrxB, mtSize);
    #if (VERBOSE == 1)
    printf("B:\n");
    print_matrix(mtrxB, mtSize);
    #endif
    
    allocate_matrix_memory(&mtrxC, mtSize);
    matrix_mul(mtrxA, mtrxB, &mtrxC, mtSize);
    #if (VERBOSE == 1)
    printf("C:\n");
    print_matrix(mtrxC, mtSize);
    #endif

    return 0;
}
