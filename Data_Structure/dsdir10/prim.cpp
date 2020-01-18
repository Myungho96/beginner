//B590011,3학년,김명호
#include<fstream>
#include<queue>
#include"mstree.h"
int NNODES;

priority_queue<Edge, vector<Edge>, Compare> PQ;

queue<Edge>* Q;//data type: Edge!!!!!!

void MoveIntoPQ_EdgesOfNode(int v) {//v's edge move to pq.
	Edge temp;
	while (!Q[v].empty()) {
		temp = Q[v].front();
		PQ.push(temp);//push temp to the PQ
		Q[v].pop();
	}
	
}

void prim() {
	Sets sets(NNODES);
	int nedges = 0;
	while (nedges < NNODES - 1) {
		if (PQ.empty()) throw "No Spanning Tree Exists.";
		Edge e = PQ.top();
		PQ.pop();
		int root0 = sets.Find(0);//find 0's root
		//////////////////////////////////////////////////
		int v1root = sets.Find(e.v1);
		int v2root = sets.Find(e.v2);
		while (v1root == v2root) {
			e = PQ.top();
			PQ.pop();
			v1root = sets.Find(e.v1);
			v2root = sets.Find(e.v2);
		}
		sets.Union(v1root, v2root);
		if (v1root != root0) MoveIntoPQ_EdgesOfNode(v1root);
		else MoveIntoPQ_EdgesOfNode(v2root);
		nedges++;
		cout << e;
		////////////////////////////////////////////////////
	}
}

void ReadEdges4prim(istream& is) {
	Q = new queue<Edge>[NNODES];
	Edge e;

	while (GetEdge(is, NNODES, e)) {
		Q[e.v1].push(e);
		Q[e.v2].push(e);
	}
	MoveIntoPQ_EdgesOfNode(0);
}

int main(int argc, char* argv[]) {
	ifstream is;
	if (argc == 1)is.open("mstree.dat");
	else is.open(argv[1]);
	if (!is) { cerr << "No such input file\n"; return 1; }
	is >> NNODES;
	if (NNODES < 2) { cerr << "#nodes must be 2.." << endl; return 1; }

	try { ReadEdges4prim(is); prim(); }
	catch (char const* str)
	{
		cerr << "Exception: " << str << endl;
		return 1;
	}
}
