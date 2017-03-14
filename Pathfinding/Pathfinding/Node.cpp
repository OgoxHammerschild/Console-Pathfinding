#include "Node.h"

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
