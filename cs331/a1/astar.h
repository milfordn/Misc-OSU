#include "base.h"

using std::vector;

struct weightedState{
	weightedState(state toCopy, state * goal);
	state s;
	int weight;
	friend bool operator<(const weightedState & a, const weightedState & b);
};

vector<state> astar(state * start, state * end, int * out_nodes);

