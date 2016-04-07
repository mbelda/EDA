#include <iostream>
#include <string>
#include <vector>
#include <stack>
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

bool resuelve(stack<Carta> & monton, int const & n, int & cont) {
	vector<Carta> A, B, C, D;
	stack<Carta> montonB;
	Carta c, aux;
	bool movidas = true;
    
    while(movidas){
        movidas=false;
    	//mientras tengamos suficientes cartas en el monton
    	while (monton.size() >= n) {
    		//sacar n cartas
    		for (int i = 0; i < n; i++) {
    			c = monton.top();
    			montonB.push(c);
    			monton.pop();
    		}
			bool hayCartas = true;
			while (jugar(A, B, C, D, c, montonB) && hayCartas) {
				movidas = true;
				if (!montonB.empty()) {
					hayCartas = true;
					c = montonB.top();
				}
				else { hayCartas = false; }
    		}
    		
    	}
    	//Si quedan menos de n cartas en el monton pero mas de 0 las sacas
    	while(!monton.empty()){
    	    c = monton.top();
    		montonB.push(c);
    		monton.pop();  
    	}
		bool hayCartas2 = true;
    	//juegas las caras que has sacado
		while (jugar(A, B, C, D, c, montonB) && hayCartas2) {
		    movidas=true;
			if (!montonB.empty()) {
				hayCartas2 = true;
				c = montonB.top();
			}
		}
		
		//pasas las cartas de B a A
		while (!montonB.empty()) {
			monton.push(montonB.top());
			montonB.pop();
		}
        
        //se ha completado la vuelta
        cont++;
    }
	
    if(monton.size() > 0) return false;
    else return true;

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
    
	int cont = 0;

	if (resuelve(monton, nCartasSacar, cont)) {cout << "SI " << cont-1 << endl; }
	else cout << "NO" << endl;

}


int main() {
	int ncasos;
	cin >> ncasos;
	for (int i = 0; i < ncasos; i++) {
		caso();
	}

	return 0;
}
