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

void selection_sort()
{
    int i;
    int j;
    for (i = 0; i < SIZE-1; i++) {
        int min = i;
        for (j = i+1; j < SIZE; j++) {
            if(arr[j] < arr[min]) {
                min = j;
            }
        }
        if (arr[min] != arr[i]) {
            swap(i, min);
        }
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
    printf("\n");

    selection_sort();

    for (i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
