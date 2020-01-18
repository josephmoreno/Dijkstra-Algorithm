//===================================================================================
// Written by Joseph Daniel Moreno
//
// Compiled using MinGW.
// Compilation command used: g++ -std=gnu++17 -Wall dijkstra_alg.cpp -o dijkstra_alg
// ==================================================================================

#include <iostream>
#include <vector>
#include <time.h>
#include <string>

struct Vertex {
	unsigned int id;
	unsigned int edges;
	int dist;
	Vertex *adj;

	Vertex(unsigned int id_num) { id = id_num; dist = -1; edges = 0; adj = nullptr; }
	Vertex(unsigned int id_num, int dist) { id = id_num; this->dist = dist; edges = 0; adj = nullptr; }
};

class AdjList {
   private:
	unsigned int total_v;
	unsigned int edge_max;
	std::vector<Vertex *> adjList;
   public:
	// Constructors
	AdjList();
	AdjList(unsigned int total_v);

	// Adjacency List Functions
	void showAL();
	std::vector<Vertex *> getList() { return adjList; }
	unsigned int getTotalV() { return total_v; }

	// Dijkstra's Algorithm
	int DA_adjList(unsigned int id0, unsigned int id1);
	void showDAList(unsigned int id);

	// Destructor
	~AdjList();
};
