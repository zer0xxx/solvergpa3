/*
 * solver.h
 *
 *  Created on: Nov 7, 2010
 *      Author: gbudiman
 */

#ifndef SOLVER_H_
#define SOLVER_H_
#include <string>
#include <vector>
#include <queue>
#include "rubik.h"
using namespace std;

class solver {
public:
	solver(string s, string r);
	void solve();
	void force(rubik* cube, string lc, int steps);
	bool checkSolved(string s);
	virtual ~solver();

	rubik* cube;
	rubik* test;
private:
	vector<string> commands;
	queue<string> triedCommands;
	bool isSolved;
	string tc;
};

#endif /* SOLVER_H_ */
