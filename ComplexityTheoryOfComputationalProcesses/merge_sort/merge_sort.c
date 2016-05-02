#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 8

void generate_random_array(int *a, int size)
{
    srand(time(NULL) + rand());
    int i;
    for (i = 0; i < size; i++) {
        a[i] = rand() % 99 + 1;
    }
}

void print_array(int *a, int size)
{
    int i;
    for (i = 0; i < size; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void merge_sort(int *a, int size)
{
    int *b;
    int right, wid, rend;
    int i, j, m, t;
    int k, left;

    b = (int *) malloc(size * sizeof(int));

    for (k = 1; k < size; k *= 2 ) {       
        for (left = 0; left + k < size; left += k * 2 ) {
            right = left + k;
            rend = right + k;

            if (rend > size) {
                rend = size;
            }

            m = left;
            i = left;
            j = right;

            while (i < right && j < rend) {
                if (a[i] <= a[j]) {
                    b[m] = a[i];
                    i++;
                } else {
                    b[m] = a[j];
                    j++;
                }
                m++;
            }

            while (i < right) {
                b[m] = a[i];
                i++;
                m++;
            }

            while (j < rend) {
                b[m] = a[j];
                j++;
                m++;
            }

            for (m = left; m < rend; m++) {
                a[m] = b[m];
            }
        }
    }
}

int main(int argc, char *argv[])
{
    int *a;
    a = (int *) malloc(SIZE * sizeof(int));
    generate_random_array(a, SIZE);
    print_array(a, SIZE); 
    merge_sort(a, SIZE);
    print_array(a, SIZE); 

    return 0;
}
