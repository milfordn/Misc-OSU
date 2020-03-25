#include "base.h"
#include <set>
#include <cstdio>
#include <algorithm>
using std::vector;
using std::set;

state get_parent(state * ch){
	state toRet;
	toRet.has_prev = false;
	toRet.l_wolves = ch->p_lwolves;
	toRet.r_wolves = ch->p_rwolves;
	toRet.l_chickens = ch->p_lchickens;
	toRet.r_chickens = ch->p_rchickens;
	toRet.l_boat = ch->p_lboat;
	return toRet;
}

void set_parent(state * ch, state * p){
	ch->has_prev = true;
	ch->depth = p->depth + 1;
	ch->p_lwolves = p->l_wolves;
	ch->p_rwolves = p->r_wolves;
	ch->p_lchickens = p->l_chickens;
	ch->p_rchickens = p->r_chickens;
	ch->p_lboat = p->l_boat;
}

void write(state * s, char * buf){
	sprintf(buf, "Left: %d chickens, %d wolves, %d boat | Right: %d chickens, %d wolves, %d boat"
		, s->l_chickens, s->l_wolves, s->l_boat, s->r_chickens, s->r_wolves, !s->l_boat);
}

state copy(state * s){
	state toRet;
	toRet.l_wolves = s->l_wolves;
	toRet.r_wolves = s->r_wolves;
	toRet.l_chickens = s->l_chickens;
	toRet.r_chickens = s->r_chickens;
	toRet.l_boat = s->l_boat;
	return toRet;
}

vector<state> state_next(state * s){
	vector<state> toRet;
	state ns = copy(s);
	set_parent(&ns, s);
	int dir = ns.l_boat ? -1 : 1;

	//case 1: move one chicken
	ns.l_boat = !ns.l_boat;
	ns.l_chickens += dir;
	ns.r_chickens -= dir;
	toRet.push_back(ns);

	//case 2: move two chickens
	ns.l_chickens += dir;
	ns.r_chickens -= dir;
	toRet.push_back(ns);

	//case 3: move one wolf
	ns.l_chickens = s->l_chickens;
	ns.r_chickens = s->r_chickens;
	ns.l_wolves += dir;
	ns.r_wolves -= dir;
	toRet.push_back(ns);

	//case 4: move one wolf and one chicken
	ns.l_chickens += dir;
	ns.r_chickens -= dir;
	toRet.push_back(ns);

	//case 5: move two wolves
	ns.l_chickens = s->l_chickens;
	ns.r_chickens = s->r_chickens;
	ns.l_wolves += dir;
	ns.r_wolves -= dir;
	toRet.push_back(ns);

	return toRet;
}

bool state_valid(state * s){
	char l_safe = s->l_chickens == 0 || (s->l_chickens >= s->l_wolves);
	char r_safe = s->r_chickens == 0 || (s->r_chickens >= s->r_wolves);
	char possible = s->l_chickens >= 0 && s->r_chickens >= 0 && s->l_wolves >= 0 && s->r_wolves >= 0;
	return l_safe && r_safe && possible;
}

bool state_eq(state * s1, state * s2){
	return s1->l_chickens == s2->l_chickens
	&& s1->l_wolves == s2->l_wolves
	&& s1->r_chickens == s2->r_chickens
	&& s1->r_wolves == s2->r_wolves
	&& s1->l_boat == s2->l_boat;
}

void filter_valid(vector<state> * vs){
	for(vector<state>::iterator it = vs->begin(); it != vs->end();){
		if(!state_valid(&(*it)))
			vs->erase(it);
		else
			++it;
	}
}

void filter_found(vector<state> * vs, set<state> * ss){
	for(vector<state>::iterator it = vs->begin(); it != vs->end();){
		if(ss->find(*it) != ss->end())
			vs->erase(it);
		else
			++it;
	}
}

bool operator<(const state & l, const state & r){
	int lhash = l.l_chickens + l.l_wolves * 256 + l.l_boat * 256 * 256;
	int rhash = r.l_chickens + r.l_wolves * 256 + r.l_boat * 256 * 256;

	return lhash < rhash;
}

state * toDynamic(state s){
	state * ns = new state(s);
	return ns;
}

vector<state> getPath(state goal, set<state> * ss){
	vector<state> toRet;
	while(goal.has_prev){
		state prev = get_parent(&goal);
		toRet.push_back(goal);
		goal = *ss->find(prev);
	}
	toRet.push_back(goal);
	std::reverse(toRet.begin(), toRet.end());
	return toRet;	
}
