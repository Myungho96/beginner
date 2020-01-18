#include<iostream>
#include"post.h"
using namespace std;
void Postfix(Expression);
int main() {
	char linebuf[MAXLEN];
	while (cin.getline(linebuf, MAXLEN)) {

		Expression e(linebuf, true);

		try { Postfix(e); }
		catch (char* msg) {
			cerr << "Exception: " << msg << endl;
		}
	}
}