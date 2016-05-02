#include <iostream>
#include <set>
#include <string>

using namespace std;

int main()
{
    string names[] = { "Juanita", "Robert", "Mary", "Amanda", "Marie" };
    set<string, less<string> > nameSet(names, names + 5);
    set<string, less<string> >::iterator iter;
    
    nameSet.insert("Yvette");
    nameSet.insert("Larry");
    nameSet.insert("Robert");
    nameSet.insert("Barry");
    nameSet.erase("Mary");

    cout << "Size = " << nameSet.size() << endl;
    iter = nameSet.begin();
    while (iter != nameSet.end()) {
        cout << *iter++ << " ";
    }
    cout << endl;

    string searchName;
    cout << "Input name for search: ";
    cin >> searchName;

    iter = nameSet.find(searchName);
    if (iter == nameSet.end()) {
        cout << "Name " << searchName << " is not in set.";
    }
    else {
        cout << "Name " << *iter << " in set.";
    }
    cout << endl;

    return 0;
}
