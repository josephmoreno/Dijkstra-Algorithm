# dijkstra_alg
Uses a variant of Dijkstra's Algorithm to calculate the shortest path between a starting vertex and all other vertices in the graph.

- Each vertex has a unique ID.
- Graph is represented by an adjacency list; distance is stored in the adjacent vertices.
- Program starts by creating a random graph with some parameters set by the user, then calculates the shortest distances.
- After the random graph, the user then has a choice to try calculating the shortest distances on a manually created graph or terminate the program.

Compiled using MinGW. Compilation command used: g++ -std=gnu++17 -Wall dijkstra_alg.cpp -o dijkstra_alg
