#include <iterator>
#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>

using namespace std;

int main()
{
    list<float> fList(5);

    cout << "Input 5 numbers (type float): ";
    istream_iterator<float> cin_iter(cin);
    istream_iterator<float> end_of_stream;
    copy(cin_iter, end_of_stream, fList.begin());
    cout << endl;

    ostream_iterator<float> ositer(cout, "--");
    copy(fList.begin(), fList.end(), ositer);
    cout << endl;

    return 0;
}
