//B590011,3학년,김명호
#include<iostream>
#include"post.h"
using namespace std;

void Eval(Expression);

int main(void) {
	char line[MAXLEN];
	while (cin.getline(line, MAXLEN)) {
		Expression e(line);
		try {
			Eval(e);
		}
		catch (char const* msg) {
			cerr << "Exception: " << msg << endl;
		}
	}
}
