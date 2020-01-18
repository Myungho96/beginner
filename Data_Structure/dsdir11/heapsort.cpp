//B590011,3학년,김명호
#include<iostream>
using namespace std;

template <class T>
void PrintArray(T* a, const int n) {
	for (int i = 1; i <= n; i++)
		cout << a[i] << " ";
	cout << endl;
}

template <class T>
void Adjust(T* a, const int root, const int n) {
	T e = a[root];

	int j;

	for (j = 2 * root; j <= n; j *= 2) {
		if (j < n && a[j] < a[j + 1])
			j++;
		if (e >= a[j])
			break;
		a[j / 2] = a[j];
	}
	a[j / 2] = e;
}

template <class T>
void HeapSort(T* a, const int n) {
	for (int i = n / 2; i >= 1; i--) {
		Adjust(a, i, n);
	}
	for (int i = n - 1; i >= 1; i--) {
		swap(a[1], a[i + 1]);
		Adjust(a, 1, i);
		PrintArray(a, i);
	}
}

int main() {
	int a[] = { 0,26,5,77,1,61,11,59,15,48,19 };
	int n = sizeof(a) / sizeof(int) - 1;//except 0

	cout << "Before Sorting : "; PrintArray(a, n);
	HeapSort(a, n);
	cout << "After Sorting : "; PrintArray(a, n);
}
