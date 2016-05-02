/* 
 * Структуры и алгоритмы обработки данных часть 1
 *
 * Лабораторная работа 1
 *
 * отсортировать массив, подсчитать количество пересылок и
 * сравнений (M и C) и сравнить их с теоретическими оценками 
 * */
#include <stdio.h>
#include <conio.h>
#include <algorithm>
#define MAXAS 200
using namespace std;

int a[MAXAS];
int c_count;
int m_count;

/* сортировка методом прямого выбора */
template <class ItemSel>
void selectionSort (ItemSel a[], int n) {
  for (int i = 0; i < n-1; i++) {
    int min = i;
    for (int j = i+1; j < n; j++)
      if(a[j] < a[min]) min = j;
    if (a[min]!=a[i]) swap(a[i],a[min]);
  }
}

/* сортировка методом пузырька */
template <class ItemBubl>
void bubbleSort (ItemBubl a[], int n) {
  for (int j = 1; j <= n-1; j++) {
    int f = 0;
    int min = j;
    for (int i = j; i <= n-j; i++) {
      if (a[i] > a[i+1]) { 
        swap(a[i], a[i+1]);
        f = 1;
        m_count++;
      }
      if (a[i] < a[min]) min = i;
    }
    if (f = 0) break;
    if (min != j) swap(a[j], a[min]);
  }
}

/* сортировка методом шейкерной сортировки */
template <class ItemShake>
void shakerSort (ItemShake a[], int n) {
  int l = 1;
  int r = n-1;
  int k = n-1;
  do {
   for (int i = r; i >= l; i--) { // Сдвигаем к концу массива "легкие элементы"
     if (a[i-1] > a[i]) {
       swap(a[i], a[i-1]);
       m_count++;
       k = i; // Запомнить место пследней перестановки
     }
     c_count++;
   }
   l = k + 1;
   for (int i = l; i <= r; i++) { // Сдвигаем к началу массива "тяжелые элементы"
     if (a[i-1] > a[i]) {
       swap(a[i], a[i-1]);
       m_count++;
       k = i; // Запомнить место пследней перестановки
     }
     c_count++;
   }
   r = k - 1;
 }
 while (l <= r);
}

/* проверка сортировки путем подсчета контрольной суммы и числа серий в массиве */

int main(int argc, char* argv[]) {
  int b[MAXAS];
  int cs1, cs2;
  int n;

  while (1) {
    printf("Enter N = ");

    if ( scanf("%d", &n) == 1 ) {
      if (n > MAXAS) printf("N > 200 !");
      else break;
    } else {
      printf("Not number!");
      getch();
      return 1;
    }
  }

  srand(time(0));
  cs1 = 0;
  printf("a = ( ");
  for (int i = 0; i < n; i++) {
    a[i] = rand() % 100;
    printf("%d ", a[i]);
    cs1 += a[i];
  }
  printf(" ) CS1 = %d\n", cs1);

  cs2 = 0;
  for (int i = 0; i < n; i++) b[i] = a[i];
  c_count = (n*n - n) / 2;
  m_count = 3*(n-1);
  selectionSort<int>(b, n);
  printf("b = ( ");
  for (int i = 0; i < n; i++) {
    printf("%d ", b[i]);
    cs2 += b[i];
  }
  printf(") CS2 = %d\n  C = %d and M = %d\n", cs2, c_count, m_count);
  selectionSort<int>(b, n);
  printf("  C = %d and M = %d\n", c_count, m_count);

  cs2 = 0;
  for (int i = 0; i < n; i++) b[i] = a[i];
  c_count = (n*n - n) / 2;
  m_count = 0;
  bubbleSort<int>(b, n);
  printf("b = ( ");
  for (int i = 0; i < n; i++) {
    printf("%d ", b[i]);
    cs2 += b[i];
  }
  printf(") CS2 = %d\n  C = %d and M = %d\n", cs2, c_count, m_count);
  m_count = 0;
  bubbleSort<int>(b, n);
  printf("  C = %d and M = %d\n", c_count, m_count);

  cs2 = 0;
  for (int i = 0; i < n; i++) b[i] = a[i];
  c_count = 0;
  m_count = 0;
  shakerSort<int>(b, n);
  printf("b = ( ");
  for (int i = 0; i < n; i++) {
    printf("%d ", b[i]);
    cs2 += b[i];
  }
  printf(") CS2 = %d\n  C = %d and M = %d\n", cs2, c_count, m_count);
  c_count = 0;
  m_count = 0;
  shakerSort<int>(b, n);
  printf("  C = %d and M = %d\n", c_count, m_count);
  getch();
  return 0;
}
 
