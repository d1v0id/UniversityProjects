#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Person
{
public:
    Person(): lastName("empty"), firstName("empty"), phoneNumber(0) {}
    Person(string lana, string fina, long pho): lastName(lana), firstName(fina), phoneNumber(pho) {}

    friend bool operator< (const Person &p1, const Person &p2)
    {
        if (p1.lastName == p2.lastName) {
            return (p1.firstName < p2.firstName);
        }
        
        return (p1.lastName < p2.lastName);
    }

    friend bool operator== (const Person &p1, const Person &p2)
    {
        return (p1.lastName == p2.lastName) && (p1.firstName == p2.firstName);
    }

    void display() const
    {
        cout << lastName << "\t" << firstName << "\t" << phoneNumber << endl;
    }

    long getPhone() const
    {
        return phoneNumber;
    }

private:
    string lastName;
    string firstName;
    long phoneNumber;
};

class ComparePersons
{
public:
    bool operator() (const Person *ptrP1, const Person *ptrP2) const
    {
        return *ptrP1 < *ptrP2;
    }
};

class DisplayPerson
{
public:
    void operator() (const Person *ptrP) const
    {
        ptrP->display();
    }
};

int main()
{
    vector<Person *> vectPtrsPers;
    Person *ptrP1 = new Person("KuangThu", "Burce", 4157300);
    Person *ptrP2 = new Person("Deauville", "William", 8435150);
    Person *ptrP3 = new Person("Wellington", "John", 9207404);
    Person *ptrP4 = new Person("Bartoski", "Peter", 6946473);
    Person *ptrP5 = new Person("Fredericks", "Roger", 7049982);
    Person *ptrP6 = new Person("McDonald", "Stacey", 7764987);

    vectPtrsPers.push_back(ptrP1);
    vectPtrsPers.push_back(ptrP2);
    vectPtrsPers.push_back(ptrP3);
    vectPtrsPers.push_back(ptrP4);
    vectPtrsPers.push_back(ptrP5);
    vectPtrsPers.push_back(ptrP6);

    for_each(vectPtrsPers.begin(), vectPtrsPers.end(), DisplayPerson());
    cout << endl;

    sort(vectPtrsPers.begin(), vectPtrsPers.end());
    cout << "Pointers are sorted:" << endl;
    for_each(vectPtrsPers.begin(), vectPtrsPers.end(), DisplayPerson());
    cout << endl;

    sort(vectPtrsPers.begin(), vectPtrsPers.end(), ComparePersons());
    cout << "Personal data are sorted:" << endl;
    for_each(vectPtrsPers.begin(), vectPtrsPers.end(), DisplayPerson());
    cout << endl;

    while (!vectPtrsPers.empty()) {
        delete vectPtrsPers.back();
        vectPtrsPers.pop_back();
    }

    return 0;
}
