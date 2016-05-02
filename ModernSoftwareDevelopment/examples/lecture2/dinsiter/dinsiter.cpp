#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

int main()
{
    int arr1[] = { 1, 3, 5, 7, 9 };
    int arr2[] = { 2, 4, 6 };
    deque<int> d1;
    deque<int> d2;

    for (int i = 0; i < 5; i++) {
        d1.push_back(arr1[i]);
    }

    for (int i = 0; i < 3; i++) {
        d2.push_back(arr2[i]);
    }

    //copy(d1.begin(), d1.end(), back_inserter(d2));
    //copy(d1.begin(), d1.end(), front_inserter(d2));
    copy(d1.begin(), d1.end(), inserter(d2, d2.begin()));

    for (int i = 0; i < d2.size(); i++) {
        cout << d2[i] << " ";
    }
    cout << endl;

    return 0;
}
