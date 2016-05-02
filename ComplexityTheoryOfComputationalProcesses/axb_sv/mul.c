/* Свертка матриц */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define N 4
#define M 4

int generate_random(int n)
{
    srand(time(NULL) + rand());
    return rand() % n - rand() % n;
}

int main(int argc, char **argv)
{
    int p, n, m, i, j, k;
    double s;
    double a[N], b[M], c[N * M];
    
    printf("\n");
    printf("A {");
    p = (N - 1) + (M - 1);
    for (i = 0; i < N; i++) {
        a[i] = generate_random(9) + 1;
        printf("%2.0lf ", a[i]);
    }

    printf("}\n");
    printf("B {");

    for (j = 0; j < M; j++) {
        b[j] = generate_random(9) + 1;
        printf("%2.0lf ", b[j]);
    }

    printf ("}\n");

    for (k = 0; k <= p; k++) {
        printf("\nC[%d] = ", k);
        for (i = 0; i < N; i++) {
            for (j = 0; j < M; j++) {
                if (k == i + j) {
                    c[k] += a[i] * b[j];
                    //printf("a[%d] * b[%d] ", i, j);
                    printf("(%.0lf * %.0lf) + ", a[i], b[j]);
                    //printf("\n%d * %d", a[i], b[j]);
                }
            }
        }
        printf(" = %.0lf\n", c[k]);
    }

    for (k = 0; k <= p; k++) {
        s = s + c[k];
    }
    printf ("\nS = %.0lf\n", s);

    return 0;
}
