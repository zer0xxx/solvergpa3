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
        stallCount = 4;
        stallRequired = false;
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
			/*if (r.at(i) != 'X'
				&& r.at(i) != 'Y'
				&& r.at(i) != 'Z'
				&& r.at(i) != '\'') {*/
				if ((i + 1 < r.size()) && r.at(i + 1) == '\'') {
					string ps = string(1, r.at(i++));
					ps += '\'';
					commands.push_back(ps);
				}
				else {
					commands.push_back(string(1, r.at(i)));
				}
			}
		/*for (unsigned int i = 0; i < commands.size(); i++) {
			cout << commands[i];
		}
		cout << endl;*/
	}
}

void solver::solve() {
	for (unsigned int i = 0; i < commands.size(); i++) {
		triedCommands.push(commands.at(i));
	}
        time(&start);
	while (!isSolved && triedCommands.size() > 0) {
		test->setState(cube->display());
                test->resetOrientation();
		force(triedCommands.front());
		triedCommands.pop();
	}
}

void solver::force(string lastCommand) {
	//cout << "Passing " << lastCommand << endl;
	//cout << pcount++ << endl;
	//pcount++;
	/*if (lastCommand.at(lastCommand.length() - 1) == '\'') {
		tc = string(1, lastCommand.at(lastCommand.length() - 2)) + string(1, lastCommand.at(lastCommand.length() - 1));
	}
	else {
		tc = string(1, lastCommand.at(lastCommand.length() - 1));
	}
	test->process(tc);*/
        //cout << "FROM " << test->display() << endl;
	for (unsigned int i = 0; i < lastCommand.length(); i++) {
		//cout << lastCommand; 
		if (i < lastCommand.length() - 1 && lastCommand.at(i + 1) == '\'') {
			test->process(string(1, lastCommand.at(i)) + '\'');
                        tc = string(1, lastCommand.at(i)) + '\'';
                        //cout << "tc: " << tc << " " << endl;
                        /*for (int v = 0; v < 6; v++) {
                            cout << test->showOrientation().at(v);
                        }
                        cout << endl;*/
			i++;
		}
		else {
			test->process(string(1, lastCommand.at(i)));
                        tc = string(1, lastCommand.at(i));
                        //cout << "tc: " << tc << " " << endl;
                        /*for (int v = 0; v < 6; v++) {
                            cout << test->showOrientation().at(v);
                        }
                        cout << endl;*/
		}
                //cout << test->display() << endl;
	}
        //cout << "END: " << test->display() << endl;
	if (checkSolved(test->display())) {
		isSolved = true;
		//cout << "Solution Found " << lastCommand << " after " << pcount << " nodes" << endl;
                if (stallRequired && stallCount > 0) {
                    while (stallCount-- > 0) {
                        cout << commands.at(0) << endl;
                    }
                }
		for (unsigned int j = 0; j < lastCommand.length(); j++) {
			if (j + 1 < lastCommand.length() && lastCommand.at(j+1) == '\'') {
				cout << lastCommand.at(j++) << "'" << endl;
			}
			else {
				cout << lastCommand.at(j) << endl;
			}
		}
	}
	else {
            time(&end);
            if (difftime(end, start) > 20) {
                stallRequired = true;
                cout << commands.at(0) << endl;
                if (stallCount-- == 1) {
                    stallCount = 4;
                }
                time(&start);
            }

            /*if (tc.compare("Y")) { test->process("Y'"); }
            else if (tc.compare("Y'")) { test->process("Y"); }
            else if (tc.compare("X")) { test->process("X'"); }
            else if (tc.compare("X'")) { test->process("X"); }
            else if (tc.compare("Z")) { test->process("Z'"); }
            else if (tc.compare("Z'")) { test->process("Z"); }*/
            //if ((test->display()).compare(cube->display()) != 0) {
            /*
             * On rotation, don't compare state, always append next commands
             */
            /*if (lastCommand.compare("ZZF'D'B'R'") == 0) {
                cout << "HUH!" << endl;
            }*/
            if (tc.compare("X") != 0 && tc.compare("X'") != 0 &&
                    tc.compare("Y") != 0 && tc.compare("Y'") != 0 &&
                    tc.compare("Z") != 0 && tc.compare("Z'") != 0) {
                if ((test->display()).compare(cube->display()) != 0) {
                    for (unsigned int i = 0; i < commands.size(); i++) {
                            if (tc.compare(commands.at(i) + "'") != 0
                                    && (tc + "'").compare(commands.at(i)) != 0) {
                                triedCommands.push(lastCommand + commands.at(i));
                            }
                    }
                }
                /*else {
                    cout << lastCommand << " pruned" << endl;
                }*/
            }
            else {
                for (unsigned int i = 0; i < commands.size(); i++) {
                    if (tc.compare(commands.at(i) + "'") != 0
                            && (tc + "'").compare(commands.at(i)) != 0) {
                        triedCommands.push(lastCommand + commands.at(i));
                    }
                }
            }
            //}
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
