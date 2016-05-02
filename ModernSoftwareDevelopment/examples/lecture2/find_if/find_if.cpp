#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

string names[] = { "Serg", "Tatiana", "Elena", "Dmitry", "Igor", "Vladimir" };

bool isDmitry(string name)
{
    return name == "Dmitry";
}

int main()
{
    string s1 = "Dmitry is not in list.";
    string s2 = "Dmitry at position ";
    string s3 = " in list.";

    string *ptr;
    ptr = find_if(names, names + 5, isDmitry);

    if (ptr == names + 5) {
        cout << s1;
    }
    else {
        cout << s2 << (ptr - names) << s3;
    }
    cout << endl;

    return 0;
}
