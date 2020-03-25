#include "astar.h"
#include <queue>
#include <cstdio>

//#define TRACE

using std::priority_queue;
using std::vector;
using std::set;

int state_diff(state * sa, state * sb){
	int ch_diff = sa->l_chickens - sb->l_chickens;
	int wf_diff = sa->l_wolves - sb->l_wolves;
	bool boat_diff = sa->l_boat ^ sb->l_boat;

	if(ch_diff < 0) ch_diff *= -1;
	if(wf_diff < 0) wf_diff *= -1;

	int total_diff = ch_diff + wf_diff;
	
	//boat is on the "from" side and all animals can be moved in one trip
	if(total_diff <= 2 && boat_diff) return 1;

	//boat is on the "from" side, but multiple trips are needed
	if(boat_diff) return total_diff * 2 - 3;

	//boat is on the "to" side, so it has to bring an animal back first
	if(!boat_diff) return (total_diff + 1) * 2 - 2;
}

weightedState::weightedState(state toCopy, state * goal){
	this->s = toCopy;
	this->weight = toCopy.depth + state_diff(&toCopy, goal);
}

bool operator<(const weightedState & a, const weightedState & b){
	return a.weight > b.weight;
}

void add_weighted(vector<state> * vs, state * goal, priority_queue<weightedState> * fringe){
	for(vector<state>::iterator it = vs->begin(); it != vs->end(); it++){
		fringe->push(weightedState(*it, goal));
	}
}

vector<state> astar(state * start, state * goal, int * out_nodes){
	int nodes = 0;

	priority_queue<weightedState> fringe;
	set<state> searched;
	
	fringe.push(weightedState(*start, goal));

	while(true){
		if(fringe.empty()) {
			return vector<state>();
		}

		state current = fringe.top().s;

		#ifdef TRACE
		printf("current state weight: %d | depth: %d\n", fringe.top().weight, current.depth);
		#endif

		fringe.pop();

		if(searched.find(current) != searched.end())
			continue;

		if(state_eq(&current, goal)){
			*out_nodes = nodes;
			return getPath(current, &searched);
		}

		searched.insert(current);

		vector<state> next = state_next(&current);
		filter_valid(&next);

		add_weighted(&next, goal, &fringe);
		nodes++;		
	}	
}
