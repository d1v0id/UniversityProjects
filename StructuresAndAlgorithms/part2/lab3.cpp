/*
 * Структуры и алгоритмы обработки данных часть 2
 *
 * Лабораторная работа 3
 * */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>

#define MAXN 500 /* максимальное количество элементов массива */

typedef int my_arr[MAXN]; /* объявляем тип-массив */

struct sTree {
	int data;
	int balance;
	sTree *left;
	sTree *right;
};

bool grow;
int turns; /* количество поворотов */

char oem_str[255];

/* построение массива */
void arr_buildArr(my_arr arr, int n, int t) {
	switch (t) {
		case 0:
			for (int i = 0; i < n; i++) {
				arr[i] = i + 1;
				printf("%d ", arr[i]);
			} break;
		case 1:
			for (int i = 0; i < n; i++) {
				arr[i] = n-i;
				printf("%d ", arr[i]);
			} break;
		case 2:
			int i = 0;
			while (i < n) {
				arr[i] = rand() % MAXN;
				bool arr_dubl = false;
				for (int j = 0; j < i; j++)
					if (arr[i] == arr[j]) arr_dubl = true;
				if (!arr_dubl) {
					printf("%d ", arr[i]);
					i++;
				}
			} break;
	}
	printf("\n");
}

/* LL поворот */
void tr_llTurn(sTree **p) {
	sTree *q;
	q = (*p)->left;
	q->balance = 0;
	(*p)->balance = 0;
	(*p)->left = q->right;
	q->right = (*p);
	(*p) = q;
}

/* LR поворот */
void tr_lrTurn(sTree **p) {
	sTree *q;
	sTree *r;
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

/* RL поворот */
void tr_rlTurn(sTree **p) {
	sTree *q = (*p)->right;
	sTree *r = q->left;
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

/* RR поворот */
void tr_rrTurn(sTree **p) {
	sTree *q;
	q = (*p)->right;
	q->balance = 0;
	(*p)->balance = 0;
	(*p)->right = q->left;
	q->left = (*p);
	(*p) = q;
}

/* добавление вершины в АВЛ дерево */
void tr_addToAVL(sTree **p, int x) {
	if ((*p) == NULL) {
		(*p) = new(sTree);
		(*p)->data = x;
		(*p)->left = NULL;
		(*p)->right = NULL;
		(*p)->balance = 0;
		grow = true;
	} else {
		if ((*p)->data > x) {
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

		} else {
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
                                          else tr_rlTurn(&(*p));
                                          turns++;
                                          grow = false;
					}
			        }
		}
	}

}

/* построение АВЛ дерева */
sTree* tr_buildAVL(my_arr arr, int n) {
	sTree *t; /* указатель на вершину дерева */
	sTree **p; /* указатель на указатель на вершину дерева */
	turns = 0;
	t = new(sTree);
	t->data = arr[0];
	t->left = NULL;
	t->right = NULL;
	t->balance = 0;
	for (int i = 1; i < n; i++) {
		p = &t;
		grow = false;
		tr_addToAVL(&(*p), arr[i]);
	}
	return t;
}

int tr_getSize(sTree *t) {
	return (t == NULL) ? 0 : 1+tr_getSize(t->left)+tr_getSize(t->right);
}

int tr_sdp(sTree *t, int l) {
	return (t == NULL) ? 0 : l+tr_sdp(t->left, l+1)+tr_sdp(t->right, l+1);
}

float tr_getAverageHeight(sTree *t) {
	return ((float)tr_sdp(t, 1) / tr_getSize(t));
}

/* проверка, является ли деревом поиска */
bool tr_isSearchTree(sTree *p) {
	return ((p != NULL) && (( (p->left != NULL) &&
	((p->data <= p->left->data) || !tr_isSearchTree(p->left))) ||
	((p->right != NULL) && ((p->data >= p->right->data) || (!tr_isSearchTree(p->right)))))
	) ? false : true;
}

/* поиск в дереве */
bool tr_searchInTree(sTree *p, int x, int *c_count) {
	while (p != NULL) {
		if (p->data < x) {
			p = p->right;
			(*c_count)++;
		} else if (p->data > x) {
			p = p->left;
			(*c_count)++;
		} else break;
	}
	return (p != NULL) ? true : false;
}

/* вывод дерева */
void tr_goFromLeftToRight(sTree *p, int s) {
	if (p == NULL) return;
	tr_goFromLeftToRight(p->left, ++s);
	for (int i = 0; i < s; ++i) printf("|");
	printf("%d\n", p->data);
	s--;
	tr_goFromLeftToRight(p->right, ++s);
	return;
}

int main (int argc, char **argv) {
	sTree *root; /* указатель на дерево */
	my_arr arr;
	int n;
	int c; /* номер команды из меню */
        CharToOem("Введите число элементов дерева: ", oem_str);
	printf("%s", oem_str);
	scanf("%d", &n);
	while (true) {
        CharToOem("[Меню]", oem_str);
	printf("%s\n", oem_str);
        CharToOem("1) Заполнить массив упорядоченными числами", oem_str);
	printf("%s\n", oem_str);
        CharToOem("2) Заполнить массив числами в обратном порядке", oem_str);
	printf("%s\n", oem_str);
        CharToOem("3) Заполнить массив случайными числами", oem_str);
	printf("%s\n", oem_str);
        CharToOem("4) Построить АВЛ дерево", oem_str);
	printf("%s\n", oem_str);
        CharToOem("5) Вычисление средней высоты дерева", oem_str);
	printf("%s\n", oem_str);
        CharToOem("6) Определить, является ли деревом поиска", oem_str);
	printf("%s\n", oem_str);
        CharToOem("7) Поиск в дереве", oem_str);
	printf("%s\n", oem_str);
        CharToOem("8) Вывод дерева", oem_str);
	printf("%s\n", oem_str);
        CharToOem("9) Выход", oem_str);
	printf("%s\n", oem_str);
	scanf("%d", &c);
		switch(c) {
			case 1: arr_buildArr(arr, n, 0);
                          break;
			case 2: arr_buildArr(arr, n, 1); break;
			case 3: arr_buildArr(arr, n, 2); break;
			case 4:
				root = tr_buildAVL(arr, n);
                                CharToOem("Поворотов = ", oem_str);
				printf("%s%d\n", oem_str, turns); break;
			case 5:
                                CharToOem("Средняя высота: ", oem_str);
                                printf("%s%5.2f\n", oem_str, tr_getAverageHeight(root)); break;
			case 6:
				CharToOem("Дерево ", oem_str);
                                printf("%s", oem_str);
				if (!tr_isSearchTree(root)) {
                                        CharToOem("не ", oem_str);
                                        printf("%s", oem_str);
                                }
                                CharToOem("является деревом поиска.", oem_str);
				printf("%s\n", oem_str); break;
			case 7:
                                CharToOem("Ключ поиска: ", oem_str);
				printf("%s", oem_str);
				scanf("%d", &c);
				if ((c > 0) && (c < MAXN)) {
        				int c_count = 0;
                                        CharToOem("Ключ ", oem_str);
        				printf("%s", oem_str);
        				if (!tr_searchInTree(root, c, &c_count)) {
                                                CharToOem("не ", oem_str);
                                                printf("%s", oem_str);
                                        }
                                        CharToOem("найден в дереве.", oem_str);
        				printf("%s\n", oem_str);
        				printf("c_count = %d\n", c_count);
				} else {
                                        CharToOem("Ключ вне диапазона!", oem_str);
                                        printf("%s\n", oem_str);
                                }
                                break;
			case 8:
				tr_goFromLeftToRight(root, 0);
				printf("\n"); break;
			case 9: return 0;
		}
	}
}
 
