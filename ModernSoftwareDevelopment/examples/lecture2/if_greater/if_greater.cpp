#include <iostream>

using namespace std;

template <class T>
class Greater {
public:
    bool operator() (T a, T b)
    {
        return a > b;
    }
};

int main()
{
    Greater<int> x;
    cout << x(4, 5) << endl;
    cout << x.operator() (3, 2) << endl;
    cout << Greater<int>() (3, 2) << endl;

    return 0;
}
