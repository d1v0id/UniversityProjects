#include <stdio.h>

#define N 20
#define M 3

const int am[3] = { 3, 7, 8 };
const int ac[3] = { 8, 20, 23 };

int mymax(int a, int b, int c) {
    if ((a > b) && (a > c)) {
        return a;
    } else if ((b > a) && (b > c)) {
        return b;
    } else {
        return c;
    }
}

int main(int argc, char **argv)
{
    int res[N];
    int tmp[M];
    int back[N];
    int i;
    int j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            if ((i - am[j]) >= 0) {
                tmp[j] = res[i - am[j]] + ac[j];
            }
            else {
                tmp[j] = 0;
            }
        }
        res[i] = mymax(tmp[0], tmp[1], tmp[2]);

        if (res[i] == tmp[0]) {
            back[i] = am[0];
        }
        if (res[i] == tmp[1]) {
            back[i] = am[1];
        }
        if (res[i] == tmp[2]) {
            back[i] = am[2];
        }

        printf("f(%d) = %d\n", i, res[i]);
    }

    for (i = N-1; i >= 0; i--) {
        printf("back[%d] = %d\n", i, back[i]);
    }

    return 0;
}
