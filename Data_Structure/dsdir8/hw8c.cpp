//B590011,3학년,김명호
#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct Student {
	Student(string n, int m, int e):name(n),math(m),english(e){}
	string name;
	int math;
	int english;
};
struct cmp {
	bool operator()(const Student s1, const Student s2) {
		return s1.math + s1.english > s2.math + s2.english;
	}
};

int main() {
	priority_queue < Student, vector<Student>, cmp> minPQ;
	minPQ.push(Student("kim", 70, 85));
	minPQ.push(Student("lee", 70, 40));
	minPQ.push(Student("byun", 90, 90));
	minPQ.push(Student("wu", 40, 40));
	minPQ.push(Student("jung", 59, 59));
	minPQ.push(Student("hong", 45, 49));

	while (!minPQ.empty()) {
		cout << minPQ.top().name << " "; minPQ.pop();
	}
	cout << endl;
}
