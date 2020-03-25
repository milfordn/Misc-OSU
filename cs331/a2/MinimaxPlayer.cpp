/*
 * MinimaxPlayer.cpp
 *
 *  Created on: Apr 17, 2015
 *      Author: wong
 */
#include <iostream>
#include <cstdio>
#include <assert.h>
#include "MinimaxPlayer.h"

using std::vector;

int _; //throwaway variable

int utility(OthelloBoard * b){
	return b->count_score(b->get_p1_symbol()) - b->count_score(b->get_p2_symbol());
}

vector<OthelloBoard> SUCC(OthelloBoard b, char pSymbol, vector<int> & cols, vector<int> & rows){
	vector<OthelloBoard> toRet;
	for(int i = 0; i < b.get_num_cols(); i++)
		for(int j = 0; j < b.get_num_rows(); j++){
			if(b.is_legal_move(i, j, pSymbol)){
				OthelloBoard next = b;
				next.play_move(i, j, pSymbol);
				cols.push_back(i);
				rows.push_back(j);
				toRet.push_back(next);
			}
		}

	return toRet;
}

int Min_play(OthelloBoard b, int & out_col, int & out_row){
	vector<int> rows, cols;
	vector<OthelloBoard> SUCCs = SUCC(b, b.get_p2_symbol(), cols, rows);
	if(SUCCs.empty()) return utility(&b);

	int min = b.get_num_rows() * b.get_num_cols();
	for(int i = 0; i < SUCCs.size(); i++){
		int v = Max_play(SUCCs[i], _, _);
		if(v < min){
			min = v;
			out_col = cols[i];
			out_row = rows[i];
		}
	}
	
	return min;
}

int Max_play(OthelloBoard b, int & out_col, int & out_row){
	vector<int> rows, cols;
	vector<OthelloBoard> SUCCs = SUCC(b, b.get_p1_symbol(), cols, rows);
	if(SUCCs.empty()) return utility(&b);

	int max = -b.get_num_rows() * b.get_num_cols();
	for(int i = 0; i < SUCCs.size(); i++){
		int v = Min_play(SUCCs[i], _, _);
		if(v > max){
			max = v;
			out_col = cols[i];
			out_row = rows[i];
		}
	}
	
	return max;
}

MinimaxPlayer::MinimaxPlayer(char symbol) :
		Player(symbol) {

}

MinimaxPlayer::~MinimaxPlayer() {

}

void MinimaxPlayer::get_move(OthelloBoard* b, int& col, int& row) {
	if(symbol == b->get_p1_symbol()){
		int max_util = Max_play(*b, col, row);
		printf("Max Util: %d\n\n", max_util);
	}
	else{
		int min_util = Min_play(*b, col, row);
		printf("Min Util: %d\n\n", min_util);
	}
}

MinimaxPlayer* MinimaxPlayer::clone() {
	MinimaxPlayer* result = new MinimaxPlayer(symbol);
	return result;
}
