#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int arr[] = { 33, 22, 33, 44, 33, 55, 66, 77 };

int main()
{
    string s1 = "Count of number 33 is ";
    string s2 = " time(s) in array.";

    int n = count(arr, arr + 8, 33);
    cout << s1 << n << s2 << endl;

    return 0;
}
