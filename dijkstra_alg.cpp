//==================================================================================
// Written by Joseph Daniel Moreno
//
// Compiled using MinGW.
// Compilation command used: g++ -std=gnu++17 -Wall dijkstra_alg.cpp -o dijkstra_alg
// =================================================================================

#include "dijkstra_alg.hpp"

unsigned int TOTAL_V;		// # of vertices in the randomly created graph.
unsigned int EDGE_MAX = 4;	// Max # of edges for each vertex.

void cinFlush() { std::cin.clear(); std::cin.ignore(INT_MAX, '\n'); }

int main() {

	srand(time(0));

	std::cout << "\nEnter the number of vertices for the graph (5 through 20): ";
	std::cin >> TOTAL_V;
	while(TOTAL_V < 5 || TOTAL_V > 20) {
		std::cout << "Invalid number. Must be greater than 4 and less than 21. Enter another: ";
		cinFlush();
		std::cin >> TOTAL_V;
	}	

	//std::cout << "\nEnter the max number of edges allowed for each vertex (2 through 4): ";
	cinFlush();
	/*std::cin >> EDGE_MAX;
	while(EDGE_MAX < 2 || EDGE_MAX > 4) {
		std::cout << "Invalid number. Must be greater than 1 and less than 5. Enter another: ";
		cinFlush();
		std::cin >> EDGE_MAX;
	}
	cinFlush();*/

	AdjList AL_0;
	AL_0.showAL();

	unsigned int s_id, f_id;	// s_id = start, f_id = finish
	std::cout << "\n\nEnter a vertex ID as a starting point: ";
	std::cin >> s_id;
	cinFlush();

	while(s_id < 0 || s_id >= AL_0.getTotalV()) {
		std::cout << "Invalid vertex ID. Must be within the range of 0 through " << AL_0.getTotalV() - 1 << ".\n";
		std::cout << "Enter a vertex ID as a starting point: ";
		std::cin >> s_id;
		cinFlush();
	}

	std::cout << "Enter a vertex ID as the finishing point: ";
	std::cin >> f_id;
	cinFlush();

	while(f_id < 0 || f_id >= AL_0.getTotalV()) {
		std::cout << "Invalid vertex ID. Must be within the range of 0 through " << AL_0.getTotalV() - 1 << ".\n";
		std::cout << "Enter a vertex ID as the finishing point: ";
		std::cin >> f_id;
		cinFlush();
	}

	if (AL_0.DA_adjList(s_id, f_id) != -1) {
		std::cout << "\nThe shortest distance between vertex " << s_id << " and vertex " << f_id << " is " << AL_0.DA_adjList(s_id, f_id) << ".\n";
		AL_0.showDAList(s_id);
	}else
		std::cout << "There is no path between vertex " << s_id << " and vertex " << f_id << ".\n";

	unsigned int choice;

	std::cout << "\nWould you like to manually create a graph and calculate the shortest paths from a starting vertex?\n";
	std::cout << "(1) Yes.\n";
	std::cout << "(2) No. Exit the program.\n";
	std::cout << "\nEnter the number of your choice: ";
	std::cin >> choice;
	cinFlush();

	while(choice != 1 && choice != 2) {
		std::cout << "\nInvalid choice. Please try again; would you like to manually create a graph and calculate the shortest paths from a starting vertex?\n";
		std::cout << "(1) Yes.\n";
		std::cout << "(2) No. Exit the program.\n";
		std::cout << "\nEnter the number of your choice: ";
		std::cin >> choice;
		cinFlush();
	}

	if (choice == 2) {
		std::cout << "\n\nGoodbye.\n";
		return(0);
	}else if (choice == 1) {
		std::cout << "\nEnter the number of vertices you want in the graph: ";
		std::cin >> TOTAL_V;
		cinFlush();

		AdjList AL_1(TOTAL_V);
		AL_1.showAL();

		std::cout << "\n\nEnter a vertex ID as the starting point: ";
		std::cin >> s_id;
		cinFlush();

		while(s_id < 0 || s_id >= AL_1.getTotalV()) {
			std::cout << "Invalid vertex ID. Must be within the range of 0 through " << AL_1.getTotalV() - 1 << ".\n";
			std::cout << "Enter a vertex ID as the starting point: ";
			std::cin >> s_id;
			cinFlush();
		}

		std::cout << "Enter a vertex ID as the finishing point: ";
		std::cin >> f_id;
		cinFlush();

		while(f_id < 0 || f_id >= AL_1.getTotalV()) {
			std::cout << "Invalid vertex ID. Must be within the range of 0 through " << AL_1.getTotalV() - 1 << ".\n";
			std::cout << "Enter a vertex ID as the finishing point: ";
			std::cin >> f_id;
			cinFlush();
		}

		AL_1.DA_adjList(s_id, f_id);
		AL_1.showDAList(s_id);
	}

	return(0);

}

AdjList::AdjList() {
	std::cout << "\nCreating a random graph...\n";

	unsigned int edge_num;	// # of edges for the vertex.
	unsigned int adj_id;	// The adjacency's ID.
	unsigned int d;		// Distance of the adjacency from the vertex.
	unsigned int i, j, dif;
	Vertex *cur = nullptr, *temp = nullptr;

	total_v = TOTAL_V;
	edge_max = EDGE_MAX;
	adjList.resize(total_v);

	// Initialize the list with new vertices.
	for(i = 0; i < total_v; ++i) {
		adjList[i] = new Vertex(i);
	}

	// Used to keep track of which edges exist already.
	// (Only 1 edge per pair of vertices.)
	std::vector<bool> adjacent(total_v);

	// Give each vertex in the list a random number of adjacencies.
	for(i = 0; i < total_v; ++i) {
		for(j = 0; j < total_v; ++j) adjacent[j] = false;
		adjacent[i] = true;

		edge_num = rand() % (edge_max + 1);
		if (edge_num == 0) edge_num = 1;

		if (adjList[i]->edges >= edge_num) continue;

		dif = edge_num - adjList[i]->edges;
		adjList[i]->edges = edge_num;
		cur = adjList[i];

		while(cur->adj != nullptr) {
			cur = cur->adj;
			adjacent[cur->id] = true;
		}

		// Get random adjacency IDs for the vertex.
		for(j = 0; j < dif; ++j) {
			adj_id = rand() % total_v;
			if (adjacent[adj_id] == true || adjList[adj_id]->edges >= edge_max) adj_id = 0;
			while (adjacent[adj_id] == true || adjList[adj_id]->edges >= edge_max) ++adj_id;
			adjacent[adj_id] = true;
			
			d = rand() % 11;	// Max distance is 10.
			if (d == 0) d = 1;

			cur->adj = new Vertex(adj_id);
			cur->adj->dist = d;
			cur = cur->adj;

			temp = adjList[adj_id];
			while(temp->adj != nullptr) temp = temp->adj;
			temp->adj = new Vertex(i);
			temp->adj->dist = d;
			adjList[adj_id]->edges++;
		}
	}

	cur = nullptr;
	temp = nullptr;
}

AdjList::AdjList(unsigned int total_v) {
	unsigned int i, j;
	unsigned int edge_num, adj_id, dif;
	int d;
	std::vector<bool> adjacent(total_v);
	Vertex *cur = nullptr, *temp = nullptr;

	this->total_v = total_v;
	adjList.resize(total_v);
	for(i = 0; i < total_v; ++i) adjList[i] = new Vertex(i);

	std::cout << "\nOnly 1 edge allowed per pair of vertices and each vertex must have at least 1 edge.";
	for(i = 0; i < total_v; ++i) {
		for(j = 0; j < total_v; ++j) adjacent[j] = false;
		adjacent[i] = true;
		cur = adjList[i];
		
		while(cur->adj != nullptr) {
			cur = cur->adj;
			adjacent[cur->id] = true;
		}


		std::cout << "\n\nVertex " << i << " currently has " << adjList[i]->edges << " edge(s). Enter a higher number if vertex " << i << " should have more. Else, enter its current # of edges: ";
		std::cin >> edge_num;
		cinFlush();

		if (edge_num == adjList[i]->edges && edge_num > 0) continue;

		while(edge_num >= total_v || edge_num < 1 || edge_num < adjList[i]->edges) {
			std::cout << "\nInvalid # of edges; must be less than the number of vertices in the graph, greater than 0, and greater than or equal to its current number of edges.\n";
			std::cout << "Vertex " << i << " currently has " << adjList[i]->edges << " edge(s). Enter a higher number if vertex " << i << " should have more. Else, enter its current # of edges: ";
			std::cin >> edge_num;
			cinFlush();
		}

		dif = edge_num - adjList[i]->edges;
		adjList[i]->edges = edge_num;
		for(j = 0; j < dif; ++j) {
			std::cout << "\nEnter the ID of vertex " << i << "'s adjacency: ";
			std::cin >> adj_id;
			cinFlush();

			while(adjacent[adj_id] == true
			      || adj_id < 0 || adj_id >= total_v) {
				std::cout << "\nInvalid adjacent vertex ID. Only 1 edge per pair of vertices and the ID must be within the range of 0 through " << total_v - 1 << ".\n";
				std::cout << "Enter the ID of vertex " << i << "'s adjacency: ";
				std::cin >> adj_id;
				cinFlush();
			}

			std::cout << "Enter the distance between vertex " << i << " and " << adj_id << ": ";
			std::cin >> d;
			cinFlush();

			while(d <= 0) {
				std::cout << "\nInvalid distance. Must be greater than 0.\n";
				std::cout << "Enter the distance between vertex " << i << " and " << adj_id << ": ";
				std::cin >> d;
				cinFlush();
			}

			cur->adj = new Vertex(adj_id, d);
			adjacent[adj_id] = true;
			cur = cur->adj;

			temp = adjList[adj_id];
			while(temp->adj != nullptr) temp = temp->adj;
			temp->adj = new Vertex(i, d);
			adjList[adj_id]->edges++;
		}
	}

	cur = nullptr; temp = nullptr;
}

void AdjList::showAL() {
	unsigned int i;
	Vertex *cur = nullptr;

	std::cout << "Here is the adjacency list:\n";
	std::cout << "FORMAT: | Vertex ID, # of Edges |->(Adj. ID, Dist.)->(Adj. ID, Dist.)->...\n";
	for(i = 0; i < total_v; ++i) {
		std::cout << "\n| " << i << ", " << adjList[i]->edges << " |";
		cur = adjList[i]->adj;

		while(cur != nullptr) {
			std::cout << "->(" << cur->id << ", " << cur->dist << ")";
			cur = cur->adj;
		}
	}

	return;
}

int AdjList::DA_adjList(unsigned int id0, unsigned int id1) {
	std::vector<unsigned int> IDs;
	std::vector<bool> visited(total_v, false);
	unsigned int i, cur_id;
	int d;
	Vertex *cur_adj;

	for(i = 0; i < total_v; ++i) adjList[i]->dist = -1;
	adjList[id0]->dist = 0; IDs.push_back(id0);

	while(!IDs.empty()) {
		cur_id = IDs.back(); IDs.pop_back();
		cur_adj = adjList[cur_id]->adj;

		while(cur_adj != nullptr) {
			if (visited[cur_adj->id] == false)
				IDs.push_back(cur_adj->id);

			d = adjList[cur_id]->dist + cur_adj->dist;
			if (adjList[cur_adj->id]->dist == -1 || d < adjList[cur_adj->id]->dist)
				adjList[cur_adj->id]->dist = d;

			cur_adj = cur_adj->adj;
		}

		visited[cur_id] = true;
	}

	return adjList[id1]->dist;
}

void AdjList::showDAList(unsigned int id) {
	std::cout << "\nHere are the shortest paths from vertex " << id << " to every other vertex:\n";
	std::cout << "FORMAT: | Vertex ID, Minimum Distance from Vertex " << id << " |\n\n";

	for(unsigned int i = 0; i < total_v; ++i) {
		if (adjList[i]->dist != -1)
			std::cout << "| " << adjList[i]->id << ", " << adjList[i]->dist << " |\n";
		else
			std::cout << "| " << adjList[i]->id << ", Unreachable |\n";
	}

	return;
}

AdjList::~AdjList() {
	unsigned int i;
	Vertex *cur = nullptr, *prev = nullptr;
	
	for(i = 0; i < total_v; ++i) {
		cur = adjList[i]->adj;
		delete adjList[i];
		adjList[i] = nullptr;

		while(cur != nullptr) {
			prev = cur;
			cur = cur->adj;
			delete prev;
			prev = nullptr;
		}
	}

	prev = nullptr; cur = nullptr;
}
