#include "base.h"
#include <vector>

using std::vector;

vector<state> DFS(state * start, state * end, int * out_nodes, int max_depth, int * out_nodesAtDepth);
vector<state> IDDFS(state * start, state * end, int * out_nodes);
