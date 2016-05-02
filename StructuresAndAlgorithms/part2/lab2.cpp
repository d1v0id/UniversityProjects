/*
 * Структуры и алгоритмы обработки данных часть 2
 *
 * Лабораторная работа 2
 * */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>

#define MAXN 500

typedef int my_arr[MAXN];

struct sTree {
	int key;
	sTree *left, *right;
};

sTree *root;

char oem_str[255];

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

template <class T>
void swap(T& a, T& b) {
	T c(a);
	a=b;
	b=c;
}

void arr_selectionSort(my_arr arr, int n) {
	for (int i = 0; i < n-1; i++) {
		int min = i;
		for (int j = i+1; j < n; j++)
		if(arr[j] < arr[min]) min = j;
		if (arr[min] != arr[i]) swap<int>(arr[i], arr[min]);
	}
}

sTree* tr_buildISDP(my_arr arr, int l, int r) {
	int m;
	if (l > r) return NULL;
	else {
		m = ceil((l+r) / 2);
		sTree *t = new sTree;
		t->key = arr[m];
		t->left = tr_buildISDP(arr, l, m-1);
		t->right = tr_buildISDP(arr, m+1, r);
		return t;
	}
}

void tr_addToSDP(sTree *t, int d) {
	sTree **p = &t;
	do {
		if (d < (*p)->key) {
			p = &((*p)->left);
		} else if (d > (*p)->key) {
			p = &((*p)->right);
		} else break;
	} while ((*p) != NULL);
	if ((*p) == NULL) {
		(*p) = new sTree;
		(*p)->key = d;
		(*p)->right = NULL;
		(*p)->left = NULL;
	}
	return;
}

sTree* tr_buildSDP(my_arr arr, int n) {
	sTree *t = new sTree;
	t->key = arr[0];
	t->left = NULL;
	t->right = NULL;
	for (int i = 1; i < n; i++) tr_addToSDP(t, arr[i]);
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

bool tr_isSearchTree(sTree *t) {
	return ((t != NULL) && (( (t->left != NULL) &&
		((t->key <= t->left->key) || !tr_isSearchTree(t->left))) ||
		((t->right != NULL) && ((t->key >= t->right->key) || (!tr_isSearchTree(t->right)))))
	) ? false : true;
}

bool tr_searchInTree(sTree *t, int x, int *c_count) {
	while (t != NULL) {
		if (t->key < x) {
			t = t->right;
			(*c_count)++;
		} else if (t->key > x) {
			t = t->left;
			(*c_count)++;
		} else break;
	}
	return (t != NULL) ? true : false;
}

void tr_goFromLeftToRight(sTree *t, int s) {
	if (t == NULL) return;
	tr_goFromLeftToRight(t->left, ++s);
	for (int i = 0; i < s; ++i) printf("|");
	printf("%d\n", t->key);
	s--;
	tr_goFromLeftToRight(t->right, ++s);
	return;
}

int main(int argc, char* argv[]) {
	int c, n;
	my_arr arr;
        CharToOem("Размер массива: ", oem_str);
	printf("%s", oem_str);
	scanf("%d", &n);
	while (true) {
                CharToOem("[Меню]", oem_str);
		printf("%s\n", oem_str);
                CharToOem("(1) Заполнить массив числами от 1 до N", oem_str);
		printf("%s\n", oem_str);
                CharToOem("(2) Заполнить массив числами от N до 1", oem_str);
		printf("%s\n", oem_str);
                CharToOem("(3) Заполнить массив случайными числами", oem_str);
		printf("%s\n", oem_str);
                CharToOem("(4) Построить СДП", oem_str);
		printf("%s\n", oem_str);
                CharToOem("(5) Построить ИСДП", oem_str);
		printf("%s\n", oem_str);
                CharToOem("(6) Вычислить среднюю высоту", oem_str);
		printf("%s\n", oem_str);
                CharToOem("(7) Проверить является ли деревом поиска", oem_str);
		printf("%s\n", oem_str);
                CharToOem("(8) Поиск в дереве", oem_str);
		printf("%s\n", oem_str);
                CharToOem("(9) Вывод дерева", oem_str);
		printf("%s\n", oem_str);
                CharToOem("(0) Выход", oem_str);
		printf("%s\n", oem_str);
		printf("-> ");
		scanf("%d", &c);
		switch (c) {
			case 1: arr_buildArr(arr, n, 0); break;
			case 2: arr_buildArr(arr, n, 1); break;
			case 3: arr_buildArr(arr, n, 2); break;
			case 4: root = tr_buildSDP(arr, n); break;
			case 5:
				arr_selectionSort(arr, n);
				root = tr_buildISDP(arr, 0, n-1); break;
			case 6:
                                CharToOem("Средняя высота: ", oem_str);
                                printf("%s%5.2f\n", oem_str, tr_getAverageHeight(root));
                                break;
			case 7:
                                CharToOem("Дерево ", oem_str);
				printf("%s", oem_str);
				if (!tr_isSearchTree(root)) {
                                        CharToOem("не ", oem_str);
                                        printf("%s", oem_str);
                                }
                                CharToOem("является деревом поиска.", oem_str);
				printf("%s\n", oem_str); break;
			case 8:
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
			case 9:
				tr_goFromLeftToRight(root, 0);
				printf("\n"); break;
			case 0:
				delete [] root;
				return 0;
		}
	}
}
 
