#include <iostream>
#include <list>
#include <numeric>

using namespace std;

class AirTime
{
public:
    AirTime(): hours(0), minutes(0) {}
    AirTime(int h, int m): hours(h), minutes(m) {}

    void display() const
    {
        cout << hours << ":" << minutes;
    }

    void get()
    {
        char dummy;
        cout << "Time (format 12:59): ";
        cin >> hours >> dummy >> minutes;
    }

    AirTime operator+ (const AirTime right) const
    {
        int temph = hours + right.hours;
        int tempm = minutes + right.minutes;

        if (tempm >= 60) {
            temph++;
            tempm -= 60;
        }

        return AirTime(temph, tempm);
    }

    bool operator== (const AirTime &at2) const
    {
        return (hours == at2.hours) && (minutes == at2.minutes);
    }

    bool operator< (const AirTime &at2) const
    {
        return (hours < at2.hours) || (hours == at2.hours && minutes < at2.minutes);
    }

    bool operator!= (const AirTime &at2) const
    {
        return !(*this == at2);
    } 

    bool operator> (const AirTime &at2) const
    {
        return !(*this < at2) && !(*this == at2);
    }

private:
    int hours;
    int minutes;
};

int main()
{
    char answer;
    AirTime temp, sum;
    list<AirTime> airList;

    do {
        temp.get();
        airList.push_back(temp);
        cout << "Continue (y/n) ? ";
        cin >> answer;
    } while(answer != 'n');

    sum = accumulate(airList.begin(), airList.end(), AirTime(0, 0), plus<AirTime>());
    cout << "sum = ";
    sum.display();
    cout << endl;

    return 0;
}
