[Back to Main Page](https://ogoxhammerschild.github.io/)    

# Pathfinding demonstrated in the Console
***   

## Content



***   



# A*   
This console application demonstrates the pathfinding algorithms BreadthFirst, BestFirst, Dijkstra and A\*. The picture below shows the result for a path searched with A\*. The green point represents the start of the path, the red point is the goal. The path itself is colored pink/purple. Grey numbers have been taken from the open list and have been investigated for a path. White numbers have not been investigated. The numbers represent both the nodes and the cost of traversing the node. Black points can not be traversed.

![astar](https://raw.githubusercontent.com/OgoxHammerschild/Console-Pathfinding/master/docs/images/AStar.PNG)   

## Code   
### Prerequisites   
In order to perform the pathfinding algorithm some prerequisites are necessary. First, you need a graph with interconnected nodes. The nodes can be connected via edges. In my case I chose not to use edges but to consider all neighboring nodes to be connected with the node I'm currently looking at.   
Furthermore, I'm using a priority queue as the open list.

#### Nodes
The Nodes contain information about their position and coloration in the grid, whether they are walkable and how much it costs to walk on them. During the A\* algorithm further information is needed about the parent node, the real, heuristic and estimated cost, whether the node is on the open list and what the open list should sort the node by.

```c++
// Node.h
//...

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
	inline float EstimateCost() const { return RealCost + Heuristic; }

	bool IsOnOpen = false;

	SortBy SortType = SortBy::Estimate;

  // ...
```   
The priority queue (open list) will sort the nodes inside it using the greater > operator so that the node with the lowest cost will end up at the front/top of the list.   

```c++
// Node.cpp

bool Node::operator>(Node const & other) const
{
	switch (SortType)
	{
	case SortBy::RealCost:
		return RealCost > other.RealCost;
	case SortBy::Heuristic:
		return Heuristic > other.Heuristic;
	case SortBy::Estimate:
		return EstimateCost() > other.EstimateCost();
	default:
		return Cost > other.Cost;
	}
}
```   
#### Priority Queue
I'm using the `std::priority_queue` with two additions for my pathfinding. Because you cannot find and remove elements in/from the `std::priority_queue`, I have added two functions to facilitate this functionality for the purpose of pathfinding.   

```c++
// PriorityQ.h
//...

class PriorityQ : public std::priority_queue<Node, std::vector<Node>, std::greater<Node>>
{
public:

	auto Find(Node* node);

	void Reinsert(Node* node); // remove the 'node' from the queue and push it back in in order to resort the queue
};
```   
### A\*-Algorithm
