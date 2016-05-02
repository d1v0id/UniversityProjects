/*
 * Характеристикой столбца целочисленной матрицы назовем
 * сумму модулей его отрицательных нечетных элементов.
 * Переставляя столбцы заданной матрицы, расположить их в
 * соответствии с ростом характеристик.
 *
 * Составить и исследовать ССП в линейной и графовой форме.
 * Указать интерпретацию ССП и составить протокол выполнения программы.
 * Построить и исследовать инварианты и ограничения цикла(ов).
 * Доказать частичную и полную правильность программы.
 * Представить схему программы в виде сети Петри и осуществить анализ
 * ее свойств на основе дерева достижимости.
 * */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define MTRX_ROW_SIZE 4
#define MTRX_COL_SIZE 4
#define MTRX_VALUE_MIN_RANGE 50
#define MTRX_VALUE_MAX_RANGE 50

void generate_random_matrix(int ***mt, int rowSize, int colSize)
{
    int i;
    int j;
    (*mt) = (int **) malloc(rowSize * sizeof(int *));

    srand(time(NULL));
    for (i = 0; i < rowSize; i++) {
        (*mt)[i] = (int *) malloc(colSize * sizeof(int));
        for (j = 0; j < colSize; j++) {
            (*mt)[i][j] = rand() % MTRX_VALUE_MIN_RANGE -
                rand() % MTRX_VALUE_MAX_RANGE;
        }
    }
}

void print_matrix(int **mt, int rowSize, int colSize)
{
    int i;
    int j;

    for (i = 0; i < rowSize; i++) {
        for (j = 0; j < colSize; j++) {
            printf("%4d ", mt[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int compute_col_characteristic(int **mt, int col, int rowSize)
{
    int i;
    int sum = 0;
    for (i = 0; i < rowSize; i++) {
        if ( (mt[i][col] < 0) && ((mt[i][col] % 2) != 0) ) {
            sum += abs(mt[i][col]);
        }
    }
    return sum;
}

void sort_matrix_by_characteristic(int ***mt, int rowSize, int colSize)
{
    int i;
    int j;
    int k;
    int tmp;
    int *srtLst = (int *) malloc(colSize * sizeof(int));

    for (i = 0; i < colSize; i++) {
        srtLst[i] = compute_col_characteristic((*mt), i, rowSize);
    }

    printf(">> ");
    for (i = 0; i < colSize; i++) {
        printf("%d ", srtLst[i]);
    }
    printf("\n");

    for (i = 0; i < colSize; i++) {
        for (j = colSize - 1; j > i; j--) {
            if (srtLst[j-1] > srtLst[j]) {
                tmp = srtLst[j-1];
                srtLst[j-1] = srtLst[j];
                srtLst[j] = tmp;

                for (k = 0; k < rowSize; k++) {
                    tmp = (*mt)[k][j-1];
                    (*mt)[k][j-1] = (*mt)[k][j];
                    (*mt)[k][j] = tmp;
                }
            }
        }
    }

    printf("<< ");
    for (i = 0; i < colSize; i++) {
        printf("%d ", srtLst[i]);
    }
    printf("\n\n");
}

int main(int argc, char *argv[])
{
    int **mtrx;
    int mtRowSize = MTRX_ROW_SIZE;
    int mtColSize = MTRX_COL_SIZE;

    generate_random_matrix(&mtrx, mtRowSize, mtColSize);
    print_matrix(mtrx, mtRowSize, mtColSize);

    sort_matrix_by_characteristic(&mtrx, mtRowSize, mtColSize);
    print_matrix(mtrx, mtRowSize, mtColSize);

    return 0;
}
