#include <iostream>
#include <fstream>
using namespace std;

#define INF 0x7fff
#define VMAX 1000
#define EMAX VMAX * (VMAX - 1) / 2

struct Edges {
    int u;
    int v;
    int w;
};

Edges edge[EMAX];

void ford_bellman(int n, int s, int e, int start)
{
    int i, j;
    int d[VMAX];

    for (i = 0; i < n; i++) {
        d[i] = INF;
    }
    d[s] = 0;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < e; j++) {
            if (d[edge[j].v] + edge[j].w < d[edge[j].u]) {
                d[edge[j].u] = d[edge[j].v] + edge[j].w;
            }
        }
    }

    for (i = 0; i < n; i++) {
        if (d[i] == INF) {
            cout << start << " -> " << i + 1 << " = Not";
        }
        else {
            cout << start << " -> " << i + 1 << " = " << d[i] << endl;
        }
    }
}

int load_graph_from_file(char *filename)
{
	ifstream in(filename);
	if(!in) {
		cout << "Cannot open file.\n";
		return 0;
	}

	int d;
	int cnt = 0;

	while (!in.eof()) {
		in >> d;
		cnt++;
	}

	char buf[256];
	int rows_cnt = 0;

	in.close();
	in.clear();
	in.open(filename);

	while(!in.eof()) {
		in.getline(buf, 255);
		rows_cnt++;
	}
	in.close();
	in.clear();

	cnt--;
	rows_cnt--;
	int cols_cnt = cnt / rows_cnt;

	in.open(filename);
	for (int i = 0; i < rows_cnt; i++) {
		for (int j = 0; j < cols_cnt; j++) {
			edge[i * rows_cnt + j].v = i;
			edge[i * rows_cnt + j].u = j;
			in >> edge[i * rows_cnt + j].w;
			cout << edge[i * rows_cnt + j].w << "\t";
		}
		cout << endl;
	}
	cout << endl;

	return rows_cnt;
}

int main(int argc, char *argv[])
{
    int n;
    int start;

    if (argc > 1) {
		n = load_graph_from_file(argv[1]);

		cout << "Стартовая вершина: ";
		cin >> start;

		cout << "Список кратчайших путей: " << endl;
		ford_bellman(n, start - 1, n * n, start);
    }
    else {
    	cout << "Using: ford_bellman file.txt" << endl;
    	return 1;
    }

    return 0;
}
