#include <iostream>
#include <set>
#include <string>

using namespace std;

int main()
{
    float m[] = { 1.11, 2.22, 3.33, 4.44, 5.55, 6.66 };
    set<float, less<float> > s;
    set<float, less<float> >::iterator iter;

    s.insert(7);

    for (int i = 0; i < 6; i++) {
        s.insert(m[i]);
    }

    iter = s.begin();
    while (iter != s.end()) {
        cout << *iter++ << " ";
    }
    cout << endl;

    float lower, upper;
    cout << "Input range(e.g. 1 6): ";
    cin >> lower >> upper;
    iter = s.lower_bound(lower);
    while (iter != s.upper_bound(upper)) {
        cout << *iter++ << " ";
    }
    cout << endl;

    return 0;
}
