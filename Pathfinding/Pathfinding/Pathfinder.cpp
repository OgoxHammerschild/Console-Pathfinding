#include "Pathfinder.h"
#include "PriorityQ.h"
#include "Colors.h"

bool Pathfinder::BreadthFirst(std::vector<std::vector<Node*>>& graph, Node * start, Node * goal)
{
	std::queue<Node*> openList;
	std::vector<Node*> closedList;

	openList.push(start);

	while (!openList.empty())
	{
		Node* current = openList.front();
		openList.pop();
		current->Color = Color::Grey;
		closedList.push_back(current);

		if (current == goal)
		{
			while (current != nullptr && current != start)
			{
				current->Color = Color::IntensePink + Color::PinkBackground;
				current = current->Parent;
			}

			return true;
		}

		for (int x = -1; x < 2; x++)
		{
			for (int y = -1; y < 2; y++)
			{
				if (x == 0 && y == 0)
				{
					continue;
				}

				int X = current->X + x;
				int Y = current->Y + y;

				if (X < 0 || X > graph.size() - 1 || Y < 0 || Y > graph[0].size() - 1)
				{
					continue;
				}

				Node* toNode = graph[X][Y];

				if (!toNode->IsWalkable || toNode->IsOnOpen || std::find(closedList.begin(), closedList.end(), toNode) != closedList.end())
				{
					continue;
				}

				toNode->Parent = current;
				toNode->IsOnOpen = true;
				openList.push(toNode);
			}
		}
	}
	return false;
}

bool Pathfinder::BestFirst(std::vector<std::vector<Node*>>& graph, Node * start, Node * goal)
{
	PriorityQ openList;
	std::vector<Node*> closedList;

	openList.push(*start);

	while (!openList.empty())
	{
		Node temp = openList.top();
		Node* current = graph[temp.X][temp.Y];
		openList.pop();
		current->Color = Color::Grey;
		closedList.push_back(current);

		if (current == goal)
		{
			while (current != nullptr && current != start)
			{
				current->Color = Color::IntensePink + Color::PinkBackground;
				current = current->Parent;
			}

			return true;
		}

		for (int x = -1; x < 2; x++)
		{
			for (int y = -1; y < 2; y++)
			{
				if (x == 0 && y == 0)
				{
					continue;
				}

				int X = current->X + x;
				int Y = current->Y + y;

				if (X < 0 || X > graph.size() - 1 || Y < 0 || Y > graph[0].size() - 1)
				{
					continue;
				}

				Node* toNode = graph[X][Y];

				if (!toNode->IsWalkable || toNode->IsOnOpen || std::find(closedList.begin(), closedList.end(), toNode) != closedList.end())
				{
					continue;
				}

				toNode->Heuristic = sqrtf(abs((goal->X - toNode->X) *(goal->X - toNode->X) + (goal->Y - toNode->Y) * (goal->Y - toNode->Y)));
				toNode->Parent = current;
				toNode->SortType = SortBy::Heuristic;
				toNode->IsOnOpen = true;
				openList.push(*toNode);
			}
		}
	}

	return false;
}

bool Pathfinder::Dijkstra(std::vector<std::vector<Node*>>& graph, Node * start, Node * goal)
{
	PriorityQ openList;
	std::vector<Node*> closedList;

	openList.push(*start);

	while (!openList.empty())
	{
		Node temp = openList.top();
		Node *current = graph[temp.X][temp.Y];
		openList.pop();
		current->Color = Color::Grey;
		closedList.push_back(current);

		if (current == goal)
		{
			while (current != nullptr && current != start)
			{
				current->Color = Color::IntensePink + Color::PinkBackground;
				current = current->Parent;
			}
			return true;
		}

		for (int x = -1; x < 2; x++)
		{
			for (int y = -1; y < 2; y++)
			{
				if (x == 0 && y == 0)
				{
					continue;
				}

				int X = current->X + x;
				int Y = current->Y + y;

				if (X < 0 || X > graph.size() - 1 || Y < 0 || Y > graph[0].size() - 1)
				{
					continue;
				}

				Node* toNode = graph[X][Y];

				if (!toNode->IsWalkable || std::find(closedList.begin(), closedList.end(), toNode) != closedList.end())
				{
					continue;
				}

				float realCost = current->RealCost + ((current->X == toNode->X || current->Y == toNode->Y) ? 1 : 1.4f);

				if (toNode->IsOnOpen)
				{
					if (realCost < toNode->RealCost)
					{
						toNode->RealCost = realCost;
						openList.Reinsert(toNode);
					}
					continue;
				}

				toNode->IsOnOpen = true;
				toNode->RealCost = realCost;
				toNode->Parent = current;
				toNode->SortType = SortBy::RealCost;
				openList.push(*toNode);
			}
		}
	}

	return false;
}

// the graph was prefilled and forwarded from the main(). the start and goal node are part of the graph.
bool Pathfinder::AStar(std::vector<std::vector<Node*>>& graph, Node * start, Node * goal)
{
	// the open list holds the nodes that have not been investigated by the algorithm
	PriorityQ openList;
	// the closed list holds the investigated nodes
	std::vector<Node*> closedList;

	// the start node initially gets pushed on the open list to be the first investigated node.
	// you could also start with the goal and look for the start, but I'm searching from start to goal
	openList.push(*start);

	// the search continues as long as there are uninvestigated nodes
	while (!openList.empty())
	{
		// the PriorityQ holds objects instead of pointers because the comparison function of the std::priority_queue 
		// can not compare the objects behind pointers. instead it would compare the memory adresses itself.
		// to make sure the node from the open list is the same as the one in the graph, the corresponding pointer is
		// taken from the graph. popped nodes become colored grey and pushed onto the closed list.
		Node temp = openList.top();
		Node* current = graph[temp.X][temp.Y];
		openList.pop();
		current->Color = Color::Grey;
		closedList.push_back(current);

		// if the last popped node is the goal
		if (current == goal)
		{
			// the path gets traced back through the parent connections untill we reach the start
			while (current != nullptr && current != start)
			{
				// nodes belonging to the path become colored pink
				current->Color = Color::IntensePink + Color::PinkBackground;
				current = current->Parent;
			}
			return true;
		}

		// if the goal has not been reached yet
		// all neighboring nodes of the current node are gathered for further investigation
		for (int x = -1; x < 2; x++)
		{
			for (int y = -1; y < 2; y++)
			{
				// don't consider yourself as a neighbor
				if (x == 0 && y == 0)
				{
					continue;
				}

				int X = current->X + x;
				int Y = current->Y + y;

				// make sure the index is still in range
				if (X < 0 || X > graph.size() - 1 || Y < 0 || Y > graph[0].size() - 1)
				{
					continue;
				}

				// the node you can reach from the current node (from = current, to = neighbor)
				Node* toNode = graph[X][Y];

				// don't consider unwalkable nodes and also
				// don't consider nodes that have been investigated already and ended up on the closed list
				if (!toNode->IsWalkable || std::find(closedList.begin(), closedList.end(), toNode) != closedList.end())
				{
					continue;
				}

				// calculate the actual cost for getting from the start to this node 
				// and the heuristic cost for getting from this node to the goal
				float realCost = current->RealCost + ((current->X == toNode->X || current->Y == toNode->Y) ? toNode->Cost : toNode->Cost + 0.4f); // with diagonal penalty
				//float realCost = current->RealCost + toNode->Cost; // without diagonal penalty
				float heuristic = sqrtf(abs((goal->X - current->X)*(goal->X - current->X) + (goal->Y - current->Y)*(goal->Y - current->Y))); // euclidean
				//float heuristic = (goal->X - toNode->X) + (goal->Y - toNode->Y); //manhattan

				// if the node is already on the open list
				if (toNode->IsOnOpen)
				{
					// and if the cost is smaller than last time we checked
					if (realCost < toNode->RealCost)
					{
						// update the node with the new infos
						toNode->RealCost = realCost;
						toNode->Heuristic = heuristic;
						toNode->Parent = current;
						openList.Reinsert(toNode);
					}
					continue;
				}

				// the node has not been touched before, so it gets filled with information
				toNode->Parent = current;
				toNode->IsOnOpen = true;
				toNode->RealCost = realCost;
				toNode->Heuristic = heuristic;
				// the sort type is set to estimate because this is what it's sorted by when using A*
				toNode->SortType = SortBy::Estimate;
				// the heuristic weight gives a higher or lower value to the heuristic cost. 
				// a weight of 4.5 allows better results than a weight of 1, if we are using
				// the currently randomly filled graph/map
				toNode->HeuristicWeight = 4.5f;

				// the node gets pushed to the open list for further investigations checking whether it's the goal 
				// or has any neighbors that might be the goal
				openList.push(*toNode);
			}
		}
	}

	// there is no path
	return false;
}
