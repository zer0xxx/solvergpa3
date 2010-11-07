/*
 * solver.cpp
 *
 *  Created on: Nov 7, 2010
 *      Author: gbudiman
 */

#include "solver.h"
#include "rubik.h"
#include <string>
using namespace std;

solver::solver(string state, string r) {
	// TODO Auto-generated constructor stub
	cube = new rubik();
	if (r.compare("0") == 0) {
		cube->setState(state);
		commands.push_back("U");
		commands.push_back("U'");
		commands.push_back("D");
		commands.push_back("D'");
		commands.push_back("R");
		commands.push_back("R'");
		commands.push_back("L");
		commands.push_back("L'");
		commands.push_back("F");
		commands.push_back("F'");
		commands.push_back("B");
		commands.push_back("B'");
	}
}

void solver::solve() {
	// 1 step solver
	string intermediate;
	for (int i = 0; i < commands.size(); i++) {
		intermediate = cube->display();
		cube->process(commands[i]);
		cout << cube->display() << endl;
		cube->setState(intermediate);
	}
}

solver::~solver() {
	// TODO Auto-generated destructor stub
}
