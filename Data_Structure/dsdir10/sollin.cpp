//B590011,3학년,김명호
#include <fstream>
#include <queue>
#include "mstree.h"
int NNODES;

priority_queue<Edge, vector<Edge>, Compare>* PQ;//all v has pq, so we need pointer

void MoveIntoPQ_EdgesOfNode(int v1, int v2)      // Move all edges of vertex 'v2' in the PQ[v2] into PQ[v1]
{
	while (!PQ[v2].empty())
	{
		Edge e = PQ[v2].top();
		PQ[v2].pop();
		PQ[v1].push(e);
	}
}

void sollin() {
	Sets sets(NNODES);
	int nedges = 0;
	while (nedges < NNODES - 1) {
		for (int i = 0; i < NNODES; i++) {//all node empty test

			Edge e = PQ[i].top();
			PQ[i].pop();
			int root0;
			int v1root = sets.Find(e.v1);
			int v2root = sets.Find(e.v2);
			if (v1root != v2root)                     // cycle이 아니면
			{
				sets.Union(v1root, v2root);
				root0=sets.Find(v1root);
				nedges++;
				cout << e;
			}
			else {
				continue;
			}
			if (root0 != v1root) {
				MoveIntoPQ_EdgesOfNode(root0, v1root);
			}
			else {
				MoveIntoPQ_EdgesOfNode(root0, v2root);
			}
		}

	}
}




void ReadEdges4sollin(istream& is) {
	PQ = new priority_queue<Edge, vector<Edge>, Compare>[NNODES];
	Edge e;
	while (GetEdge(is, NNODES, e)) {
		PQ[e.v1].push(e);
		PQ[e.v2].push(e);
	}
}

int main(int argc, char* argv[]) {
	ifstream is;
	if (argc == 1)is.open("mstree.dat");
	else is.open(argv[1]);
	if (!is) { cerr << "No such input file\n"; return 1; }
	is >> NNODES;
	if (NNODES < 2) { cerr << "#nodes must be 2.." << endl; return 1; }

	try { ReadEdges4sollin(is); sollin(); }
	catch (char const* str)
	{
		cerr << "Exception: " << str << endl;
		return 1;
	}
}
