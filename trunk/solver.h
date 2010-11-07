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
#include "rubik.h"
using namespace std;

class solver {
public:
	solver(string s, string r);
	void solve();
	rubik* cube;
	virtual ~solver();
private:
	vector<string> commands;
};

#endif /* SOLVER_H_ */
