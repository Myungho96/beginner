//B590011,3학년,김명호
#include<iostream>
using namespace std;

template <class T>
class Maxheap {
public:
	Maxheap(int a=10);//constructor
	void Push(const T& e);
	void Pop();
	bool IsEmpty() { return heapSize == 0; }
	T Top() {
		if (IsEmpty()) {
			cout << "heap is empty.";
			return -1;
		}
		return heap[1];}
private:
	int heapSize;//elements in heap
	int capacity;//size of array heap
	T* heap;//element array
	template <class T2>
	friend ostream& operator<<(ostream&, Maxheap<T2>&);

};

template <class T>
void ChangeSizeID(T*& a, const int oldSize, const int newSize) {//2*capacity+1
	T* temp = new T[newSize];
	copy(a, a + oldSize, temp);
	delete[]a;
	a = temp;
}

template <class T>
ostream& operator<<(ostream& os, Maxheap<T>& H) {
	os << "<Heap Contents> ";
	for (int i = 1; i <= H.heapSize; i++)
		os << i << ":" << H.heap[i] << " ";
	os << endl;
	return os;
}

template <class T>
Maxheap<T>::Maxheap(int theCapacity) :heapSize(0) {
	if (theCapacity < 1)throw "Must be +ve";
	capacity = theCapacity;
	heap = new T[capacity + 1];
}

template <class T>
void Maxheap<T>::Push(const T& e){//Insert e
	if (heapSize == capacity) {
		ChangeSizeID(heap, capacity + 1, 2 * capacity + 1); 
		capacity *= 2;
	}
	int currentNode = ++heapSize;//what position of heapsize?
	while (currentNode != 1 && heap[currentNode / 2] < e)
	{
		heap[currentNode] = heap[currentNode / 2]; // move parent node
		currentNode /= 2;
	}
	heap[currentNode] = e;
}

template <class T>
void Maxheap<T>::Pop(){
	if (IsEmpty()) throw "Heap is empty.Cannot delete.";
	heap[1].~T();
	T lastE = heap[heapSize--];//remove

	int currentNode = 1; //root
	int child = 2;//child
	while (child <= heapSize)//if exist child
	{ 
		if (child < heapSize && heap[child] < heap[child + 1]) child++;
		if (lastE >= heap[child]) break;

		heap[currentNode] = heap[child];
		currentNode = child; child *= 2;
	}
	heap[currentNode] = lastE;
}
