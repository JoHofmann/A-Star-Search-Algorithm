#include "a_star/node.hpp"

Node::Node(Node* parent, vec2 target, vec2 position) :
	parent(parent), position(position)
{
	if(!parent) {
		g_cost = 0;	// start node has no g cost
	}else{
		g_cost = calcGCost();
	}

	h_cost = manhattan(position, target);

	f_cost = g_cost + h_cost;
}

Node::~Node()
{}

Node* Node::getParent() {
	return parent;
}

uint Node::manhattan(const vec2& a, const vec2& b) {
	return STRAIGHT_COST * (abs(a.x - b.x) + abs(a.y - b.y));
}

uint Node::calcGCost() {
	int parentX = parent->getPosition().x;
	int parentY = parent->getPosition().y;

	int x = position.x;
	int y = position.y;

	if(parentX < x && parentY < y) {	// top left
		return g_diag;
	}
	if(parentX < x && parentY == y) {	// left
		return g_straight;
	}
	if(parentX < x && parentY > y) {  // bottom left
		return g_diag;
	}
	if(parentX == x && parentY > y) { // bottom
		return g_straight;
	}
	if(parentX == x && parentY < y) { // top
		return g_straight;
	}
	if(parentX > x && parentY < y) {	// top right
		return g_diag;
	}
	if(parentX > x && parentY == y) { // right
		return g_straight;
	}
	if(parentX > x && parentY > y) { // bottom right
		return g_diag;
	}
	return 0.f;
}






