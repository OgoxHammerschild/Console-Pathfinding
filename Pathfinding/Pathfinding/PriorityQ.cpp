// (c) Daniel Bortfeld 2018
#include "PriorityQ.h"

auto PriorityQ::Find(Node * node)
{
	for (auto iter = c.begin(); iter != c.end(); ++iter)
	{
		if (&*iter == node)
		{
			return iter;
		}
	}
	return c.end();
}

void PriorityQ::Reinsert(Node * node)
{
	auto iter = Find(node);
	if (iter != c.end())
	{
		c.erase(iter);
		push(*node);
	}
}
