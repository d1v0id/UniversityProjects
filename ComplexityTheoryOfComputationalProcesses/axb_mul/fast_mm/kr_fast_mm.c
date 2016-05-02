/*
 * Вычисление произведения двух матриц A и B
 * используя алгоритм быстрого умножения.
 *
 * При перемножении двух матриц n x n разделим
 * каждую из них на 4 матрицы вдвое меньшего размера:
 *
 * A = /A1 A2\ B = /B1 B2\ Ai, Bi = n/2 x n/2
 *     \A3 A4/     \B3 B4/
 *
 * M1 = (A2 - A4)(B3 + B4)
 * M2 = (A1 + A4)(B1 + B4)
 * M3 = (A1 - A3)(B1 + B2)
 * M4 = (A1 + A2)B4
 * M5 = A1(B2 - B4)
 * M6 = A4(B3 - B1)
 * M7 = (A3 + A4)B1
 * C1 = M1 + M2 - M4 + M6
 * C2 = M4 + M5
 * C3 = M6 + M7
 * C4 = M2 - M3 + M5 - M7
 * */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define MTRX_SIZE 4
#define MTRX_VALUE_MIN_RANGE 50
#define MTRX_VALUE_MAX_RANGE 50

#define DEBUG 0
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

void div_matrix_on_parts(int *a, int **a1, int **a2, int **a3, int **a4, int size)
{
    int i;
    int j;
    int n = size / 2;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if ((i < n) && (j < n)) {
                (*a1)[i * n + j] = a[i * size + j];
            }
            if ((i < n) && (j >= n)) {
                (*a2)[i * n + j - n] = a[i * size + j];
            }
            if ((i >= n) && (j < n)) {
                (*a3)[(i - n) * n + j] = a[i * size + j];
            }
            if ((i >= n) && (j >= n)) {
                (*a4)[(i - n) * n + j - n] = a[i * size + j];
            }
        }
    }
}

void combine_matrix_from_parts(int **a, int *a1, int *a2, int *a3, int *a4, int size)
{
    int i;
    int j;
    int n = size / 2;
    
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if ((i < n) && (j < n)) {
                (*a)[i * size + j] = a1[i * n + j];
            }
            if ((i < n) && (j >= n)) {
                (*a)[i * size + j] = a2[i * n + j - n];
            }
            if ((i >= n) && (j < n)) {
                (*a)[i * size + j] = a3[(i - n) * n + j];
            }
            if ((i >= n) && (j >= n)) {
                (*a)[i * size + j] = a4[(i - n) * n + j - n];
            }
        }
    }
}

void matrix_add(int *a, int *b, int **c, int size)
{
    int i;
    int j;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
                (*c)[i * size + j] = a[i * size + j] + b[i * size + j]; 
        }
    }
}

void matrix_sub(int *a, int *b, int **c, int size)
{
    int i;
    int j;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
                (*c)[i * size + j] = a[i * size + j] - b[i * size + j]; 
        }
    }
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
    int *mtrxA, *a1, *a2, *a3, *a4;
    int *mtrxB, *b1, *b2, *b3, *b4;
    int *mtrxC, *c1, *c2, *c3, *c4;
    int *m1, *m2, *m3, *m4, *m5, *m6, *m7;
    int *tmp1, *tmp2;

    int mtSize;
    if (argc > 1) {
        mtSize = atoi(argv[1]);
    }
    else {
        mtSize = MTRX_SIZE;
    }

    int size = mtSize / 2;

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
    

    allocate_matrix_memory(&a1, size);
    allocate_matrix_memory(&a2, size);
    allocate_matrix_memory(&a3, size);
    allocate_matrix_memory(&a4, size);
    div_matrix_on_parts(mtrxA, &a1, &a2, &a3, &a4, mtSize);

    #if (DEBUG == 1)
    printf("A1:\n");
    print_matrix(a1, size);
    printf("A2:\n");
    print_matrix(a2, size);
    printf("A3:\n");
    print_matrix(a3, size);
    printf("A4:\n");
    print_matrix(a4, size);
    #endif


    allocate_matrix_memory(&b1, size);
    allocate_matrix_memory(&b2, size);
    allocate_matrix_memory(&b3, size);
    allocate_matrix_memory(&b4, size);
    div_matrix_on_parts(mtrxB, &b1, &b2, &b3, &b4, mtSize);

    #if (DEBUG == 1)
    printf("B1:\n");
    print_matrix(b1, size);
    printf("B2:\n");
    print_matrix(b2, size);
    printf("B3:\n");
    print_matrix(b3, size);
    printf("B4:\n");
    print_matrix(b4, size);
    #endif

    
    allocate_matrix_memory(&m1, size);
    allocate_matrix_memory(&m2, size);
    allocate_matrix_memory(&m3, size);
    allocate_matrix_memory(&m4, size);
    allocate_matrix_memory(&m5, size);
    allocate_matrix_memory(&m6, size);
    allocate_matrix_memory(&m7, size);
    allocate_matrix_memory(&tmp1, size);
    allocate_matrix_memory(&tmp2, size);

    // m1 = (a2 - a4)(b3 + b4)
    matrix_sub(a2, a4, &tmp1, size);
    matrix_add(b3, b4, &tmp2, size);
    matrix_mul(tmp1, tmp2, &m1, size);
    #if (DEBUG == 1)
    printf("M1:\n");
    print_matrix(m1, size);
    #endif

    // m2 = (a1 + a4)(b1 + b4)
    matrix_add(a1, a4, &tmp1, size);
    matrix_add(b1, b4, &tmp2, size);
    matrix_mul(tmp1, tmp2, &m2, size);
    #if (DEBUG == 1)
    printf("M2:\n");
    print_matrix(m2, size);
    #endif

    // m3 = (a1 - a3)(b1 + b2)
    matrix_sub(a1, a3, &tmp1, size);
    matrix_add(b1, b2, &tmp2, size);
    matrix_mul(tmp1, tmp2, &m3, size);
    #if (DEBUG == 1)
    printf("M3:\n");
    print_matrix(m3, size);
    #endif

    // m4 = (a1 + a2)b4
    matrix_add(a1, a2, &tmp1, size);
    matrix_mul(tmp1, b4, &m4, size);
    #if (DEBUG == 1)
    printf("M4:\n");
    print_matrix(m4, size);
    #endif

    // m5 = a1(b2 - b4)
    matrix_sub(b2, b4, &tmp1, size);
    matrix_mul(a1, tmp1, &m5, size);
    #if (DEBUG == 1)
    printf("M5:\n");
    print_matrix(m5, size);
    #endif

    // m6 = a4(b3 - b1)
    matrix_sub(b3, b1, &tmp1, size);
    matrix_mul(a4, tmp1, &m6, size);
    #if (DEBUG == 1)
    printf("M6:\n");
    print_matrix(m6, size);
    #endif

    // m7 = (a3 + a4)b1
    matrix_add(a3, a4, &tmp1, size);
    matrix_mul(tmp1, b1, &m7, size);
    #if (DEBUG == 1)
    printf("M7:\n");
    print_matrix(m7, size);
    #endif


    allocate_matrix_memory(&c1, size);
    allocate_matrix_memory(&c2, size);
    allocate_matrix_memory(&c3, size);
    allocate_matrix_memory(&c4, size);

    // c1 = m1 + m2 - m4 + m6
    matrix_add(m1, m2, &tmp1, size);
    matrix_sub(tmp1, m4, &tmp2, size);
    matrix_add(tmp2, m6, &c1, size);
    #if (DEBUG == 1)
    printf("C1:\n");
    print_matrix(c1, size);
    #endif

    // c2 = m4 + m5
    matrix_add(m4, m5, &c2, size);
    #if (DEBUG == 1)
    printf("C2:\n");
    print_matrix(c2, size);
    #endif

    // c3 = m6 + m7
    matrix_add(m6, m7, &c3, size);
    #if (DEBUG == 1)
    printf("C3:\n");
    print_matrix(c3, size);
    #endif

    // c4 = m2 - m3 + m5 - m7
    matrix_sub(m2, m3, &tmp1, size);
    matrix_add(tmp1, m5, &tmp2, size);
    matrix_sub(tmp2, m7, &c4, size);
    #if (DEBUG == 1)
    printf("C4:\n");
    print_matrix(c4, size);
    #endif


    allocate_matrix_memory(&mtrxC, mtSize);

    combine_matrix_from_parts(&mtrxC, c1, c2, c3, c4, mtSize);
    #if (VERBOSE == 1)
    printf("C:\n");
    print_matrix(mtrxC, mtSize);
    #endif

    return 0;
}
