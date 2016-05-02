/* Примеры шаблонов функций */
#include <iostream>
using namespace std;

template <class T>
void func(T t)
{
  // Тело ф-ции
}

template <class T>
void Swap(T t[], int indx1, int indx2)
{
  T tmp = t[indx1];
  t[indx1] = t[indx2];
  t[indx2] = tmp;
}

template <class T>
void func_1(T t1, T t2)
{
  // Тело ф-ции
}

template <class T1, class T2>
void func_2(T1 t1, T2 t2)
{
  // Тело ф-ции
}

template <class T>
void print(T arr, int size)
{
  for (int i = 0; i < size; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;
}

int main(int argc, char* argv[])
{
  int arr[5] = { 1, 2, 3, 4, 5 };
  print(arr, 5);

  Swap(arr, 0, 1);
  print(arr, 5);  

  return 0;
}