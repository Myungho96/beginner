//B590011,3학년,김명호
#include<iostream>
#include<map>
#include<cstring>
using namespace std;

struct cmp {
	bool operator()(char const* a, char const* b) {
		return strcmp(a, b) < 0;
	}
};map<char*, float, cmp>ST;

void StoreIntoST(char* name, float val) {
	ST[name] = val;
}

void PrintValue(char* name) {
	map<char*, float, cmp>::iterator iter;
	iter = ST.find(name);
	if (iter == ST.end())
		cout << name << " does not exist" << endl;
	else
		cout << name << " " << ST[name] << endl;
}

int main() {
	StoreIntoST((char*)"abro", 23);
	StoreIntoST((char*)"bb", 34.5);
	StoreIntoST((char*)"haha", 99);
	ST.erase((char*)"bb");

	StoreIntoST((char*)"bb", 1234.5);

	PrintValue((char*)"bb");
	PrintValue((char*)"haha");
	PrintValue((char*)"hoho");
}
