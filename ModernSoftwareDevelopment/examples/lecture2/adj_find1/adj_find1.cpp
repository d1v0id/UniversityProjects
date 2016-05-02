#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <class T>
class F {
public:
    bool operator() (T &a1, T &a2) {
        return a1 == a2;
    }
};

class A {
public:
    A(int n = 0, int d = 1): n(n), d(d) {};

    A operator+ (const A b)
    {
        return A((n * b.d + b.n * d), d * b.d);
    }

    string get()
    {
        string a = to_string(n) + "/" + to_string(d);
        return a;
    }

    bool operator== (const A b)
    {
        return n * b.d == d * b.n;
    }

private:
    int n;
    int d;
};

int main()
{
    vector<A> m;
    m.push_back(A(2));
    m.push_back(A(3));
    m.push_back(A(1, 5));
    m.push_back(A(5));
    m.push_back(A(3, 4));
    m.push_back(A(6, 8));

    cout << (*adjacent_find(m.begin(), m.end(), F<A>())).get() << endl;

    return 0;
}
