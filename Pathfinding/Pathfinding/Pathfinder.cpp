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
		current->Color = Color::Red;

		current->IsOnOpen = false;
		closedList.push_back(current);

		if (current == goal)
		{
			while (current != nullptr && current != start)
			{
				current->Color = Color::IntenseRed + Color::PinkBackground;
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

				if (toNode->IsOnOpen || !toNode->IsWalkable)
				{
					continue;
				}

				if (std::find(closedList.begin(), closedList.end(), toNode) != closedList.end())
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
		current->Color = Color::Red;

		current->IsOnOpen = false;
		closedList.push_back(current);

		if (current == goal)
		{
			while (current != nullptr && current != start)
			{
				current->Color = Color::IntenseRed + Color::PinkBackground;
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

				if (toNode->IsOnOpen || !toNode->IsWalkable)
				{
					continue;
				}

				if (std::find(closedList.begin(), closedList.end(), toNode) != closedList.end())
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
		current->Color = Color::Red;

		current->IsOnOpen = false;
		closedList.push_back(current);

		if (current == goal)
		{
			while (current != nullptr && current != start)
			{
				current->Color = Color::IntenseRed + Color::PinkBackground;
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

				float realCost = current->RealCost + ((current->X == toNode->X || current->Y == toNode->Y) ? toNode->Cost : toNode->Cost + 0.4f); // with diagonal penalty

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

bool Pathfinder::AStar(std::vector<std::vector<Node*>>& graph, Node * start, Node * goal)
{
	PriorityQ openList;
	std::vector<Node*> closedList;

	openList.push(*start);

	while (!openList.empty())
	{
		Node temp = openList.top();
		Node* current = graph[temp.X][temp.Y];
		openList.pop();
		current->Color = Color::Red;

		current->IsOnOpen = false;
		closedList.push_back(current);

		if (current == goal)
		{
			while (current != nullptr && current != start)
			{
				current->Color = Color::IntenseRed + Color::PinkBackground;
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

				float realCost = current->RealCost + ((current->X == toNode->X || current->Y == toNode->Y) ? toNode->Cost : toNode->Cost + 0.4f); // with diagonal penalty
				//float realCost = current->RealCost + toNode->Cost; // without diagonal penalty
				float heuristic = sqrtf(abs((goal->X - toNode->X)*(goal->X - toNode->X) + (goal->Y - toNode->Y)*(goal->Y - toNode->Y))); // euclidean
				//float heuristic = (goal->X - toNode->X) + (goal->Y - toNode->Y); //manhatten

				if (toNode->IsOnOpen)
				{
					if (realCost < toNode->RealCost)
					{
						toNode->RealCost = realCost;
						toNode->Heuristic = heuristic;
						toNode->Parent = current;
						openList.Reinsert(toNode);
					}
					continue;
				}

				toNode->Parent = current;
				toNode->IsOnOpen = true;
				toNode->RealCost = realCost;
				toNode->Heuristic = heuristic;
				toNode->SortType = SortBy::Estimate;

				openList.push(*toNode);
			}
		}
	}

	return false;
}
