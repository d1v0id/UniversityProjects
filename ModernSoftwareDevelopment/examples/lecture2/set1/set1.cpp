#include <iostream>
#include <set>

using namespace std;

int main()
{
    float n[] = { 11, 22, 33, 44, 55 };
    set<float, less<float> > s(n, n + 5);
    set<float, less<float> >::iterator iter;

    s.insert(10);
    s.insert(15);
    s.insert(10);
    s.insert(20);
    s.erase(11);

    cout << "Size = " << s.size() << endl;
    iter = s.begin();
    while (iter != s.end()) {
        cout << *iter++ << " ";
    }
    cout << endl;

    float search;

    cout << "Input number for search: ";
    cin >> search;

    iter = s.find(search);
    if (iter == s.end()) {
        cout << "Number " << search << " is not in set.";
    }
    else {
        cout << "Number " << *iter << " in set.";
    }
    cout << endl;

    return 0;
}
