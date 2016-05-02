#include <iostream>
#include <string>
#include <algorithm>
#include <string>

using namespace std;

string names[] = { "Serg", "Tatiana", "Elena", "Dmitry", "Mihail", "Vladimir" };

bool alpha_comp(string s1, string s2)
{
    return s1.compare(s2) < 0;
}

int main()
{
    sort(names, names + 6, alpha_comp);
    for (int i = 0; i < 6; i++) {
        cout << names[i] << " ";
    }
    cout << endl;

    return 0;
}
