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
#include <sys/time.h>
#include "rubik.h"
using namespace std;

class solver {
public:
	solver(string s, string r);
	void solve();
	void force(string lc);
	bool checkSolved(string s);
	virtual ~solver();
	unsigned int pcount;

	rubik* cube;
	rubik* test;
private:
	vector<string> commands;
	queue<string> triedCommands;
	bool isSolved;
	string tc;
        time_t start;
        time_t end;
        int stallCount;
        bool stallRequired;
};

#endif /* SOLVER_H_ */
