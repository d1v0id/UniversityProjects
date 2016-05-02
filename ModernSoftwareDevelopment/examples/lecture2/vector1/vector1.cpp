#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <string>

using namespace std;

template <class T>
class Greater
{
public:
    bool operator() (T a, T b)
    {
        return a > b;
    }
};

class A
{
public:
    A(int n = 0, int d = 1): n(n), d(d) {};

    A operator+ (const A b)
    {
        return A((n * b.d + b.n * d), d * b.d);
    }

    bool operator> (const A b)
    {
        return n * b.d > d * b.n;
    }

    string get()
    {
        return to_string(n) + "/" + to_string(d);
    }

private:
    int n;
    int d;
};

int main()
{
    vector<A> m;
    vector<A>::iterator iter;
    m.push_back(A(2));
    m.push_back(A(3));
    m.push_back(A(1));
    m.push_back(A(5));
    m.push_back(A(9));
    m.push_back(A(7));
    
    sort(m.begin(), m.end(), Greater<A>());
    for (iter = m.begin(); iter != m.end(); iter++) {
        cout << iter->get() << " ";
    }
    cout << endl;

    for (int i = 0; i != m.size(); i++) {
        cout << m[i].get() << " ";
    }
    cout << endl;

    //A sum = accumulate(m.begin(), m.end(), A(), plus<A>());
    //cout << sum.get() << endl;

    return 0;
}
