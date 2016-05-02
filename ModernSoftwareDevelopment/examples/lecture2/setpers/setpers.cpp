#include <iostream>
#include <set>
#include <string>

using namespace std;

class Person
{
public:
    Person(): lastName("empty"), firstName("empty"), phoneNumber(0) {}

    Person(string lana, string fina, long pho): lastName(lana), firstName(fina), phoneNumber(pho) {}

    friend bool operator< (const Person& p1, const Person& p2)
    {
        if (p1.lastName == p2.lastName) {
            return p1.firstName < p2.firstName;
        }

        return p1.lastName < p2.lastName;
    }

    friend bool operator== (const Person& p1, const Person& p2)
    {
        return (p1.lastName == p2.lastName) && (p1.firstName == p2.firstName);
    }

    void display() const
    {
        cout << lastName << "\t" << firstName << "\t" << phoneNumber << endl;
    }

private:
    string lastName;
    string firstName;
    long phoneNumber;
};

int main()
{
    Person pers1("Deauville", "William", 8435150);
    Person pers2("McDonald", "Stacey", 3327563);
    Person pers3("Bartoski", "Peter", 6946473);
    Person pers4("KuangThu", "Bruce", 4157300);
    Person pers5("Wellington", "John", 9207404);
    Person pers6("McDonald", "Amanda", 8435150);
    Person pers7("Fredericks", "Roger", 7049982);
    Person pers8("McDonald", "Stacey", 7764987);

    multiset<Person, less<Person> > persSet;
    multiset<Person, less<Person> >::iterator iter;

    persSet.insert(pers1);
    persSet.insert(pers2);
    persSet.insert(pers3);
    persSet.insert(pers4);
    persSet.insert(pers5);
    persSet.insert(pers6);
    persSet.insert(pers7);
    persSet.insert(pers8);

    cout << "Number of records: " << persSet.size() << endl;

    iter = persSet.begin();
    while (iter != persSet.end()) {
        (*iter++).display();
    }

    string searchLastName, searchFirstName;
    cout << "Input family name for search: ";
    cin >> searchLastName;
    cout << "Input name for search: ";
    cin >> searchFirstName;

    Person searchPerson(searchLastName, searchFirstName, 0);
    int cntPersons = persSet.count(searchPerson);
    cout << "Number of persons with this name: " << cntPersons << endl;

    iter = persSet.lower_bound(searchPerson);
    while (iter != persSet.upper_bound(searchPerson)) {
        (*iter++).display();
    }
    cout << endl;

    return 0;
}
