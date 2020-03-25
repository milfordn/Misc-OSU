#include "dfs.h"
#include <set>
#include <cstdio>

//#define TRACE

using std::set;
using std::vector;

vector<state> DFS(state * start, state * goal, int * out_nodes, int max_depth, int * out_nodesAtDepth){
	int nodes = 0;
	int nodesAtDepth = 0;
	vector<state> fringe;
	set<state> searched;
	
	fringe.push_back(*start);
	
	while(true){
		if(fringe.empty()){
			#ifdef TRACE
			printf("solution not found, searched %d nodes\n", nodes);
			#endif
			*out_nodes = nodes;
			*out_nodesAtDepth = nodesAtDepth;
			vector<state> empty;
			return empty;
		}

		state current = *fringe.begin();
		fringe.erase(fringe.begin());
	
		//skip if duplicate and duplicate is better than current
		set<state>::iterator found = searched.find(current);
		if(found != searched.end()){
			//found a better solution? erase the old one
			if(found->depth > current.depth)
				searched.erase(found);
			else
				continue;
		}


		#ifdef TRACE
		char buf[100];
		write(&current, buf);
		puts(buf);
		#endif
	
		if(state_eq(&current, goal)){
			*out_nodes = nodes;
			*out_nodesAtDepth = nodesAtDepth;
			return getPath(current, &searched);
		}

		searched.insert(current);

		if(max_depth >= 0 && current.depth == max_depth){
			nodesAtDepth++;
		}
		else {
			vector<state> next = state_next(&current);
			filter_valid(&next);
			fringe.insert(fringe.begin(), next.begin(), next.end());
		}

		nodes++;
	}
}

vector<state> IDDFS(state * start, state * goal, int * out_nodes){
	int node_count = 0;
	for(int max = 0;;max++){
		int _ = 0;
		int newNodes = 0;
		vector<state> maybeSolution = DFS(start, goal, &newNodes, max, &_);

		node_count += newNodes;

		#ifdef TRACE
		printf("searched up to depth %d, added %d nodes", max, atDepth);
		#endif

		//if a solution is found, return it
		if(!maybeSolution.empty()){
			*out_nodes = node_count;
			return maybeSolution;
		}
	}
}
