#ifndef A_STAR_H
#define A_STAR_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "node.hpp"

#define barrier 1

class A_star
{
public:
	A_star(std::vector<std::vector<int>>* map, vec2 start, vec2 target);
	~A_star();

	bool iteration();
	bool isPathFound() { return pathFound; }

	std::vector<vec2> getPath();

	auto getopenList() { return openList; }
	auto getclosedList() { return closedList; }

private:
	bool listCheck(int x, int y);
	bool inMap(int x, int y);

private:
	std::vector<Node> openList;
	std::vector<Node*> closedList;

	Node start;
	vec2 target;
	std::vector<std::vector<int>>* map;

	bool pathFound;

	Node* best;
};


#endif