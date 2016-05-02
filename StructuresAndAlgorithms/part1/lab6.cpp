/*
 * Структуры и алгоритмы обработки данных часть 1
 *
 * Лабораторная работа 6
 * */
#include <iostream.h>
#include <fstream.h>
#define MAXSIZE 1000

struct nodeTable { /* класс элемента хэш-таблицы */
  char str[255];
  int key;
};

int c_count, /* количество коллизий */
    w_count, /* количество слов */
    t_size;  /* размер таблицы */

const int MAXN = 200; /* максимальный размер хэш-таблицы */
nodeTable hashTable[MAXN]; /* хэш-таблица */

int loadFFile(string *arr) {
  char fname[255];
  string word;
  int len;
  while(1) {
    cout << "File name: ";
    cin >> fname;
    ifstream tfile(fname);
    if (tfile) {
      int i = 0;
      while(getline(tfile, word, ' ')) {
        arr[i] = word;
        i++;
        if (i > MAXSIZE) break;
      }           
      len = i;
      break;
    }
  }
  return len;
}

void printStrings(string *arr, int len) {
  for (int i = 0; i < len-1; i++) {
    cout << arr[i] << " ";
  }
  cout << arr[len-1] << endl;
  return;
}

int getHash(string str) {
  int h = 0;
  for (int i = 0; i < (signed)str.size(); i++) {
    h = (h * 255 + abs(str[i])) % w_count;
  }
  return h;
}

/* линейные пробы */
void hashLStrings(string *arr, int len) {
  int res;
  w_count = len;
  t_size = 0;
  c_count = 0;
  memset(hashTable, NULL, sizeof(hashTable));
  for (int i = 0; i < len; i++) {
    int hash = getHash(arr[i]);
    int n = hash;
    while (1) {
      if (hashTable[n].key != 0) {
        c_count++;
        if (strcmp(hashTable[n].str, arr[i].c_str()) == 0) break;
        n++;
        if (n > w_count && n < MAXN) w_count = n;
        if (n > MAXN) n = n % MAXN;
      } else {
        t_size++;
        strcpy(hashTable[n].str, arr[i].c_str());
        hashTable[n].key = n;
        break;
      }
    }
  }
  cout << "L: " << t_size << " " << c_count << endl;
  return;
}

/* квадратичные пробы */
void hashQStrings(string *arr, int len) {
  int res;
  w_count = len;
  t_size = 0;
  c_count = 0;
  memset(hashTable, NULL, sizeof(hashTable));
  for (int i = 0; i < len; i++) {
    int hash = getHash(arr[i]);
    int n = hash;
    int zn = 1;
    int j = 1;
    while (1) {
      if (hashTable[n].key != 0) {
        if (strcmp(hashTable[n].str, arr[i].c_str()) != 0) {
          c_count++;
          n = (n+j*zn) + (n+i*zn);
          zn = -zn;
          if (zn == 1) j++;
          if (n > w_count && n < MAXN) w_count = n;
          if (n > MAXN) n = n % MAXN;
          if (n < 0) n = 1;
        } else break;
      } else {
        t_size++;
        strcpy(hashTable[n].str, arr[i].c_str());
        hashTable[n].key = hash;
        break;
      }
    }
  }
  cout << "Q: " << t_size << " " << c_count << endl;
  return;
}

int main(int argc, char* argv[])
{
  char c;
  string arr[MAXSIZE];
  int len = 0;
  while(1) {
    cout << "Menu:" << endl;
    cout << "[1] Load strings from file" << endl;
    cout << "[2] Print strings" << endl;
    cout << "[3] Line hash table" << endl;
    cout << "[4] Quadr hash table" << endl;
    cout << "[5] Exit" << endl;
    while(1) {
      cin >> c;
      if (c == '1') {
        len = loadFFile(arr);
        break;
      }
      if (c == '2') {
        if (len > 0) printStrings(arr, len);
        else cout << "Create string list before print!" << endl;
        break;
      }
      if (c == '3') {
        if (len > 0) hashLStrings(arr, len);
        else cout << "Create string list before LHash!" << endl;
        break;
      }
      if (c == '4') {
        if (len > 0) hashQStrings(arr, len);
        else cout << "Create string list before QHash!" << endl;
        break;
      }
      if (c == '5') return 0;
    }
  }
}
 
