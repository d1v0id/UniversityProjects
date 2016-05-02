/*
 * Структуры и алгоритмы обработки данных часть 2
 *
 * Лабораторная работа 4
 * */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>

#define MAXN 300 /* максимальное количество элементов массива */
#define M 2 /* ? */

typedef int my_arr[MAXN]; /* объявляем тип-массив */

struct sTree {
	int data;
	int balance;
	sTree *left;
	sTree *right;
};

bool vr, hr;

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

/* добавление в Б-дерево */
void tr_addToBTree(sTree **p, int x) {
	sTree *q;
	if ((*p) == NULL) {
		(*p) = new(sTree);
		(*p)->data = x;
		(*p)->left = NULL;
		(*p)->right = NULL;
		(*p)->balance = 0;
		vr = true;
	} else {
		if ((*p)->data > x) {
			tr_addToBTree(&(*p)->left, x);
			if (vr) {
				if ((*p)->balance == 0) {
					q = (*p)->left;
					(*p)->left = q->right;
					q->right = (*p);
					(*p) = q;
					q->balance = 1;
					vr = false;
					hr = true;
				} else {
					(*p)->balance = 0;
					hr = true;
				}
			} else hr = false;
		} else if ((*p)->data < x) {
			tr_addToBTree(&(*p)->right, x);
			if (vr) {
				(*p)->balance = 1;
				vr = false;
				hr = true;
			} else {
				if (hr) {
					if ((*p)->balance > 0) {
						q = (*p)->right;
						(*p)->right = q->left;
						(*p)->balance = 0;
						q->balance = 0;
						q->left = (*p);
						(*p) = q;
						vr = true;
						hr = false;
					} else hr = false;
				}
			}
		}
	}
}

/* построение Б-дерева */
sTree* tr_buildBTree(my_arr arr, int n) {
	sTree *t; /* указатель на вершину дерева */
	sTree **p; /* указатель на указатель на вершину дерева */
	t = new(sTree);
	t->data = arr[0];
	t->left = NULL;
	t->right = NULL;
	t->balance = 0;
	for (int i = 1; i < n; i++) {
		p = &t;
		vr = false;
		hr = false;
		tr_addToBTree(&(*p), arr[i]);
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
        CharToOem("4) Поистроить двоичное Б-дерево", oem_str);
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
			case 1: arr_buildArr(arr, n, 0); break;
			case 2: arr_buildArr(arr, n, 1); break;
			case 3: arr_buildArr(arr, n, 2); break;
			case 4: root = tr_buildBTree(arr, n); break;
			case 5:
                                CharToOem("Средняя высота: ", oem_str);
                                printf("%s%5.2f\n", oem_str, tr_getAverageHeight(root));
                                break;
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
                                } break;
			case 8:
				tr_goFromLeftToRight(root, 0);
				printf("\n"); break;
			case 9: return 0;
		}
	}
}

