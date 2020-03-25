#include "parse.h"
#include <cstdio>
#include <ctype.h>
#include <cstring>

using std::vector;
using std::string;
using std::size_t;
using std::tolower;

string substrUntil(const string& in, char delim, size_t start = 0){
	size_t pos = in.find(delim, start);
	return in.substr(0, pos);
}

void sanitize(string & s){
	size_t pos = 0;

	//remove dots
	while((pos = s.find('.', pos+1)) != string::npos){
		s.replace(pos, 1, " ");
	}
	while((pos = s.find(',', pos+1)) != string::npos){
		s.replace(pos, 1, " ");
	}
	
	//remove multiple spaces
	while((pos = s.find("  ")) != string::npos){
		s.replace(pos, 2, " ");
	}

	for(size_t i = 0; i < s.length(); i++){
		s[i] = tolower(s[i]);
	}
}

vector<string> split(char * in, bool & isPos){
	vector<string> ret;
	size_t pos = 0;
	size_t plast = 0;
	int len = strlen(in);	

	char c = in[len - 4];
	isPos = c == '1';
	in[len - 6] = 0;
	printf("%s is a %s comment with '%c'\n", in, isPos ? "Positive" : "Negative", c);
	string s(in);
	sanitize(s);

	while((pos = s.find(' ', plast)) != string::npos){
		ret.push_back(s.substr(plast, pos - plast));
		plast = pos + 1;
	}

	return ret;
}

bool getPos(vector<string> * line){
	string v = line->back();
	line->pop_back();
	return v == "1";
}
