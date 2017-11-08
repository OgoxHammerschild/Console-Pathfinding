#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <vector>
#include "Node.h"

class Pathfinder
{
public:

	static int TotalPathCost;

public:

	Pathfinder();
	~Pathfinder();

	static bool BreadthFirst(std::vector<std::vector<Node*>>& graph, Node* start, Node* goal);
	
	static bool BestFirst(std::vector<std::vector<Node*>>& graph, Node* start, Node* goal);
	
	static bool Dijkstra(std::vector<std::vector<Node*>>& graph, Node* start, Node* goal);
	
	static bool AStar(std::vector<std::vector<Node*>>& graph, Node* start, Node* goal);
};

#endif // !PATHFINDER_H
