#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include "DoubleLinkedList.h"
using namespace std;

class Carta {
	int num;
	char palo;

public:
	Carta() {}

	Carta(int n, char p) {
		num = n; palo = p;
	}

	char getPalo() const { return palo; }
	int getNum() const { return num; }

};

bool colocar(vector<Carta> & v, Carta const & c, stack<Carta> & montonB) {
	if (v.size() > 0) {
		if (v.at(v.size() - 1).getNum() == (c.getNum() - 1)) {
			v.push_back(c);
			montonB.pop();
			return true;
		}
	}
	else if (c.getNum() == 1) {
		v.push_back(c);
		montonB.pop();
		return true;
	}
	return false;
}

bool jugar(vector<Carta> & A, vector<Carta> & B, vector<Carta> & C, vector<Carta> & D, Carta const & c, stack<Carta> & montonB) {
	if (c.getPalo() == 'A') { if (colocar(A, c, montonB)) return true; }
	else if (c.getPalo() == 'B') { if (colocar(B, c, montonB)) return true; }
	else if (c.getPalo() == 'C') { if (colocar(C, c, montonB)) return true; }
	else if (c.getPalo() == 'D') { if (colocar(D, c, montonB)) return true; }
	return false;
}

int resuelve(stack<Carta> & monton, int const & n) {
	vector<Carta> A, B, C, D;
	stack<Carta> montonB;
	Carta c, aux;
	Carta ultSinMover = monton.top();
	bool movidas = true;
	int cont = 0;

	//mientras tengamos suficientes cartas en el monton
	while (monton.size() >= n) {
		//sacar n cartas
		for (int i = 0; i < n; i++) {
			c = monton.top();
			montonB.push(c);
			monton.pop();
		}

		while (jugar(A, B, C, D, c, montonB)) {
			c = montonB.top();
		}

		if (!movidas && ultSinMover == montonB.top()) {
			return cont;
		}
		
	}
	


}


void caso() {
	int nCartasPalo, nPalos, nCartasSacar;
	cin >> nCartasPalo >> nPalos >> nCartasSacar;

	stack<Carta> monton = stack<Carta>();

	Carta c;
	char ch;
	int num;
	for (int i = 0; i < nCartasPalo*nPalos; i++) {
		cin >> num >> ch;
		c = Carta(num, ch);
		monton.push(c);
	}

	int n = resuelve(monton, nCartasSacar);

	if (n < 0) { cout << "NO" << endl; }
	else cout << "SI " << n << endl;

}


int main() {
	int ncasos;
	cin >> ncasos;
	for (int i = 0; i < ncasos; i++) {
		caso();
	}

	return 0;
}