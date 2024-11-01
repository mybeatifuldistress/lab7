#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <locale>
#include <iostream> 
#include <stack>

using namespace std;
stack <int> S;

int k;
int size1, h;
int** arr1;
int* vis;

struct Node {
	int n;			//Номер вершины (0..N-1)
	Node* next;
};

Node* LA;			//Массив структур - списков смежности [N]

Node* make_LA() {
	Node* la = new Node[size1];
	Node* p;

	for (int i = 0; i < size1; i++) {
		la[i].n = i;
		la[i].next = nullptr;
		p = &la[i];

		for (int j = 0; j < size1; j++) {
			if (arr1[i][j] == 1) {
				p->next = new Node;
				p = p->next;
				p->n = j;
				p->next = nullptr;
			}
		}
	}
	return la;
}

void print_LA() {
	Node* p;
	for (int i = 0; i < size1; i++) {
		p = &LA[i];
		while (p != nullptr) {
			cout << p->n << " > ";
			p = p->next;
		}
		cout << endl;
	}
}

void first_list(int l) {
	Node* p;
	p = &LA[l];
	vis[l] = 1;
	cout << l << ' ';

	while (p->next != nullptr) {
		if (vis[p->next->n] == 0) {
			vis[p->next->n] = 1;
			l = p->next->n;
			first_list(l);
		}
		p = p->next;
	}
}

void create_matrix() {
	for (int i = 0; i < size1; i++) {
		for (int j = i; j < size1; j++) {
			if (i == j) {
				arr1[i][j] = 0;
			}
			else {
				arr1[i][j] = rand() % 2;
				arr1[j][i] = arr1[i][j];
			}
		}
	}
}

void print_matrix() {
	cout << "     " << endl;
	for (int i = 0; i < size1; i++) {
		cout << i << ' ';
	}
	cout << endl;
	cout << "-----------------------------------------------------------\n";

	for (int i = 0; i < size1; i++) {
		cout << i << '|';
		for (int j = 0; j < size1; j++) {
			cout << arr1[i][j] << ' ';
		}
		cout << endl;;
	}
	cout << endl;;
}

void print_vis() {
	cout << "\nМассив vis:\n";
	for (int i = 0; i < size1; i++) {
		cout << vis[i];
	}
	cout << "\n\n";
}

void DFS1(int s) {
	vis[s] = 1;
	cout << s << ' ';
	for (int i = 0; i < size1; i++) {
		if ((arr1[s][i] == 1) && (vis[i] == 0)) {
			DFS1(i);
		}
	}
}

void DES2(int s) {
	vis[s] = 1;
	cout << s << ' ';
	S.push(s);
	while (!S.empty()) {
		s = S.top();
		S.pop();
		for (int i = size1 - 1; i >= 0; i--) {
			if ((arr1[s][i] == 1) && (vis[i] == 0)) {
				cout << i << ' ';
				vis[i] = 1;
				S.push(i);
			}
		}
	}
}

void clean_vis() {
	for (int i = 0; i < size1; i++) {
		vis[i] = 0;
	}
}

int main() {

	srand(time(NULL));
	setlocale(LC_ALL, "");

	cout << "Задание 1\n";
	cout << "Введите размер матрицы смежности M1: ";
	cin >> size1;
	cout << endl;

	vis = new int[size1];

	arr1 = new int* [size1];
	for (int i = 0; i < size1; i++) {
		arr1[i] = new int[size1];
	}

	cout << "Матрица M1:\n";
	create_matrix();
	print_matrix();

	clean_vis();
	cout << "=======================================================================\n\n";
	cout << "Задание 2\n";
	cout << "Введите вершину от (0 до " << size1 - 1 << ") для начала обхода: ";
	cin >> h;

	int l = h;

	k = h;
	cout << endl;
	cout << "был в вершинах: ";

	DFS1(h);
	cout << endl;

	clean_vis();

	cout << endl;

	cout << "=======================================================================\n\n";
	cout << "Задание 3\n";
	cout << "Список смежности S1:\n";
	LA = make_LA();
	print_LA();
	cout << endl;

	cout << "был в вершинах: ";
	first_list(l);
	cout << endl;

	cout << "=======================================================================\n\n";
	cout << "Задание 4\n";

	clean_vis();
	cout << "был в вершинах: ";
	DES2(k);

	for (int i = 0; i < size1; ++i) delete[] arr1[i];
	delete[] arr1;
	delete[] vis;
	delete[] LA;

	return 0;
}