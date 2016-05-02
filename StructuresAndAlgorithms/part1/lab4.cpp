/*
 * Структуры и алгоритмы обработки данных часть 1
 *
 * Лабораторная работа 4
 * */
#include <iostream.h>
#include <conio.h>
#define NMAX 200

int m_count = 0, c_count = 0;

/* классы для работы с
   последовательностями */
class IntKey {
  friend ostream & operator << (ostream & out, const IntKey & v);
  int value;
public:
  IntKey(int v = 0) : value(v) {}
  IntKey(const IntKey & key) : value(key.value) {}
  int getValue() { return value; }
  int length() { return 8; }
  int power() { return 16; }
  int operator [] (int i) const { return (value >> (4*(7-i))) & 15; }
};

ostream & operator << (ostream & out, const IntKey & v) {
  return out << v.value;
}

template <class Key>
struct Element {
  Key value;
  int next;

  Element() {
    next = -1;
  }

  Element(const Element<Key> & src) : value(src.value), next(src.next)
  {}

  Element(const Key & val, int n = -1) : value(val), next(n)
  {}

  Element & operator = (const Element<Key> & src) {
    value = src.value;
    next = src.next;
    return *this;
  }
};

template <class Key>
class ListBuffer {
private:
  Element<Key> * buffer;
  int size;
  int freePtr;

public:
  ListBuffer(int n) {
    buffer = new Element<Key>[size = n];
    Clear();
  }

  ~ListBuffer() {
    delete [] buffer;
  }

  void Clear() {
    freePtr = 0;
  }

  Element<Key> & operator [] (int i) {
    return buffer[i];
  }

  int get() {
    return freePtr++;
  }
};

template <class Key>
class KeyList {
private:
  ListBuffer<Key> * buffer;
  int first;
  int last;

public:
  KeyList(ListBuffer<Key> * buf = NULL) : buffer(buf), first(-1), last(-1)
  {}

  void Initialize(ListBuffer<Key> * buf) {
    buffer = buf;
  }

  void AddKey(const Key & key) {
    int nextElem = buffer->get();
    (*buffer)[nextElem] = Element<Key>(key);

    if(first == -1) {
      first = nextElem;
    } else {
      (*buffer)[last].next = nextElem;
    }
    c_count++;
    last = nextElem;
  }

  int ToArray(Key * array, int from) {
    int ptr = first;
    while(ptr != -1) {
      array[from++] = (*buffer)[ptr].value;
      ptr = (*buffer)[ptr].next;
    }
    return from;
  }

  void Clear() {
    first = last = -1;
  }
};


/* создание последовательности */
template <class Element>
void CreateArray(Element *arr, int n) {
  int seed = 13;
  for(int i = 0; i < n; i++) {
    arr[i] = IntKey(seed = (837*seed + 1079) & 0x7fffffff);
  }
}


/* вывод последовательности на экран */
template <class Element>
void PrintArray(Element * array, int low, int high) {
  for(int i = low; i <= high; i++) {
    cout << array[i] << (i < high ? ", " : "");
    /* подсчет контрольной суммы */
  }
  cout << endl;
}


/* цифровая сортировка */
template <class Key>
void DigitSort(Key * array, int low, int high) {
  int n = high - low + 1;
  int listNumber = array[low].power();
  int passes = array[low].length();
  ListBuffer<Key> buffer(n);

  KeyList<Key> * lists = new KeyList<Key>[listNumber];
  for(int i = 0; i < listNumber; i++) {
    lists[i].Initialize(&buffer);
  }

  for(int digit = passes-1; digit >= 0; digit--) {
    for(int i = low; i <= high; i++) {
      lists[array[i][digit]].AddKey(array[i]);
    }
    m_count++;

    int start = low;
    for(int i = 0; i < listNumber; i++) {
      start = lists[i].ToArray(array, start);
      lists[i].Clear();
    }
    buffer.Clear();
  }
}


/* сортировка методом прямого слияния */
template<class Key>
void Merge(Key * arr1, int low1, int high1,
  Key * arr2, int low2, int high2,
  Key * arr3, int low3) {
  
  int ndx1 = low1,
      ndx2 = low2,
      ndx3 = low3;

  while(ndx1 <= high1 && ndx2 <= high2) {
    if(arr1[ndx1] < arr2[ndx2]) {
      arr3[ndx3++] = arr1[ndx1++];
    } else {
      arr3[ndx3++] = arr2[ndx2++];
    }
  }

  if(ndx1 > high1) {
    while(ndx2 <= high2) {
     arr3[ndx3++] = arr2[ndx2++];
    }
  } else {
    while(ndx1 <= high1) {
      arr3[ndx3++] = arr1[ndx1++];
    }
  }
}

template <class Key>
void Move(Key * src, int sLow, int sHigh, Key * dst, int dLow) {
  for(int pSrc = sLow, pDst = dLow; pSrc <= sHigh; ) {
    dst[pDst++] = src[pSrc++];
    m_count++;
  }
}

template <class Key>
void MergeSort(Key * array, int low, int high) {
  int n = high - low + 1;
  int frag = n;
  int len = 1;
  Key * source = array,
      * dest = new Key[n];
  int sourceLow = low,
      destLow = 0;

  while(frag > 1) {
    int pSource = sourceLow, pDest = destLow;
    do {
      int nextSource = min(pSource + 2*len, sourceLow + n);
      if(nextSource > pSource + len) {
        Merge<Key>(source, pSource, pSource+len-1,
                   source, pSource+len, nextSource-1,
                   dest, pDest);
      } else {
        Move<Key>(source, pSource, nextSource-1,
                 dest, pDest);
      }
      c_count++;
      pSource = nextSource;
      pDest += 2*len;
    } while(pSource < sourceLow+n);
    len *= 2;
    frag = (frag+1)/2;

    Key * tempArray = dest;
    dest = source;
    source = tempArray;

    int tempLow = destLow;
    destLow = sourceLow;
    sourceLow = tempLow;
  }
  if(source != array) {
    Move<Key>(source, sourceLow, sourceLow+n-1, dest, destLow);
  }
}


int main(int argc, char* argv[])
{
  int n;
  cout << "N = ";
  cin >> n;
  if (n > NMAX) return -1;

  /* инициализация исходного массива */
  IntKey arr[NMAX];
  CreateArray<IntKey>(arr, n);

  /* сортировка */
  c_count = 0;
  m_count = 0;
  DigitSort<IntKey>(arr, 0, n-1);
  cout << "M = " << m_count << " C = " << c_count << endl;
  c_count = 0;
  m_count = 0;
  DigitSort<IntKey>(arr, 0, n-1);
  cout << "M = " << m_count << " C = " << c_count << endl;

  int sMerge[NMAX];
  srand(time(0));
  for(int i = 0; i < n; i++) {
    sMerge[i] = rand() % 100;
  }
  c_count = 0;
  m_count = 0;
  MergeSort<int>(sMerge, 0, n-1);
  cout << "M = " << m_count << " C = " << c_count << endl;
  MergeSort<int>(sMerge, 0, n-1);
  c_count = 0;
  m_count = 0;
  cout << "M = " << m_count << " C = " << c_count << endl;

  getch();
  return 0;
}

