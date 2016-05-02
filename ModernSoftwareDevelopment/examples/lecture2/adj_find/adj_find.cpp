#include <algorithm>
#include <iostream>

using namespace std;

struct A {
    int x;
    int y;
};

bool f(A &a1, A &a2)
{
    return a1.x + a1.y == a2.x + a2.y;
}

int main()
{
    int m[8] = { 45, 60, 60, 25, 25, 2, 13, 35 };
    cout << *(adjacent_find(m, m + 8)) << endl;

    A ma[5] = { {2, 4}, {3, 1}, {2, 2}, {1, 2}, {1, 2} };
    cout << (*adjacent_find(ma, ma + 5, f)).x << endl;

    return 0;
}
