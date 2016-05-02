#include <iostream>
#include <list>

using namespace std;

int main()
{
    list<int> ilist;

    ilist.push_back(30);
    ilist.push_back(40);
    ilist.push_back(20);
    ilist.push_back(10);

    int size = ilist.size();

    for (int i = 0; i < size; i++) {
        cout << ilist.front() << " ";
        ilist.pop_front();
    }
    cout << endl;

    return 0;
}
