/*
 * Структуры и алгоритмы обработки данных часть 1
 *
 * Лабораторная работа 2 
 */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>
#define MAXAS 200
using namespace std;

int a[MAXAS];
int c_count, m_count;

int increment(long incr[], long n) {
  int p1, p2, p3, s;
  p1 = p2 = p3 = 1;
  s = -1;
  do {
    if (++s % 2) {
      incr[s] = 8*p1 - 6*p2 + 1;
    } else {
      incr[s] = 9*p1 - 9*p3 + 1;
      p2 *= 2;
      p3 *= 2;
    }
    p1 *= 2;
  } while(3*incr[s] < n);
  return s > 0 ? --s : 0;
}

/* метод сортировки Шелла */
template<class ItemShell>
void shellSort(ItemShell a[], long n) {
  long incr, i, j, seq[40];
  int s;
  s = increment(seq, n); // вычисление последовательности приращений
  while (s >= 0) {
    incr = seq[s--]; // сортировка вставками с инкрементами inc[]
    for (i = incr; i < n; i++) {
      ItemShell temp = a[i];
      for (j = i-incr; (j >= 0) && (a[j] > temp); j -= incr)
        a[j+incr] = a[j];
      a[j+incr] = temp;
      m_count++;
    }
  }
}

template<class ItemShift>
void shiftDown(ItemShift* const a, int i, int const n) {
  int nMax( i );
  ItemShift const value(a[i]);
  while (true) {
    int childN( i*2+1 );
    if ( ( childN < n ) && ( a[childN] > value ) ) {
      nMax = childN;
      c_count++;
    }
    ++childN;
    if ( ( childN < n ) && ( a[childN] > a[nMax] ) ) {
      nMax = childN;
      c_count++;
    }
    if ( nMax == i ) break;
    a[i] = a[nMax];
    a[nMax] = value;
    i = nMax;
    m_count++;
  }
}

/* пирамидальный метод сортировки  */
template<class ItemPyram>
void pyramidSort(ItemPyram* const a, int n) {
  for (int i(n/2-1); i >= 0; --i) shiftDown(a, i, n);
  while( n > 1 ) {
    --n;
    ItemPyram const firstElem(a[0]);
    a[0] = a[n];
    a[n] = firstElem;
    shiftDown(a, 0, n);
  }
}

/* метод сортировки Хоара */
template<class ItemHoar>
void hoarSort(ItemHoar* const a, int l, int r) {
  long base, opposite, p;
  int c;
  base = l;
  opposite = r;
  while (base != opposite) {
    if ((a[base] > a[opposite])^(base > opposite)) {
      c = a[base];
      a[base] = a[opposite];
      a[opposite] = c;
      p = base;
      base = opposite;
      if (p < opposite) opposite = p + 1;
      else opposite = p - 1;
    } else {
      if (base < opposite) opposite--;
      else opposite++;
    }
    c_count++;
  }
  if (l < base-1) { hoarSort(a, l, base-1); m_count++; }
  if (base+1 < r) { hoarSort(a, base+1, r); m_count++; }
}

/* 
   проверить правильность сортировки проверить
   путум подсчета контрольной сумму и числа
   серий в массиве
*/

/*
   предусмотреть подсчет количества 
   пересылок и сравнений во время
   сортировки
*/
int main (int argc, char **argv) {
  int b[MAXAS];
  int CS1, CS2;
  int n;

  cout << "Enter N = ";
  cin >> n;
  if (n > MAXAS) {
    cout << "N > " << MAXAS << "!" << endl;
    getch();
    return 0;
  }

  srand(time(0));
  for (int i = 0; i < n; i++) {
    a[i] = rand() % 100;
    CS1 += a[i];
  }
  cout << "a = ( ";
  for (int i = 0; i < n; i++) cout << a[i] << " ";
  cout << ")" << endl;
  for (int i = 0; i < n; i++) b[i] = a[i];
  c_count = 0;
  m_count = 0;
  shellSort<int>(b, n);
  for (int i = 0; i < n; i++) CS2 += i+1;
  cout << "b = ( ";
  for (int i = 0; i < n; i++) cout << b[i] << " ";
  cout << ")" << endl;
  cout << ">> C = " << c_count << " M = " << m_count << endl;
  c_count = 0;
  m_count = 0;
  shellSort<int>(b, n);
  cout << ">> C = " << c_count << " M = " << m_count << endl;


  srand(time(0));
  for (int i = 0; i < n; i++) {
    a[i] = rand() % 100;
    CS1 += a[i];
  }
  cout << "a = ( ";
  for (int i = 0; i < n; i++) cout << a[i] << " ";
  cout << ")" << endl;
  for (int i = 0; i < n; i++) b[i] = a[i];
  c_count = 0;
  m_count = 0;
  pyramidSort<int>(b, n);
  for (int i = 0; i < n; i++) CS2 += i+1;
  cout << "b = ( ";
  for (int i = 0; i < n; i++) cout << b[i] << " ";
  cout << ")" << endl;
  cout << ">> C = " << c_count << " M = " << m_count << endl;
  c_count = 0;
  m_count = 0;
  pyramidSort<int>(b, n);
  cout << ">> C = " << c_count << " M = " << m_count << endl;


  srand(time(0));
  for (int i = 0; i < n; i++) {
    a[i] = rand() % 100;
    CS1 += a[i];
  }
  cout << "a = ( ";
  for (int i = 0; i < n; i++) cout << a[i] << " ";
  cout << ")" << endl;
  for (int i = 0; i < n; i++) b[i] = a[i];
  c_count = 0;
  m_count = 0;
  hoarSort<int>(b, 1, n);
  for (int i = 0; i < n; i++) CS2 += i+1;
  cout << "b = ( ";
  for (int i = 0; i < n; i++) cout << b[i] << " ";
  cout << ")" << endl;
  cout << ">> C = " << c_count << " M = " << m_count << endl;
  c_count = 0;
  m_count = 0;
  hoarSort<int>(b, 1, n);
  cout << ">> C = " << c_count << " M = " << m_count << endl;

  getch();
}
 
