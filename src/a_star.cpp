#include "a_star/a_star.hpp"


A_star::A_star(std::vector<std::vector<int>>* map, vec2 start, vec2 target) :
	start(nullptr, target, start), target(target), map(map), pathFound(false)
{
	// First step: add start node to openList
	openList.push_back(this->start);
	best = nullptr;
}

A_star::~A_star() {
	for (auto it = closedList.begin(); it < closedList.end(); ++it) {
		delete *it;
	}
}

bool A_star::iteration() {

	if(openList.empty()) {
		std::cerr << "No Path found!" << std::endl;
		return false;
	}

	auto bestNode = std::min_element(openList.begin(), openList.end());

	best = new Node(*bestNode);
	openList.erase(bestNode);

	closedList.push_back(best);

	vec2 pos = vec2{best->getPosition().x, best->getPosition().y};
	(*map)[pos.x][pos.y] = 3;



	if(best->getPosition() == target) {

		std::cout << "Path found!" << std::endl;
		pathFound = true;
		return false;

	}else{
		//straight neighbours
		if(inMap(pos.x+1, pos.y) && (*map)[pos.x+1][pos.y] != barrier && !listCheck(pos.x+1, pos.y)) {
			openList.push_back(Node(best, target, vec2{pos.x+1, pos.y}));
		}

		if(inMap(pos.x-1, pos.y) && (*map)[pos.x-1][pos.y] != barrier && !listCheck(pos.x-1, pos.y)) {
			openList.push_back(Node(best, target, vec2{pos.x-1, pos.y}));
		}

		if(inMap(pos.x, pos.y+1) && (*map)[pos.x][pos.y+1] != barrier && !listCheck(pos.x, pos.y+1)) {
			openList.push_back(Node(best, target, vec2{pos.x, pos.y+1}));
		}

		if(inMap(pos.x, pos.y-1) && (*map)[pos.x][pos.y-1] != barrier && !listCheck(pos.x, pos.y-1)) {
			openList.push_back(Node(best, target, vec2{pos.x, pos.y-1}));
		}

		//diag neigbours
		if(inMap(pos.x-1, pos.y-1) && (*map)[pos.x-1][pos.y-1] != barrier && !listCheck(pos.x-1, pos.y-1)) {
			openList.push_back(Node(best, target, vec2{pos.x-1, pos.y-1}));
		}
		if(inMap(pos.x-1, pos.y+1) && (*map)[pos.x-1][pos.y+1] != barrier && !listCheck(pos.x-1, pos.y+1)) {
			openList.push_back(Node(best, target, vec2{pos.x-1, pos.y+1}));
		}
		if(inMap(pos.x+1, pos.y-1) && (*map)[pos.x+1][pos.y-1] != barrier && !listCheck(pos.x+1, pos.y-1)) {
			openList.push_back(Node(best, target, vec2{pos.x+1, pos.y-1}));
		}
		if(inMap(pos.x+1, pos.y+1) && (*map)[pos.x+1][pos.y+1] != barrier && !listCheck(pos.x+1, pos.y+1)) {
			openList.push_back(Node(best, target, vec2{pos.x+1, pos.y+1}));
		}
	}
	return true;
}

bool A_star::listCheck(int x, int y) {
	for (auto it = closedList.begin(); it != closedList.end(); ++it) {
		if((*it)->getPosition() == vec2{x, y})
			return true;
	}

	for (auto it = openList.begin(); it != openList.end(); ++it) {
		if(it->getPosition() == vec2{x, y}) {
			Node n2(best, target, vec2{x, y});

			if(n2.getF_cost() > it->getF_cost()) {
				return true;
			}else{
				openList.erase(it);

				return false;
			}
		}
	}

	return false;
}

bool A_star::inMap(int x, int y) {

	int height = (int)map->at(0).size();
	int width = (int)map->size();

	if(0 <= x && width  > x &&
	   0 <= y && height > y) {
		return true;
	}
	return false;
}


std::vector<vec2> A_star::getPath() {
	std::vector<vec2> path;

	Node* currNode = best;

	while(best && currNode->getParent()) {	// nullptr is start node
		path.push_back(currNode->getPosition());
		currNode = currNode->getParent();
	}

	return path;
}





















