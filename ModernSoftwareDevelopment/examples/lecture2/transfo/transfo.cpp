#include <iostream>
#include <algorithm>

using namespace std;

double in_to_cm(double in)
{
    return (in * 2.54);
}

int main()
{
    double inches[] = { 3.5, 6.2, 1.0, 12.75, 4.33 };
    double centi[5];
    
    transform(inches, inches + 5, centi, in_to_cm);

    for (int i = 0; i < 5; i++) {
        cout << centi[i] << " ";
    }
    cout << endl;

    return 0;
}
