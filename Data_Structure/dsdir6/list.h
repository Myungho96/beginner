//B590011,3학년,김명호
#ifndef LIST_H
#define LIST_H
#include<iostream>
using namespace std;

struct Node {
	Node(int d = 0, Node* l = 0) :data(d), link(l) {}
	int data;
	Node* link;
};

class IntList {
public:
	IntList() {
		last = first = 0;
	}
	bool IsEmpty() {
		return !first;
	}
	void Push_Back(int);

	int Front();
	void Pop_Front();
	void Push_Front(int);
	void Insert(int);
private:
	Node* first;
	Node* last;
	friend ostream& operator<<(ostream&, IntList&);
};

ostream& operator<<(ostream&, IntList&);
#endif
