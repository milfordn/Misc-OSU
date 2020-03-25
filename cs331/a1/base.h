#ifndef BASE_H
#define BASE_H

#include <vector>
#include <set>
using std::set;
using std::vector;

struct state {
	int l_wolves, l_chickens, r_wolves, r_chickens;
	bool l_boat;

	bool has_prev;
	int p_lwolves, p_lchickens, p_rwolves, p_rchickens;
	bool p_lboat;

	int depth;
	friend bool operator<(const state & l, const state & r);
};

state get_parent(state * ch);
void set_parent(state * ch, state * p);
void write(state * s, char * buf);
state copy(state * s);
vector<state> state_next(state * s);
bool state_valid(state * s);
bool state_eq(state * s1, state * s2);
void filter_valid(vector<state> * vs);
void filter_found(vector<state> * vs, set<state> * ss);
state * toDynamic(state s);
vector<state> getPath(state goal, set<state> * ss);

#endif

