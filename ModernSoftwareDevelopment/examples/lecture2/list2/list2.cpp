#include <iostream>
#include <list>

using namespace std;

int main()
{
    list<int> list1, list2;
    int arr1[] = { 40, 30, 20, 10 };
    int arr2[] = { 15, 20, 25, 30, 35 };

    for (int i = 0; i < 4; i++) {
        list1.push_back(arr1[i]);
    }

    for (int i = 0; i < 5; i++) {
        list2.push_back(arr2[i]);
    }

    list1.reverse();
    list1.merge(list2);
    list1.unique();

    while(!list1.empty()) {
        cout << list1.front() << " ";
        list1.pop_front();
    }
    cout << endl;

    return 0;
}
