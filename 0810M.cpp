#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool abierto(char const & ch) {
	if (ch == '(' || ch == '{' || ch == '[')return true;
	return false;
}

bool cerrado(char const & ch) {
	if (ch == ')' || ch == '}' || ch == ']')return true;
	return false;
}

bool corresponden(char const & pilach, char const & ch) {
	if ((pilach == '(') && (ch == ')')) return true;
	else if ((pilach == '{') && (ch == '}')) return true;
	else if ((pilach == '[') && (ch == ']')) return true;
	return false;
}

bool procesa(char const & ch, stack<char> & pila) {
	if (abierto(ch)) {
		pila.push(ch);
	}
	else if (cerrado(ch)) {
		if (!pila.empty() && corresponden(pila.top(), ch)) {
			pila.pop();
		}
		else { return false; }
	}
	return true;
}

bool resuelve() {
	string str;
	getline(cin, str);
	stack<char> pila;
	bool equilibrado = true;
	if (str == ".") return false;
	for (int i = 0; i < str.size() && equilibrado; i++){
		if (!procesa(str.at(i), pila)) { equilibrado = false; }
	}
	if (!pila.empty() || !equilibrado) { cout << "NO" << endl; }
	else { cout << "YES" << endl; }
	return true;	
}


int main() {

	while (resuelve()) {}

	return 0;
}