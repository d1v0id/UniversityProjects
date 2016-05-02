#include <stdio.h>
#include <time.h>

#define SIZE 5
#define MAX_VALUE 100

int arr[SIZE];

void swap(int a, int b)
{
    int tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
}

void bubble_sort()
{
    int i;
    int j;

    int flag = 0;
    for (i = 0; i < SIZE; i++) {
        for (j = SIZE-1; j > i; j--) {
            if (arr[j-1] > arr[j]) {
                swap(j-1, j);
                flag = 1;
            }
        }
        if (flag == 0) break;
        for (j = 0; j < SIZE; j++) {
            printf("%d ", arr[j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    int i;

    srand(time(NULL));
    for (i = 0; i < SIZE; i++) {
        arr[i] = rand() % MAX_VALUE;
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    bubble_sort();

    printf("\n");
    for (i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
