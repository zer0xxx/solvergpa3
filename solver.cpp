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
	test = new rubik();
	cube->setState(state);
	if (r.compare("0") == 0) {
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
	else {
		for (unsigned int i = 0; i < r.size(); i++) {
			if (r.at(i) != 'X'
				&& r.at(i) != 'Y'
				&& r.at(i) != 'Z'
				&& r.at(i) != '\'') {
				if ((i + 1 < r.size()) && r.at(i + 1) == '\'') {
					string ps = string(1, r.at(i++));
					ps += '\'';
					commands.push_back(ps);
				}
				else {
					commands.push_back(string(1, r.at(i)));
				}
			}
		}
		for (unsigned int i = 0; i < commands.size(); i++) {
			cout << commands[i];
		}
		cout << endl;
	}
}

void solver::solve() {
	// 4 steps solver
	string intermediate;
	cout << "Possible solutions: " << endl;
	for (unsigned int i = 0; i < commands.size(); i++) {
		force(cube, commands[i], 6);
	}
}

void solver::force(rubik* crubik, string lastCommand, int stepsLeft) {
	if (stepsLeft >= 1) {
		string tc = "";
		test->setState(crubik->display());
		if (lastCommand.at(lastCommand.size() - 1) == '\'') {
			tc.append(1, lastCommand.at(lastCommand.size() - 2));
			tc.append("'");
		}
		else {
			tc.append(1, lastCommand.at(lastCommand.size() - 1));
		}
		test->process(tc);
		string localState = test->display();
		if (checkSolved(test->display())) {
			cout << lastCommand << endl;
		}
		for (unsigned int i = 0; i < commands.size(); i++) {
			//cout << tc.compare(commands[i] + "'") << endl;
			if (tc.compare(commands[i] + "'") != 0 && commands[i].compare(tc + "'") != 0) {
				//cout << tc << " | " << commands[i] << endl;
				string localCommand = lastCommand;
				test->setState(localState);
				force(test, localCommand.append(commands[i]), stepsLeft-1);
			}
		}
	}
}

bool solver::checkSolved(string state) {
	if (state.compare("YYYYYYYYYRRRRRRRRRGGGGGGGGGOOOOOOOOOBBBBBBBBBWWWWWWWWW") == 0) {
		return true;
	}
	return false;
}

solver::~solver() {
	// TODO Auto-generated destructor stub
}
