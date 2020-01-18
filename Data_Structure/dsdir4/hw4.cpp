//B590011,3학년,김명호
#include<iostream>
#include"post.h"
using namespace std;
void Postfix(Expression);
int main() {
	char linebuf[MAXLEN];
	while (cin.getline(linebuf, MAXLEN)) {

		Expression e(linebuf, true);

		try { Postfix(e); }
		catch (char const *msg) {
			cerr << "Exception: " << msg << endl;
		}
	}
}
