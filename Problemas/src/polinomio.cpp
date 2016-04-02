#include <iostream>
#include <vector>
using namespace std;

template<class T>
class Polinomio{
    vector<T> coef;
    int grado;

public:

	Polinomio() { coef = vector<T>(); }

	T resuelve(const T & num){
		T x = 1;
		T sol = 0;

		for (int i = grado; i >= 0; i--) {
			sol += coef[i] * x;
			x *= num;
		}

		return sol;
	}

	bool leerPolinomio(){
		cin>>grado;
		if(!cin) return false;
		for(int i=0; i<=grado; i++){
			T c;
			cin >> c;
			coef.push_back(c);
	 	}
		return true;
	}

};




bool resuelveCaso(){
	Polinomio<long long int> pol = Polinomio<long long int>();
	if(pol.leerPolinomio()){
		long long int num;
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
