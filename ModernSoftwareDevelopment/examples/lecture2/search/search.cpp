#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int source[] = { 11, 44, 33, 11, 22, 33, 11, 22, 44 };
int pattern[] = { 11, 22, 33 };

int main()
{
    string s1 = "Pattern doesn't match";
    string s2 = "Match in position ";

    int *ptr;
    ptr = search(source, source + 9, pattern, pattern + 3);
    if (ptr == source + 9) {
        cout << s1;
    }
    else {
        cout << s2 << (ptr - source);
    }
    cout << endl;

    return 0;
}
