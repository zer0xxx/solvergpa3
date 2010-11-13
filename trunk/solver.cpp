/*
 * solver.cpp
 *
 *  Created on: Nov 7, 2010
 *      Author: gbudiman
 */

#include "solver.h"
#include "rubik.h"
#include <sys/time.h> 
#include <string>
using namespace std;

solver::solver(string state, string r) {
	// TODO Auto-generated constructor stub
	cube = new rubik();
	test = new rubik();
	isSolved = false;
	pcount = 0;
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
		/*for (unsigned int i = 0; i < commands.size(); i++) {
			cout << commands[i];
		}
		cout << endl;*/
	}
}

void solver::solve() {
	for (int i = 0; i < commands.size(); i++) {
		triedCommands.push(commands.at(i));
	}
	while (!isSolved && triedCommands.size() > 0) {
		test->setState(cube->display());
		force(cube, triedCommands.front(), 0);
		triedCommands.pop();
	}
}

void solver::force(rubik* crubik, string lastCommand, int comLength) {
	//cout << "Passing " << lastCommand << endl;
	//cout << pcount++ << endl;
	pcount++;
	/*if (lastCommand.at(lastCommand.length() - 1) == '\'') {
		tc = string(1, lastCommand.at(lastCommand.length() - 2)) + string(1, lastCommand.at(lastCommand.length() - 1));
	}
	else {
		tc = string(1, lastCommand.at(lastCommand.length() - 1));
	}
	test->process(tc);*/
	string tc;
	for (int i = 0; i < lastCommand.length(); i++) {
		if (i < lastCommand.length() - 1 && lastCommand.at(i + 1) == '\'') {
			test->process(string(1, lastCommand.at(i)) + '\'');
			tc = string(1, lastCommand.at(i)) + '\'';
			i++;
		}
		else {
			test->process(string(1, lastCommand.at(i)));
			tc = string(1, lastCommand.at(i));
		}
	}
	if (checkSolved(test->display())) {
		isSolved = true;
		//cout << "Solution Found " << lastCommand << " after " << pcount << " nodes" << endl;
		for (int j = 0; j < lastCommand.length(); j++) {
			if (j + 1 < lastCommand.length() && lastCommand.at(j+1) == '\'') {
				cout << lastCommand.at(j++) << "'" << endl;
			}
			else {
				cout << lastCommand.at(j) << endl;
			}
		}
	}
	else {
		if ((test->display()).compare(cube->display()) != 0) {
			for (int i = 0; i < commands.size(); i++) {
				if (tc.compare(commands.at(i) + "'") != 0 && (tc + "'").compare(commands.at(i)) != 0)
				triedCommands.push(lastCommand + commands.at(i));
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
