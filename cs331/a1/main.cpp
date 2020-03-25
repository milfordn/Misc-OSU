#include "base.h"
#include "bfs.h"
#include "dfs.h"
#include "astar.h"
#include <cstdio>
#include <cstring>

using std::vector;

void read(char * file, state * s){
        FILE * fp = fopen(file, "r+");
        fscanf(fp, "%d,%d,%d\n", &(s->l_chickens), &(s->l_wolves), &(s->l_boat));
        fscanf(fp, "%d,%d,%*d\n", &(s->r_chickens), &(s->r_wolves));
	s->has_prev = false;
}

void write(FILE * fp, vector<state> * solution){
	char buf[100];

	for(vector<state>::iterator it = solution->begin(); it != solution->end(); it++){
		write(&(*it), buf);
		fputs(buf, fp);
		fputc('\n', fp);
	}
}

int main(int argc, char ** argv){
	if(argc != 5){
		puts("yu fukin bad");
		return 1;
	}

	state start, goal;
	read(argv[1], &start);
	read(argv[2], &goal);
	char * mode = argv[3];

	int searched = 0, _;
	vector<state> solution;	

	if(!strcmp(mode, "bfs"))
		solution = BFS(&start, &goal, &searched);
	else if(!strcmp(mode, "dfs"))
		solution = DFS(&start, &goal, &searched, -1, &_);
	else if(!strcmp(mode, "iddfs"))
		solution = IDDFS(&start, &goal, &searched);
	else if(!strcmp(mode, "astar"))
		solution = astar(&start, &goal, &searched);
	
	printf("Searched %d Nodes\n", searched);

	FILE * fp = fopen(argv[4], "w+");
	write(fp, &solution);
	write(stdout, &solution);	

	return 0;
}
