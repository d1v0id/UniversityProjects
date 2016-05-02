/*
 * Структуры и алгоритмы обработки данных часть 1
 *
 * Лабораторная работа 5
 * */
#include <iostream.h>
#include <stdlib.h>
#include <fstream>
#define MINSIZE 20
#define MAXSIZE 1000

struct tel {
  char name[40];
  char addr[20];
  char tnum[9];
  struct tel *next;
};

struct tel *head;
tel *pred;
int len = 0;

void entryIface(tel *ei) {
  cout << "[Add Item]" << endl;
  cout << "Name: ";
  cin >> ei->name;
  cout << "Address: ";
  cin >> ei->addr;
  cout << "Phone: ";
  cin >> ei->tnum;
}

void enterTel(tel *t) {
  char c;
  len = 0;
  head = t = pred = (tel*)malloc(sizeof(tel));
  entryIface(t);
  pred->next = t;
  pred = t;
  len++;
  cout << endl << "Next? (Yes/No) ";
  cin >> c;
  if ((c == 'N') || (c == 'n')) return;
  while (1) {
    t = (tel*)malloc(sizeof(tel));
    entryIface(t);
    pred->next = t;
    pred = t;
    len++;
    cout << endl << "Next? (Yes/No) ";
    cin >> c;
    if ((c == 'N') || (c == 'n')) break;
  }
  return;
}

void fileTel(tel *t) {
  char fname[255];
  string word;
  while (1) {
    cout << "File name: ";
    cin >> fname;
    ifstream tfile(fname);
    if (tfile) {
      len = 0;
      head = t = pred = (tel*)malloc(sizeof(tel));
      int i = 0;
      while(getline(tfile, word, ',')) {
        switch(i) {
        case 0: strcpy(t->name, word.c_str()); break;
        case 1: strcpy(t->addr, word.c_str()); break;
        case 2: strcpy(t->tnum, word.c_str()); break;
        }
        if (i == 2) { break; }
        i++;
      }
      pred->next = t;
      pred = t;
      len++;
      i = 0;
      while(getline(tfile, word, ',')) {
        if (i == 0) t = (tel*)malloc(sizeof(tel));
        switch(i) {
        case 0: strcpy(t->name, word.c_str()); break;
        case 1: strcpy(t->addr, word.c_str()); break;
        case 2: strcpy(t->tnum, word.c_str()); break;
        }
        if (i == 2) {
          pred->next = t;
          pred = t;
          len++;
          i = -1;
        }
        i++;
      }
      break;
    }
    else cout << endl << "File not exist!" << endl;
  }
  return;
}

void printTel(tel *t) {
  for (int i = 0; i < len; i++) {
    cout << "[" << i+1 << "] " << t->name
    << " " << t->addr << " " << t->tnum << endl;
    t = t->next;
  }
  return;
}

void sortTel(tel *t) {
  int b[MAXSIZE];
  string a[MAXSIZE];
  for (int i = 1; i <= len; i++) {
    a[i] = t->name;
    t = t->next;
  }
  for (int i = 1; i <= len; i++) b[i] = i;
  for (int i = 1; i <= len; i++)
    for (int j = len; j >= i+1; j--) {
      if (a[b[j]] < a[b[j-1]]) swap(b[j], b[j-1]);
    }

  for (int i = 1; i <= len; i++)
    cout << "[" << i << "] " << a[b[i]] << endl;
  return;
}

int main (int argc, char **argv) {
  char c;
  while(1) {
    cout << "Menu:" << endl;
    cout << "[1] Create new list" << endl;
    cout << "[2] Load new list from file" << endl;
    cout << "[3] Print on screen" << endl;
    cout << "[4] Sort by Name and print list" << endl;
    cout << "[5] Quit" << endl;
    while(1) {
      cin >> c;
      if (c == '1') {
        enterTel(head);
        break;
      }
      if (c == '2') {
        fileTel(head);
        break;
      }
      if (c == '3') {
        if (len != 0) printTel(head);
        else cout << "Add before print!" << endl;
        break;
      }
      if (c == '4') {
        if (len != 0) sortTel(head);
        else cout << "Add before sort!" << endl;
        break;
      }
      if (c == '5') return 0;
    }
  }
}

