#ifndef PRIORITYQ_H
#define PRIORITYQ_H

#include <queue>
#include <functional>
#include "Node.h"

class PriorityQ : public std::priority_queue<Node, std::vector<Node>, std::greater<Node>>
{
public:

	auto Find(Node* node);

	void Reinsert(Node* node);
};

#endif // !PRIORITYQ_H
