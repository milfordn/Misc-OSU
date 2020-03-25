#include "base.h"
#include <set>
#include <vector>
#include <cstdio>

//#define TRACE

using std::vector;
using std::set;

vector<state> BFS(state * start, state * goal, int * out_nodes){
	int nodes = 0;
	
	vector<state> fringe;
	set<state> searched;

	fringe.push_back(*start);

	while(true){
		if(fringe.empty()) {
			printf("solution not found, searched %d nodes\n", nodes);
		}

		state current = *fringe.begin();
		fringe.erase(fringe.begin());

		//skip if duplicate
		if(searched.find(current) != searched.end())
			continue;

		#ifdef TRACE
		char buf[100];
		write(&current, buf);
		puts(buf);
		#endif

		if(state_eq(&current, goal)){
			*out_nodes = nodes;
			return getPath(current, &searched);
		}

		searched.insert(current);

		vector<state> next = state_next(&current);
		filter_valid(&next);

		#ifdef TRACE
		printf("adding %d nodes to fringe | total %d\n", next.size(), nodes);
		#endif

		fringe.insert(fringe.end(), next.begin(), next.end());
		nodes++;
	}
}
