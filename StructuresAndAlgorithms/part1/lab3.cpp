/*
 * Структуры и алгоритмы обработки данных часть 1
 *
 * Лабораторная работа 3
 *
 * Работа со стеком и с очередью
 * */
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#define LSIZE 20
using namespace std;

/* класс для работы со стеком */
class IntStack {
  public:
    IntStack (int num) {
      tail = 0;
      maxlen = num;
      s = new int[maxlen];
    }

    void push (int t) {
      if (tail == maxlen) return;
      s[tail++] = t;
    }

    int pop () {
      if (tail == 0) return -1;
      return s[--tail];
    }

    int empty() {
      return tail == 0;
    }

  private:
    int *s;
    int tail;
    int maxlen;
};

IntStack *st = new IntStack(LSIZE); /* объявление нового стека */

/* класс для работы с очередью */
class IntQueue {
  public:
    IntQueue (int num) {
      head = 0;
      tail = 0;
      len = 0;
      maxlen = num;
      q = new int[maxlen];
    }

    void push (int t) {
      if (len == maxlen) return;
      if (tail == maxlen) tail -= maxlen + 1;
      q[tail++] = t;
      ++len;
    }

    int pop () {
      if (len == 0) return -1;
      if (head == maxlen) head -= maxlen + 1;
      --len;
      return q[head++];
    }

    int empty() {
      return len != 0;
    }

  private:
    int *q;
    int head;
    int tail;
    int len;
    int maxlen;
};

IntQueue *qu = new IntQueue(LSIZE); /* объявление новой очереди */

/* очистка стека */
void stackClear() {
  while (!(st->empty())) st->pop();
}

/* очистка очереди */
void queueClear() {
  while ((qu->empty())) qu->pop();
}

/* заполнение стека возрастающими числами */
void stackIncFill (int st_size, int first_n) {
  for (int i = 1; i <= st_size; i++)
    st->push(first_n++);
}

/* заполнение очереди возрастающими числами */
void queueIncFill (int qu_size, int first_n) {
  for (int i = 1; i <= qu_size; i++)
    qu->push(first_n++);
}

/* заполнение стека убывающими числами */
void stackDecFill (int st_size, int first_n) {
  for (int i = 1; i <= st_size; i++)
    st->push(first_n--);
}

/* заполнение очереди убывающими числами */
void queueDecFill (int qu_size, int first_n) {
  for (int i = 1; i <= qu_size; i++)
    qu->push(first_n--);
}

/* заполнение стека случайными числами */
void stackRandFill (int st_size) {
  srand(time(0));
  for (int i = 1; i <= st_size; i++)
    st->push(rand() % 100);
}

/* заполнение очереди случайными числами */
void queueRandFill (int qu_size) {
  srand(time(0));
  for (int i = 1; i <= qu_size; i++)
    qu->push(rand() % 100);
}

/* печать элементов стека */
void stackPrint() {
  int num = 0, num_buf = 0, ser = 1, CS = 0;
  while (!(st->empty())) {
    num_buf = num;
    num = st->pop();
    CS += num;
    printf("%d ", num);
    if (num < num_buf) ser++;
  }
  printf(" S = %d CS = %d\n", ser, CS);
}

/* печать элементов очереди */
void queuePrint() {
  int num = 0, num_buf = 0, ser = 1, CS = 0;
  while ((qu->empty())) {
    num_buf = num;
    num = qu->pop();
    CS += num;
    printf("%d ", num);
    if (num < num_buf) ser++;
  }
  printf(" S = %d CS = %d\n", ser, CS);
}

/* подсчет контрольной суммы элементов списка и
 * подсчет количества серий в списке
 * */

int main(int argc, char* argv[]) {
  stackIncFill(LSIZE, 1);
  stackPrint();
  stackClear();

  stackDecFill(LSIZE, LSIZE);
  stackPrint();
  stackClear();

  stackRandFill(LSIZE);
  stackPrint();
  stackClear();

  printf("\n");

  queueIncFill(LSIZE, 1);
  queuePrint();
  queueClear();  

  queueDecFill(LSIZE, LSIZE);
  queuePrint();
  queueClear();

  queueRandFill(LSIZE);
  queuePrint();
  queueClear();

  getch();  
  return 0;
}
 
