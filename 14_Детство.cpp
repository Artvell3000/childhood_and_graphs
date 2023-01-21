#include <fstream>
#include <iostream>
using namespace std;

struct el {
	int s;
	el* next;
};

void eiler_cycle(int** M, int n, int start) {
	int i;
	el* C = nullptr;
	el* S = nullptr;
	el* p0 = new el;

	p0->s = start;
	p0->next = nullptr;
	S = p0;

	while (S != nullptr) {
		int x = S->s, y = -1;

		for (i = 0;i < n and y == -1;i++)
			if (M[x][i] != 0) {
				y = i;
			}
		if (y != -1) {
			el* p = new el;
			p->s = y;
			p->next = S;
			S = p;

			M[x][y] = 0;
			M[y][x] = 0;
		}
		else {
			el* p = S;
			S = S->next;
			p->next = C;
			C = p;
		}

	}

	cout << "Путь:" << endl;
	for (el* p = C;p != nullptr;p = p->next) {
		cout << p->s << " ";
	}
	cout << endl;
}

int main() {
	setlocale(LC_ALL,"ru");
	ifstream fin("in_envelope.txt");
	/*
	in_cycle.txt
	in_envelope.txt
	in_star.txt
	in_way.txt
	in_error.txt
	*/

	if (!fin) return -1;
	int n,i;
	fin >> n;
	int** M = new int* [n];
	for (int i = 0;i < n;i++) {
		M[i] = new int[n];
		for (int j = 0;j < n;j++)
			M[i][j] = 0;
	}

	while (!fin.eof()) {
		int a, b;
		fin >> a >> b;
		M[a][b] = 1;
		M[b][a] = 1;
	}

	int start;
	int q = 0;

	for (i = 0;i < n;i++) {
		int k = 0;
		for (int j = 0;j < n;j++)k += M[i][j];
		
		if (k % 2 == 1) {
			start = i;
			q++;
		}
	}

	if (q == 0) {
		cout << "Можно нарисовать эту фигуру, начиная и заканчивая рисование в одной и той же точке." << endl;
		eiler_cycle(M, n, 0);
	}
	else if (q == 2) {
		cout << "Можно нарисовать эту фигуру, начиная и заканчивая рисование в различных точках." << endl;
		eiler_cycle(M, n, start);
	}
	else {
		cout << "Нельзя нарисовать эту фигуру(без наложения линий), не отрывая карандаша от бумаги." << endl;
		return 0;
	}
}

 

