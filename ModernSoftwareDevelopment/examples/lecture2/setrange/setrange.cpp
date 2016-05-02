#include <iostream>
#include <set>
#include <string>

using namespace std;

int main()
{
    set<string, less<string> > organic;
    set<string, less<string> >::iterator iter;

    organic.insert("Curine");
    organic.insert("Xanthine");
    organic.insert("Malamine");
    organic.insert("Cyanimide");
    organic.insert("Phenol");
    organic.insert("Aphrodine");
    organic.insert("Imidazole");
    organic.insert("Cinchonine");
    organic.insert("Palmitamide");
    organic.insert("Cyanimide");

    iter = organic.begin();
    while (iter != organic.end()) {
        cout << *iter++ << " ";
    }
    cout << endl;

    string lower, upper;
    cout << "Input range (e.g. C Czz): ";
    cin >> lower >> upper;
    iter = organic.lower_bound(lower);
    while (iter != organic.upper_bound(upper)) {
        cout << *iter++ << " ";
    }
    cout << endl;

    return 0;
}
