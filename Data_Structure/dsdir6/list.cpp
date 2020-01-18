//B590011,3학년,김명호
#include<iostream>
#include"list.h"
ostream& operator<<(ostream& os, IntList& il) {
	Node* ptr = il.first;
	while (ptr != 0) {
		os << ptr->data << " ";
		ptr = ptr->link;
	}
	os << endl;
	return os;
}

void IntList::Push_Back(int e) {
	if (!first)
		first = last = new Node(e);
	else {
		last->link = new Node(e);
		last = last->link;
	}
}

int IntList::Front() {
	return first->data;
}
void IntList::Pop_Front() {
	first = first->link;
}
void IntList::Push_Front(int e) {
	if (!first)
		first = last = new Node(e);
	else {
		Node* p = new Node(e);
		p->link = first;
		first = p;
	}
}
void IntList::Insert(int e) {
	if (!first)
		first = last = new Node(e);
	else if (first->data > e){
		Node* p = new Node(e);
		p->link = first;
		first = p;
	}
	else if (first->data == e) {
		return;
	}
	else {
		Node* q = first;
		Node * p = first->link;
		while (p && p->data < e) {
			q = p;
			p = p->link;
		}
		if (!p) {
			last->link = new Node(e);
			last = last->link;
		}
		else if (p->data == e)
			return;
		else {
			Node *r = new Node(e);
			q->link = r;
			r->link = p;
		}
	}
}

