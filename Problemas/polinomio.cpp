#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

template<class T>
class Polinomio{
    vector<T> coef;
    T grado;

	void eleva(const T & num, vector<T> & p){
		p.push_back(1);
		for (int i = 1; i <= grado; i++){
			p.push_back(p[i - 1] * num);
		}
	}


public:
	T resuelve(const T & num){
		T sol = 0;
		T g = grado;
		vector<T> p;
		eleva(num, p);
		for (int i = 0; i < coef.size(); i++, g--){
			sol += coef[i] * p[grado - i];
		}
		return sol;
	}

	bool leerPolinomio(){
		cin>>grado;
		if(!cin) return false;
		for(int i=0; i<=grado; i++){
		 int c;
		 cin>>c;
		 coef.push_back(c);
	 	}
		return true;
	}

};




bool resuelveCaso(){
	Polinomio<int> pol;
	if(pol.leerPolinomio()){
		 int num;
		 cin >> num;
		 while (num != 0){
			 cout << pol.resuelve(num) << endl;
			 cin >> num;
		 }
		 return true;
	}
	return false;	
}



int main() {

	while (resuelveCaso()) {}

	return 0;
}
