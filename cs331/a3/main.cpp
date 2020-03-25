#include "parse.h"
#include "network.h"
#include <cstdio>
#include <cstdlib>

using std::string;
using std::vector;
using std::map;

int main(int argc, char ** argv){
	char * trainFile = argv[1];
	char * testFile = argv[2];

	printf("opening training file...");
	FILE * ftrain = fopen(trainFile, "r+");
	puts("done");

	printf("initializing tables...");
	map<string, count> mapFuckers;
	map<string, double> network;
	puts("done");

	//read training file
	puts("reading training file...");
	char _[300];
	char * line = _;
	size_t len = 0;
	bool isPos = false;

	puts("starting parse loop");
	while(getline(&line, &len, ftrain) != -1){
		vector<string> words = split(line, isPos);
		
		for(vector<string>::iterator it = words.begin(); it != words.end(); it++){
			add(&mapFuckers, *it, isPos);
		}
	}
	free(line);
	puts("done");

	fclose(ftrain);
	network = convert(&mapFuckers);

	//compare testing file
	FILE * ftest = fopen(testFile, "r+");
	int accum = 0, correct = 0;
	puts("starting inference loop");
	while(getline(&line, &len, ftest) != -1){
		puts("splitting line");
		vector<string> words = split(line, isPos);

		puts("inferring...");
		double probPos = infer(&network, &words, true);
		double probNeg = infer(&network, &words, false);

		accum++;
		if(probPos > probNeg == isPos){
			correct++;
			puts("Inference Correct!");
		}
	}

	fclose(ftest);
	printf("Proportion Correct: %f\n", (double)correct / accum);
	puts("dunzo");
	return 0;
}
