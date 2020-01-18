//B590011,3학년,김명호
#include"mstree.h"
Sets::Sets(int numberOfElements) {
	if (numberOfElements < 2)throw"2개 이상이어야 함.";
	n = numberOfElements;
	parent = new int[n];
	fill(parent, parent + n, -1);
}

void Sets::Union(int i, int j) { parent[i] = j; }

int Sets::Find(int i) {
	while (parent[i] >= 0)
		i = parent[i];
	return i;
}//Assume two vertices in any edge are always in ascending order

bool Edge::operator==(Edge& e2) { return(v1 == e2.v1 && v2 == e2.v2); }
bool Edge::operator!=(Edge& e2) { return(v1 != e2.v1 || v2 != e2.v2); }

ostream& operator<<(ostream& os, Edge& e) {
	os << "(" << e.v1 << "," << e.v2 << ") : " << e.weight << endl;
	return os;
}

bool GetEdge(istream& is, const int numnodes, Edge& e) {
	//make sure that node number is 0 to NNODES-1
	is >> e.v1 >> e.v2 >> e.weight;
	if (!is.good())
		return false;
	if (e.v1 < 0 || e.v1 >= numnodes || e.v2 < 0 || e.v2 >= numnodes || e.v1 == e.v2)
		throw "Incorrect Edge";
	if (e.v2 < e.v1)
		swap(e.v1, e.v2);//low-numbered vertex first.
	return true;
}
