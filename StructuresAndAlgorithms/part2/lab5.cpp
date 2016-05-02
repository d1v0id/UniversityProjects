/*
 * Структуры и алгоритмы обработки данных часть 2
 *
 * Лабораторная работа 5
 * */
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>

#define MAXN 500 /* максимальное количество элементов массива */

struct sMyArray {
	int a;
	int w;
	bool use;
};


typedef sMyArray my_arr[MAXN]; /* объявляем тип-массив */
my_arr v;

int wsum = 0;

struct sTree {
    int data;
    int weight; /* вес */
    sTree *left;
    sTree *right;
};

int n = 10;

char oem_str[255];

/* построение массива */
void arr_buildArr(my_arr a, int n, int t, int maxVal, int d) {
	if (d == 0) {
		switch (t) {
			case 0:
				for (int i = 0; i < n; i++) {
					a[i].a = i + 1;
					printf("%d ", a[i].a);
				} break;
			case 1:
				for (int i = 0; i < n; i++) {
					a[i].a = n-i;
					printf("%d ", a[i].a);
				} break;
			case 2:
				int i = 0;
				while (i < n) {
					a[i].a = rand() % maxVal;
					bool arr_dubl = false;
					for (int j = 0; j < i; j++)
					if (a[i].a == a[j].a) arr_dubl = true;
					if (!arr_dubl) {
						printf("%d ", a[i].a);
						i++;
					}
				} break;
		}
	} else if (d == 1) {
		switch (t) {
				case 0:
					for (int i = 0; i < n; i++) {
						a[i].w = i + 1;
						printf("%d ", a[i].w);
					} break;
				case 1:
					for (int i = 0; i < n; i++) {
						a[i].w = n-i;
						printf("%d ", a[i].w);
					} break;
				case 2:
					int i = 0;
					while (i < n) {
						a[i].w = rand() % maxVal;
						bool arr_dubl = false;
						for (int j = 0; j < i; j++)
						if (a[i].w == a[j].w) arr_dubl = true;
						if (!arr_dubl) {
							printf("%d ", a[i].w);
							i++;
						}
					} break;
		}
	}
	printf("\n");
}

/* добавление элемента в СДП */
void tr_addToSDP(sTree **p, sMyArray a) {
	while ((*p) != NULL) {
		if ((*p)->data > a.w) p = &((*p)->left);
		else if ((*p)->data < a.w) p = &((*p)->right);
			 else break;
	}
	if ((*p) == NULL) {
		(*p) = new(sTree);
		(*p)->data = a.a;
		(*p)->weight = a.w;
		(*p)->left = NULL;
		(*p)->right = NULL;
	}
	return;
}

/* построение ДОП методом А1 */
void tr_buildDOPa1(sTree **t) {
	(*t) = NULL;
	for (int i = 0; i < n; i++) v[i].use = false;
	for (int i = 0; i < n; i++) {
		int max = 0;
		int index = 0;
		for (int j = 0; j < n; j++) {
			if ((v[j].w > max) && (!v[j].use)) {
				max = v[j].w;
				index = j;
			}
		}
		v[index].use = true;
		tr_addToSDP(t, v[index]);
	}

	return;
}

/* построение ДОП методом А2 */
void tr_buildDOPa2(sTree **t, int l, int r) {
	int i;
	int wes = 0;
	int summa = 0;
	if (l <= r) {
		for (i = l; i <= r; i++) wes = wes + v[i].w;
		for (i = l; i <= r-1; i++) {
			if ((summa < wes/2) && (summa + v[i].w >= wes/2)) break;
			summa += v[i].w;
		}
		tr_addToSDP(t, v[i]);
		tr_buildDOPa2(t, l, i-1);
		tr_buildDOPa2(t, i+1, r);
	}

	return;
}

int tr_getSize(sTree *t) {
	return (t == NULL) ? 0 : 1+tr_getSize(t->left)+tr_getSize(t->right);
}

void tr_getWidthSum(sTree *p) {
        if (p == NULL) return;
	tr_getWidthSum(p->left);
        wsum += p->weight;
	tr_getWidthSum(p->right);
	return;
}

int tr_sdp(sTree *t, int l) {
	return (t == NULL) ? 0 : t->weight*l+tr_sdp(t->left, l+1)+tr_sdp(t->right, l+1);
}

float tr_getAverageHeight(sTree *t) {
        tr_getWidthSum(t);
	return (float)tr_sdp(t, 1) / wsum;
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
	sTree *root = NULL; /* указатель на дерево */
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
                CharToOem("4) Заполнить массив весов упорядоченными числами", oem_str);
		printf("%s\n", oem_str);
                CharToOem("5) Заполнить массив весов числами в обратном порядке", oem_str);
		printf("%s\n", oem_str);
                CharToOem("6) Заполнить массив весов случайными числами", oem_str);
		printf("%s\n", oem_str);
                CharToOem("7) Построить ДОП методом А1", oem_str);
		printf("%s\n", oem_str);
                CharToOem("8) Построить ДОП методом А2", oem_str);
		printf("%s\n", oem_str);
                CharToOem("9) Вычисление средневзвешенной высоты дерева", oem_str);
		printf("%s\n", oem_str);
                CharToOem("0) Выход", oem_str);
		printf("%s\n", oem_str);
		printf(">");
		scanf("%d", &c);
		switch(c) {
			case 1: arr_buildArr(v, n, 0, MAXN, 0); break;
			case 2: arr_buildArr(v, n, 1, MAXN, 0); break;
			case 3: arr_buildArr(v, n, 2, MAXN, 0); break;
			case 4: arr_buildArr(v, n, 0, MAXN, 1); break;
			case 5: arr_buildArr(v, n, 1, MAXN, 1); break;
			case 6:	arr_buildArr(v, n, 2, MAXN, 1); break;
			case 7:
				tr_buildDOPa1(&root);
				tr_goFromLeftToRight(root, 0);
				printf("\n");
                                break;
			case 8:
				tr_buildDOPa2(&root, 0, n-1);
				tr_goFromLeftToRight(root, 0);
				printf("\n");
                                break;
			case 9:
                                if (root != NULL) {
                                        CharToOem("Средняя высота: ", oem_str);
                                        printf("%s%5.2f\n", oem_str, tr_getAverageHeight(root));
                                }
                                break;
			case 0: return 0;
		}
	}
}

