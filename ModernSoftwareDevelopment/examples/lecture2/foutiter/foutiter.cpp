#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <list>

using namespace std;

int main()
{
    int arr[] = { 11, 21, 31, 41, 51 };
    list<int> theList;

    for (int i = 0; i < 5; i++) {
        theList.push_back(arr[i]);
    }

    ofstream outfile("iter.dat");
    ostream_iterator<int> ositer(outfile, " ");
    copy(theList.begin(), theList.end(), ositer);

    return 0;
}
