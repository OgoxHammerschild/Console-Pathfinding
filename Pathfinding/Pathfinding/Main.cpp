// (c) Daniel Bortfeld 2018
#include "Node.h"
#include "Pathfinder.h"

#include <vector>
#include <time.h>
#include <chrono>
#include <ctime>
#include <iostream>
#include <Windows.h>

int main()
{
	std::cout << "[1] BreadthFirst, [2] BestFirst, [3] Dijkstra, [4] A*" << std::endl;

	int algorithm;

	std::cin >> algorithm;

	int width = 30;
	int height = 25;

	std::vector<std::vector<Node*>> map;

	map.resize(width);

	//srand(time(NULL));
	srand(1337);

	for (int x = 0; x < width; x++)
	{
		map[x].resize(height);
		for (int y = 0; y < height; y++)
		{
			if (x == width / 2 && y > 2 && y < height - 3 && y != height / 2)
			{
				map[x][y] = new Node(x, y, 10, false);
				map[x][y]->Color = Color::Black;
			}
			else
			{
				int cost = rand() % 3 + 6;

				map[x][y] = new Node(x, y, cost, true);
			}
		}
	}

	// stopwatch start 
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	// ~stopwatch start 

	switch (algorithm)
	{
	case 1:
		Pathfinder::BreadthFirst(map, map[1][1], map[width - 2][height - 2]);
		break;
	case 2:
		Pathfinder::BestFirst(map, map[1][1], map[width - 2][height - 2]);
		break;
	case 3:
		Pathfinder::Dijkstra(map, map[1][1], map[width - 2][height - 2]);
		break;
	case 4:
		Pathfinder::AStar(map, map[1][1], map[width - 2][height - 2]);
		break;
	default:
		return 1;
	}

	// stopwatch end 
	end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;

	std::cout << "elapsed search time: " << elapsed_seconds.count() << "s\n";
	// ~stopwatch end 

	map[1][1]->Color = Color::IntenseGreen + Color::GreenBackground;
	map[width - 2][height - 2]->Color = Color::IntenseRed + Color::RedBackground;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), map[x][y]->Color);

			if (map[x][y]->IsWalkable)
			{
				std::cout << map[x][y]->Cost;
			}
			else
			{
				std::cout << '#';
			}
		}
		std::cout << std::endl;
	}

	std::cout << std::endl << "Total Cost of Path (excluding Start): " << Pathfinder::TotalPathCost << " (without diagonal penalty)\n\n";

	system("pause");

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			delete map[x][y];
		}
	}

	return 0;
}