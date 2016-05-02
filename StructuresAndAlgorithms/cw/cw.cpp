/*
 * Структуры и алгоритмы обработки данных
 *
 * Курсовая работа
 * */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

#define NAMESIZE 32     /* размер поля ФИО */
#define DPSIZE 3 	/* количество цифр в номере отдела */
#define POSTSIZE 22     /* размер поля должность */
#define BDATESIZE 8     /* размер поля дата рождения */

/* описание структуры БД*/
struct orgDBase {
    char name[NAMESIZE];        /* ФИО */
    unsigned short int depnum;  /* номер отдела */
    char post[POSTSIZE];        /* должность */
    char bdate[BDATESIZE];      /* дата рождения */
};

orgDBase* orgDBArray;
int empCount;

struct indDBase {
    orgDBase* key;
};

indDBase* indDBArrayElem;

char oem_str[255];

/* ф-ция загрузки БД из файла в оперативную память */
void dbase_loadFromFile(char *fname) {
	FILE *binFile = NULL;
        unsigned long lSize;
        size_t result;
	binFile = fopen(fname, "rb");
	if (binFile == NULL) {
                CharToOem("Ошибка! Файл недоступен!", oem_str);
		printf("%s\n", oem_str);
                getch();
		exit(1);
	}

        fseek(binFile, 0, SEEK_END);
	lSize = ftell(binFile);
	rewind (binFile);
        empCount = lSize / sizeof(orgDBase);

	orgDBArray = (orgDBase*)malloc(sizeof(orgDBase) * lSize);
	if (orgDBArray == NULL) {
                CharToOem("Ошибка памяти!", oem_str);
                printf("%s\n", oem_str);
		exit(2);
	}

	result = fread(orgDBArray, 1, lSize, binFile);
	if (result != lSize) {
                CharToOem("Ошибка чтения файла!", oem_str);
		printf("%s\n", oem_str);
		exit (3);
	}

	fclose(binFile);
}

void ind_buildIndexArray() {
    indDBArrayElem = (indDBase*)malloc(sizeof(indDBase) * empCount);
    for (int i = 0; i < empCount; i++) {
        indDBArrayElem[i].key = &orgDBArray[i];
    }
}

/* процедура вывода БД из памяти на экран */
void dbase_drawTable(int index)
{
    gotoxy(1, 1);
    cprintf("%c", 201);
    for (int i = 0; i < 80 - 2; i++)
      cprintf("%c", 205);
    cprintf("%c", 187);
    cprintf("%c", 186);
    cprintf("           Employer name           %c  #"
            "  %c          Post          %c Birth day"
            " ", 179, 179, 179);
    cprintf("%c", 186);

    gotoxy(1, 3);
    cprintf("%c", 204);
    for (int i = 0; i < 80 - 2; i++)
      cprintf("%c", 205);
    cprintf("%c", 185);

    int n = empCount;
    if (empCount > 15) n = 15;
    for (int i = 0; i < n; i++) {
      cprintf("%c", 186);
      cprintf("  ");
      for (int j = 0; j < NAMESIZE; j++)
        cprintf("%c", indDBArrayElem[i + index].key->name[j]);
      cprintf(" %c ", 179);

      cprintf("%3d", indDBArrayElem[i + index].key->depnum);
      cprintf(" %c ", 179);

      for (int j = 0; j < POSTSIZE; j++)
        cprintf("%c", indDBArrayElem[i + index].key->post[j]);
      cprintf(" %c ", 179);

      for (int j = 0; j < BDATESIZE; j++)
        cprintf("%c", indDBArrayElem[i + index].key->bdate[j]);
      cprintf("  ");

      cprintf("%c", 186);
    }
    cprintf("%c", 200);
    for (int i = 0; i < 80 - 2; i++)
      cprintf("%c", 205);
    cprintf("%c\n", 188);
    gotoxy(2, 24); cprintf("[S] Sort   [Q] Search");
    gotoxy(70, 24); cprintf("[Esc] Quit");
    gotoxy(80, 25);
}

bool compareStr(char* a, char* b) {
    char* bdate1 = new char[BDATESIZE-2];
    bdate1[0] = a[6];
    bdate1[1] = a[7];
    bdate1[2] = a[3];
    bdate1[3] = a[4];
    bdate1[4] = a[0];
    bdate1[5] = a[1];

    char* bdate2 = new char[BDATESIZE-2];
    bdate2[0] = b[6];
    bdate2[1] = b[7];
    bdate2[2] = b[3];
    bdate2[3] = b[4];
    bdate2[4] = b[0];
    bdate2[5] = b[1];

    if (strcmp(bdate1, bdate2) > 0)
        return true;
    if (strcmp(bdate1, bdate2) < 0)
        return false;

    return false;
}

void ind_sortHoarArray(int l, int r)
{
    indDBase c;
    long base, opposite, p;
    base = l;
    opposite = r;
    while (base != opposite) {
        if ( compareStr(indDBArrayElem[base].key->bdate,
                indDBArrayElem[opposite].key->bdate) ^ (base > opposite) ) {
            c = indDBArrayElem[base];
            indDBArrayElem[base] = indDBArrayElem[opposite];
            indDBArrayElem[opposite] = c;
            p = base;
            base = opposite;
            if (p < opposite) opposite = p + 1;
            else opposite = p - 1;
        } else {
            if (base < opposite) opposite--;
            else opposite++;
        }
    }
    if (l < base-1) ind_sortHoarArray(l, base-1);
    if (base+1 < r) ind_sortHoarArray(base+1, r);
}

typedef orgDBase* ptrDBase; 

class DBQueue {
    public:
        DBQueue(int num) {
            head = 0;
            tail = 0;
            len = 0;
            maxlen = num;
            q = new ptrDBase[maxlen];
        }
        
        void push(ptrDBase t) {
            if (len == maxlen) return;
            if (tail == maxlen) tail -= maxlen+1;
            q[tail++] = t;
            ++len;
        }

        ptrDBase pop() {
            if (len == 0) return NULL;
            if (head == maxlen) head -= maxlen+1;
            --len;
            return q[head++];
        }
        
        int empty() {
            return len != 0;
        }
        
        int queueGetSize() {
            return len;
        }
    
    private:
        ptrDBase* q;
        int head;
        int tail;
        int len;
        int maxlen;
};

void queueClear(DBQueue *qu)
{
    while ((qu->empty())) qu->pop();
}

void queuePrint(DBQueue *qu)
{
    orgDBase* quElem;
    while ((qu->empty())) {
        quElem = qu->pop();
        for (int i = 0; i < BDATESIZE; i++)
          printf("%c", quElem->bdate[i]);
        printf("\n");
    }
}

DBQueue * dbase_searchByKey(char* key)
{
    DBQueue *qu = new DBQueue(empCount);
    char dtYear[2];
    for (int i = 0; i < empCount; i++) {
      dtYear[0] = indDBArrayElem[i].key->bdate[6];
      dtYear[1] = indDBArrayElem[i].key->bdate[7];
      if (atoi(dtYear) == atoi(key))
        qu->push(indDBArrayElem[i].key);
    }

    return qu;
}

struct stAVLTree {
    ptrDBase key;
    ptrDBase eq[100];
    int eqCount;
    int balance;
    stAVLTree* left;
    stAVLTree* right;
};

bool grow;
int turns;

void tr_llTurn(stAVLTree** p)
{
    stAVLTree *q;
    q = (*p)->left;
    q->balance = 0;
    (*p)->balance = 0;
    (*p)->left = q->right;
    q->right = (*p);
    (*p) = q;
}

void tr_lrTurn(stAVLTree** p)
{
    stAVLTree *q;
    stAVLTree *r;
    q = (*p)->left;
    r = q->right;
    if (r->balance < 0) (*p)->balance = 1;
    else (*p)->balance = 0;
    if (r->balance > 0) q->balance = -1;
    else q->balance = 0;
    r->balance = 0;
    (*p)->left = r->right;
    q->right = r->left;
    r->left = q;
    r->right = (*p);
    (*p) = r;
}

void tr_rlTurn(stAVLTree** p)
{
    stAVLTree *q = (*p)->right;
    stAVLTree *r = q->left;
    if (r->balance > 0) (*p)->balance = -1;
    else (*p)->balance = 0;
    if (r->balance < 0) q->balance = 1;
    else q->balance = 0;
    r->balance = 0;
    (*p)->right = r->left;
    q->left = r->right;
    r->left = (*p);
    r->right = q;
    (*p) = r;
}

void tr_rrTurn(stAVLTree** p)
{
    stAVLTree *q;
    q = (*p)->right;
    q->balance = 0;
    (*p)->balance = 0;
    (*p)->right = q->left;
    q->left = (*p);
    (*p) = q;
}

void tr_addToAVL(stAVLTree** p, ptrDBase x)
{
    if ((*p) == NULL) {
        (*p) = new(stAVLTree);
        (*p)->key = x;
        (*p)->eqCount = 0;
        (*p)->left = NULL;
        (*p)->right = NULL;
        (*p)->balance = 0;
        grow = true;
    } else {
        char* dt_day1 = new char[2];
        char* dt_day2 = new char[2];
        dt_day1[0] = (*p)->key->bdate[0];
        dt_day1[1] = (*p)->key->bdate[1];
        dt_day2[0] = x->bdate[0];
        dt_day2[1] = x->bdate[1];

        if (strcmp(dt_day1, dt_day2) == 0) {
          (*p)->eq[(*p)->eqCount] = x;
          (*p)->eqCount++;
        }

        if (strcmp(dt_day1, dt_day2) > 0) {
            tr_addToAVL(&(*p)->left, x);
            if (grow)
                if ((*p)->balance > 0) {
	                (*p)->balance = 0;
	                grow = false;
	        } else {
                        if ((*p)->balance == 0)
                                (*p)->balance = -1;
	                else {
                                if ((*p)->left->balance < 0)
                                        tr_llTurn(&(*p));
                                else
                                        tr_lrTurn(&(*p));
                                turns++;
                                grow = false;
                        }
                }
	}

           
        if (strcmp(dt_day1, dt_day2) < 0) {
            tr_addToAVL(&(*p)->right, x);
            if (grow)
	        if ((*p)->balance < 0) {
	                (*p)->balance = 0;
	                grow = false;
                } else {
                        if ((*p)->balance == 0)
                                (*p)->balance = 1;
	                else {
                                if ((*p)->right->balance > 0)
                                        tr_rrTurn(&(*p));
                                else
                                        tr_rlTurn(&(*p));
                                turns++;
                                grow = false;
	                }
	        }
	}
    }
}

stAVLTree* tr_buildAVLTree(DBQueue* sr_keyQuPointer, int n)
{
    stAVLTree* t;
    stAVLTree** p;
    turns = 0;
    t = new(stAVLTree);
    t->key = sr_keyQuPointer->pop();
    t->eqCount = 0;
    t->left = NULL;
    t->right = NULL;
    t->balance = 0;
    for (int i = 1; i < n; i++) {
        p = &t;
        grow = false;
        tr_addToAVL(p, sr_keyQuPointer->pop());
    }
    
    return t;           
}

void tr_goFromLeftToRight(stAVLTree* p, int s)
{
    if (p == NULL) return;
    tr_goFromLeftToRight(p->left, ++s);
    for (int i = 0; i < s; ++i) printf("|");
    for (int i = 0; i < BDATESIZE; i++)
        printf("%c", p->key->bdate[i]);
    printf("   [%d]\n", p->eqCount);

    for (int i = 0; i < p->eqCount; i++) {
        printf("\t");
        for (int j = 0; j < BDATESIZE; j++)
            printf("%c", p->eq[i]->bdate[j]);
        printf("\n");
    }

    s--;
    tr_goFromLeftToRight(p->right, ++s);
}

int tr_getSize(stAVLTree *t) {
    return (t == NULL) ? 0 : 1+tr_getSize(t->left)+tr_getSize(t->right);
}

int tr_sdp(stAVLTree *t, int l) {
    return (t == NULL) ? 0 : l+tr_sdp(t->left, l+1)+tr_sdp(t->right, l+1);
}

float tr_getAverageHeight(stAVLTree *t) {
    return ((float)tr_sdp(t, 1) / tr_getSize(t));
}

bool tr_searchInTree(stAVLTree* p, int x, int* t_count, stAVLTree** findElem)
{
    while (p != NULL) {
        char dt_day[2];
        dt_day[0] = p->key->bdate[0];
        dt_day[1] = p->key->bdate[1];
        if (atoi(dt_day) < x) {
            p = p->right;
            (*t_count)++;
        } else if (atoi(dt_day) > x) {
            p = p->left;
            (*t_count)++;
        } else break;
    }

    if (p != NULL) {
        *findElem = p;
        return true;
    } else {
        return false;
    }
}

int main (int argc, char **argv)
{
    char *fname = (char*)"base2.dat";   /* имя файла БД */
    orgDBase *ptr_dbHead;               /* указатель на начало массива записей из БД */
    DBQueue* sr_keyQueue;
    stAVLTree *tr_srchRoot;

    /* загрузка БД из файла в память */
    CharToOem("Загрузка БД...", oem_str);
    printf("%s\n", oem_str);
    dbase_loadFromFile(fname);

    ind_buildIndexArray();

    /* Вывод на экран полей БД из памяти */
    clrscr();

    int index = 0;
    char c;
    while(true) {
      dbase_drawTable(index);
      c = getch();
      switch(c) {
        case 113 :
          clrscr();
          printf("Search: ");
          char key[2];
          scanf("%s", &key);
          sr_keyQueue = NULL;
          sr_keyQueue = dbase_searchByKey(key);
          /* Debug
           * queuePrint(sr_keyQueue);
           * */
          CharToOem("Найдено элементов: ", oem_str);
          printf("%s%d\n", oem_str, sr_keyQueue->queueGetSize());
          tr_srchRoot = NULL;
          tr_srchRoot = tr_buildAVLTree(sr_keyQueue, sr_keyQueue->queueGetSize());
          /* Debug
           * CharToOem("АВЛ-дерево:", oem_str);
           * printf("\n%s\n", oem_str);
           * tr_goFromLeftToRight(tr_srchRoot, 0);
           * */

          CharToOem("Средняя высота дерева: ", oem_str);
          printf("%s%5.2f\n", oem_str, tr_getAverageHeight(tr_srchRoot));
          CharToOem("Поиск в дереве: ", oem_str);
          printf("%s", oem_str);
          scanf("%d", &c);
          if ((c > 0) && (c < 32)) {
                int t_count = 0;
                stAVLTree* findElem; // найденный элемент
                CharToOem("Ключ ", oem_str);
                printf("%s", oem_str);
                bool isFind = true;
                if (!tr_searchInTree(tr_srchRoot, c, &t_count, &findElem)) {
                        CharToOem("не ", oem_str);
                        printf("%s", oem_str);
                        isFind = false;
                }
                CharToOem("найден в дереве.", oem_str);
                printf("%s\n", oem_str);
                CharToOem("Переходов: ", oem_str);
                printf("%s%d\n", oem_str, t_count);

                if (isFind) {
                printf("%c", 201);
                for (int i = 0; i < 80 - 2; i++)
                      printf("%c", 205);
                printf("%c", 187);
                printf("%c", 186);
                printf("           Employer name           %c  #"
                       "  %c          Post          %c Birth day"
                       " ", 179, 179, 179);
                printf("%c", 186);

                printf("%c", 204);
                for (int i = 0; i < 80 - 2; i++)
                        printf("%c", 205);
                printf("%c", 185);

                printf("%c", 186);
                printf("  ");
                for (int i = 0; i < NAMESIZE; i++)
                        printf("%c", findElem->key->name[i]);
                printf(" %c ", 179);

                printf("%3d", findElem->key->depnum);
                printf(" %c ", 179);

                for (int i = 0; i < POSTSIZE; i++)
                        printf("%c", findElem->key->post[i]);
                printf(" %c ", 179);

                for (int i = 0; i < BDATESIZE; i++)
                        printf("%c", findElem->key->bdate[i]);
                printf("  ");
                printf("%c", 186);

                for (int i = 0; i < findElem->eqCount; i++) {

                        printf("%c", 186);
                        printf("  ");
                        for (int j = 0; j < NAMESIZE; j++)
                                printf("%c", findElem->eq[i]->name[j]);
                        printf(" %c ", 179);

                        printf("%3d", findElem->eq[i]->depnum);
                        printf(" %c ", 179);

                        for (int j = 0; j < POSTSIZE; j++)
                                printf("%c", findElem->eq[i]->post[j]);
                        printf(" %c ", 179);

                        for (int j = 0; j < BDATESIZE; j++)
                                printf("%c", findElem->eq[i]->bdate[j]);
                        printf("  ");
                        printf("%c", 186);
                }

                printf("%c", 200);
                for (int i = 0; i < 80 - 2; i++)
                      printf("%c", 205);
                printf("%c\n", 188);
                }
          } else {
                CharToOem("Значение ключа поиска вне диапазона!", oem_str);
                printf("%s\n", oem_str);
          }
          getch();
          clrscr();
          break;

        case 115 :
          ind_sortHoarArray(0, empCount-1);
          break;

        case 72 :
          if (index > 0) index--;
          break;

        case 80 :
          if (index < empCount - 15) index++;
          break;

        case 73 :
          if (index > 0) {
            if ((index - 15) >= 0) index -=15;
          }
          break;

        case 81 :
          if (index < empCount - 15) {
            if ((index + 15) < empCount - 15) index +=15;
            else index = empCount - 15;
          }
          break;

        case 27 :
          free(indDBArrayElem);
          free(orgDBArray);
          return 0;
      }
    }
}

