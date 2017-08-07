#ifndef NODE_H
#define NODE_H

#include "Colors.h"

enum SortBy
{
	RealCost,
	Heuristic,
	Estimate
};

class Node
{
public:

	int X;
	int Y;
	
	bool IsWalkable;

	int Cost;
	char Color = Color::IntenseWhite;

	Node* Parent;

	float RealCost;
	float Heuristic;
	float HeuristicWeight = 4.5f;
	inline float EstimateCost() const { return RealCost + Heuristic * HeuristicWeight; }

	bool IsOnOpen = false;

	SortBy SortType = SortBy::Estimate;

public:

	Node() {}

	Node(int x, int y, int cost, bool walkable) : X(x), Y(y), Cost(cost), IsWalkable(walkable) {}

	~Node() {}

	bool operator> (Node const& other)const;
};

#endif // !NODE_H
