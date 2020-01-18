#ifndef BST_H
#define BST_H
#include<iostream>
#include<queue>
using namespace std;

template<class K, class E>
struct Node {
	Node(K ky, E el, Node<K, E>* left = 0, Node<K, E>* right = 0) :key(ky), element(el), leftChild(left), rightChild(right), leftSize(1) {}

	int leftSize;
	Node<K, E>* leftChild;
	K key;
	E element;
	Node<K, E>* rightChild;
};

template<class K, class E>
class BST {
public:
	BST() { root = 0; }
	void Insert(K& newkey, E el) { Insert(root, newkey, el); }
	void Preorder() { Preorder(root); }
	void Inorder() { Inorder(root); }
	void Postorder() { Postorder(root); }

	void Levelorder();
	/////////////////////////////////////////////////////////////////
	//int leftsize(Node<K, E>*);
	///////////////////////////////////////////////////
	bool Get(const K&, E&);
	void Print();
	//////////////////////-------------------------///////////////////////
	bool RankGet(int r, K &k, E &e);
	void Delete(K& oldkey) { Delete(root, oldkey); }
	void ThreeWayJoin(BST<K, E>& small, K midkey, E midel, BST<K, E>& big);
	void TwoWayJoin(BST<K, E>& small, BST<K, E>& big);
	/////////////////////---------------------------////////////////////////
	//////////////////////////////////////////////////////
private:
	void Visit(Node<K, E>*);
	void Insert(Node<K, E>*&, K, E);
	void Preorder(Node<K, E>*);
	void Inorder(Node<K, E>*);
	void Postorder(Node<K, E>*);
	//////////////////////////////////////////////////////////
	void Delete(Node < K, E>*&, K&);
	/////////////////////////////////////////////////////////////////
	Node<K, E>* root;
};

template<class K, class E>
void BST<K, E>::Visit(Node<K, E>* ptr) {
	cout << ptr->key << ":" << ptr->element << " ";
}

template<class K, class E>
void BST<K, E>::Insert(Node<K, E>*& ptr, K newkey, E el) {
	if (ptr == 0) ptr = new Node<K, E>(newkey, el);
	else if (newkey < ptr->key) { 
		ptr->leftSize++;
		Insert(ptr->leftChild, newkey, el); }
	else if (newkey > ptr->key) Insert(ptr->rightChild, newkey, el);
	else ptr->element = el;
}

///////////////////////////////////////////////////////////////////////////////
template<class K, class E>
bool BST<K, E>::Get(const K& k, E& e) {
	Node<K, E>* ptr = root;
	while (ptr) {
		if (k < ptr->key)
			ptr=ptr->leftChild;
		else if (k > ptr->key)
			ptr=ptr->rightChild;
		else { e = ptr->element; return true; }
	}
	return false;
}

template<class K, class E>
void BST<K, E>::Print() {
	cout << endl << "Inorder traversal : "; Inorder();
	cout << endl << "Postorder traversal : "; Postorder();
	cout << endl;
}

///////////////////////////////////////////////////////////////////////////////

template<class K, class E>
void BST<K, E>::Preorder(Node<K, E>* currentNode) {
	if (currentNode) {
		Visit(currentNode);
		Preorder(currentNode->leftChild);
		Preorder(currentNode->rightChild);
	}
}

template<class K, class E>
void BST<K, E>::Inorder(Node<K, E>* currentNode) {
	if (currentNode) {
		Inorder(currentNode->leftChild);
		Visit(currentNode);
		Inorder(currentNode->rightChild);
	}
}


template<class K, class E>
void BST<K, E>::Postorder(Node<K, E>* currentNode) {
	if (currentNode) {
		Postorder(currentNode->leftChild);
		Postorder(currentNode->rightChild);
		Visit(currentNode);
	}
}

template<class K, class E>
void BST<K, E>::Levelorder() {
	queue<Node<K, E>*> q;
	Node<K, E>* currentNode = root;
	while (currentNode) {
		Visit(currentNode);
		if (currentNode->leftChild)
			q.push(currentNode->leftChild);
		if (currentNode->rightChild)
			q.push(currentNode->rightChild);
		if (q.empty()) return;
		currentNode = q.front();
		q.pop();
	}
}

///////////////////////////////////////////////////////////
//template<class K, class E>
//int BST<K, E>::leftsize(Node<K, E>* currentNode) {
//	if (currentNode == NULL)return 0;
//	int sum = leftsize(currentNode->leftChild) + leftsize(currentNode->rightChild) + 1;
//	return sum;
//}


template<class K, class E>
bool BST<K, E>::RankGet(int r, K &k, E &e) {
	Node<K, E>* currentNode = root;

	while (currentNode) {
		//currentNode->leftSize = leftsize(currentNode->leftChild)+1;
		if (r < currentNode->leftSize)
			currentNode = currentNode->leftChild;
		else if (r > currentNode->leftSize) {
			r = r - currentNode->leftSize;
			currentNode = currentNode->rightChild;
		}
		else {
			k = currentNode->key;
			e = currentNode->element;
			return 1;
		}
	}
	return 0;

}

template<class K, class E>
void BST<K, E>::Delete(Node<K, E>*& ptr, K& oldkey) {
	//delete oldkey to ptr that is root of tree
	Node<K, E>* tmpptr;
	Node<K, E>* tmpdaddyptr;
	if (ptr == 0)return;//there is no exsit.
	if (oldkey < ptr->key) {
		ptr->leftSize--;
		Delete(ptr->leftChild, oldkey);
	}
	else if (oldkey > ptr->key) {
		Delete(ptr->rightChild, oldkey);
	}
	else {
		if (!ptr->leftChild && !ptr->rightChild) {
			delete ptr; ptr = 0; return;
		}
		else if (ptr->leftChild && !ptr->rightChild) {
			tmpptr = ptr;
			ptr = ptr->leftChild;
			delete tmpptr;
			return;
		}
		else if (!ptr->leftChild && ptr->rightChild) {
			tmpptr = ptr;
			ptr = ptr->rightChild;
			delete tmpptr;
			return;
		}
		else {
			Node<K, E>* rc = ptr->rightChild;
			if (!rc->leftChild) {
				ptr->key = rc->key;
				ptr->element = rc->element;
				ptr->rightChild = rc->rightChild;
				delete rc;
				return;
			}
			else {
				while (1) {
					if (rc->leftChild) {
						tmpdaddyptr = rc;
						rc = rc->leftChild;
					}
					else
						break;
				}
				ptr->key = rc->key;
				ptr->element = rc->element;
				tmpdaddyptr->leftChild = rc->rightChild;
				delete rc;
				return;
			}
		}
	}
}


template<class K, class E>
void BST<K, E>::ThreeWayJoin(BST<K, E>& small, K midkey, E midel, BST<K, E>& big) {
	root = new Node<K, E>(midkey, midel, small.root, big.root);
	small.root = big.root = 0;
}

template<class K, class E>
void BST<K, E>::TwoWayJoin(BST<K, E>& small, BST<K, E>& big) {
	if (!small.root) { root = big.root; big.root = 0; return; }
	if (!big.root) { root = small.root; small.root = 0; return; }
	BST small2 = small;
	Node<K, E>* ptr = small2.root;
	Node<K, E>* pptr = ptr;

	while (1) {
		if (ptr->rightChild!=0) {
			pptr = ptr;
			ptr = ptr->rightChild;
		}
		else {
			break;
		}
	}
	K midkey = ptr->key;
	E midel = ptr->element;
	Delete(small2.root, midkey);
	ThreeWayJoin(small2, midkey, midel, big);
	small.root = small2.root = big.root = 0;
	
	//if (ptr == pptr) {
	//	ptr->rightChild = big.root;
	//	root = small2.root;
	//	small2.root = 0;
	//	big.root = 0;
	//}
	//else if (ptr->leftChild == 0) {
	//	pptr->rightChild = 0;
	//	Delete(midkey);
	//	ThreeWayJoin(small2, midkey, midel, big);

	//}
	//else{
	//	pptr->rightChild = ptr->leftChild;
	//	Delete(midkey);
	//	ThreeWayJoin(small2, midkey, midel, big);
	//}
}

#endif