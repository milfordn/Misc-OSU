// Network.h
#ifndef NET_H
#define NET_H

#include <map>
#include <string>
#include <vector>

using std::vector;
using std::map;
using std::string;

struct count {
public:
	int positive, total;
	void add(bool positive);
	count();
};

void add(map<string, count> * network, string word, bool positive);

map<string, double> convert(map<string, count> * network);

double infer(map<string, double> * network, vector<string> * sentence, bool);

#endif
