#ifndef NODE_H
#define NODE_H

#include <cmath>

typedef int unsigned uint;

const static uint STRAIGHT_COST = 10;
const static uint DIAG_COST = 14;

#define g_straight STRAIGHT_COST + parent->getG_cost()
#define g_diag DIAG_COST + parent->getG_cost()

struct vec2 {
	int x;
	int y;

	bool operator==(const vec2& other) {
		if(x == other.x && y == other.y) {
			return true;
		}
		return false;
	}
};

class Node
{
public:
	Node(Node* parent, vec2 target, vec2 position);
	~Node();

	Node* getParent();
	vec2 getPosition() { return position; }

	uint getG_cost() { return g_cost; }
	uint getF_cost() { return f_cost; }


	friend bool operator<(const Node& n1, const Node& n2) {
		return n1.f_cost < n2.f_cost;
	}

private:
	uint manhattan(const vec2& a, const vec2& b);
	uint calcGCost();

private:
	Node* parent;
	vec2 position;

	uint g_cost;
	uint h_cost;
	uint f_cost;
};

#endif
