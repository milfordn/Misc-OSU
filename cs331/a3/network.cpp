#include "network.h"
#include "math.h"
#include <cstdio>

using std::map;
using std::string;
using std::vector;

count::count(){
	positive = 1;
	total = 2;
}

void count::add(bool positive){
	if(positive)
		this->positive++;
	total++;
}

void add(map<string, count> * network, string word, bool positive){
	map<string, count>::iterator it = network->find(word);
	if(it == network->end()){
		network->operator[](word) = count();
	}
	network->operator[](word).add(positive);

	//printf("Word: \"%s\" Positive: %d Total: %d\n", word.c_str(), network->operator[](word).positive, network->operator[](word).total);
}

map<string, double> convert(map<string, count> * network){
	map<string, double> ret;
	for(map<string, count>::iterator it = network->begin(); it != network->end(); it++){
		ret[it->first] = (double)it->second.positive / (double)it->second.total;
	}

	return ret;
}

double infer(map<string, double> * network, vector<string> * words, bool pos){
	double accum = 0;

	for(vector<string>::iterator it = words->begin(); it != words->end();it++){
		double prob;
		if(network->count(*it))
			prob = network->operator[](*it);
		else
			prob = 0.5;
		//printf("probability \"%s\" is a positive comment: %f\n", it->c_str(), prob);
		if(pos) 
			accum += log(prob);
		else 
			accum += log(1 - prob);
	}

	//printf("probability of a %s comment: %f\n", pos ? "positive" : "negative", accum);
	return accum;
}
