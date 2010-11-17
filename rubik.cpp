/*
 * rubik.cpp
 *
 *  Created on: Nov 7, 2010
 *      Author: gbudiman
 */

#include "rubik.h"
#include <stdlib.h>
#include <vector>
#include <QtCore>

rubik::rubik() {
	// TODO Auto-generated constructor stub
	for (int cell = 0; cell < 9; cell++) {
		cube[0][cell] = 'Y';
		cube[1][cell] = 'R';
		cube[2][cell] = 'G';
		cube[3][cell] = 'O';
		cube[4][cell] = 'B';
		cube[5][cell] = 'W';
	}
	top = 0;
	front = 1;
	right = 2;
	back = 3;
	left = 4;
	down = 5;
}

void rubik::reset() {
	for (int cell = 0; cell < 9; cell++) {
		cube[0][cell] = 'Y';
		cube[1][cell] = 'R';
		cube[2][cell] = 'G';
		cube[3][cell] = 'O';
		cube[4][cell] = 'B';
		cube[5][cell] = 'W';
	}
	top = 0;
	front = 1;
	right = 2;
	back = 3;
	left = 4;
	down = 5;
}

void rubik::resetOrientation() {
    top = 0;
    front = 1;
    right = 2;
    back = 3;
    left = 4;
    down = 5;
}
string rubik::display() {
	string dump = "";
	for (int face = 0; face < 6; face++) {
		for (int cell = 0; cell < 9; cell++) {
			dump.append(string(1, cube[face][cell]));
		}
	}
	return dump;
}

vector<int> rubik::showOrientation() {
    vector<int> so;
    so.push_back(top);
    so.push_back(front);
    so.push_back(right);
    so.push_back(back);
    so.push_back(left);
    so.push_back(down);
    return so;
}

void rubik::applyOrientation(vector<int> s) {
    top = s.at(0);
    front = s.at(1);
    right = s.at(2);
    back = s.at(3);
    left = s.at(4);
    down = s.at(5);
}

void rubik::transpose(int face, bool clockwise) {
	if (clockwise) {
		char temp = cube[face][0];
		char temp2 = cube[face][1];
		cube[face][0] = cube[face][6];
		cube[face][6] = cube[face][8];
		cube[face][8] = cube[face][2];
		cube[face][2] = temp;

		cube[face][1] = cube[face][3];
		cube[face][3] = cube[face][7];
		cube[face][7] = cube[face][5];
		cube[face][5] = temp2;
	}
	else {
		char temp = cube[face][0];
		char temp2 = cube[face][1];
		cube[face][0] = cube[face][2];
		cube[face][2] = cube[face][8];
		cube[face][8] = cube[face][6];
		cube[face][6] = temp;

		cube[face][1] = cube[face][5];
		cube[face][5] = cube[face][7];
		cube[face][7] = cube[face][3];
		cube[face][3] = temp2;
	}
}

void rubik::setState(string iState) {
	int stringPointer = 0;
	for (int face = 0; face < 6; face++) {
		for (int i = 0; i < 9; i++) {
			cube[face][i] = iState.at(stringPointer++);
		}
	}
}

void rubik::roll(int f1, int c11, int c12, int c13,
		int f2, int c21, int c22, int c23,
		int f3, int c31, int c32, int c33,
		int f4, int c41, int c42, int c43, bool clockwise) {
	char t1 = cube[f1][c11];
	char t2 = cube[f1][c12];
	char t3 = cube[f1][c13];

	if (!clockwise) {
		cube[f1][c11] = cube[f2][c21];
		cube[f1][c12] = cube[f2][c22];
		cube[f1][c13] = cube[f2][c23];

		cube[f2][c21] = cube[f3][c31];
		cube[f2][c22] = cube[f3][c32];
		cube[f2][c23] = cube[f3][c33];

		cube[f3][c31] = cube[f4][c41];
		cube[f3][c32] = cube[f4][c42];
		cube[f3][c33] = cube[f4][c43];

		cube[f4][c41] = t1;
		cube[f4][c42] = t2;
		cube[f4][c43] = t3;
	}
	else {
		cube[f1][c11] = cube[f4][c41];
		cube[f1][c12] = cube[f4][c42];
		cube[f1][c13] = cube[f4][c43];

		cube[f4][c41] = cube[f3][c31];
		cube[f4][c42] = cube[f3][c32];
		cube[f4][c43] = cube[f3][c33];

		cube[f3][c31] = cube[f2][c21];
		cube[f3][c32] = cube[f2][c22];
		cube[f3][c33] = cube[f2][c23];

		cube[f2][c21] = t1;
		cube[f2][c22] = t2;
		cube[f2][c23] = t3;
	}
}

void rubik::process(string command) {
	if (command.compare("X") == 0) {
		//System.out.println("Rotate along X axis CW");
		int temp = top;
		top = front;
		front = down;
		down = back;
		back = temp;
	}
	else if (command.compare("X'") == 0) {
		//System.out.println("Rotate along X axis CCW");
		int temp = top;
		top = back;
		back = down;
		down = front;
		front = temp;
	}
	// Affected: front, left, right, back;
	else if (command.compare("Y") == 0) {
		//System.out.println("Rotate along Y axis CW");
		int temp = front;
		front = right;
		right = back;
		back = left;
		left = temp;
	}
	else if (command.compare("Y'") == 0) {
		//System.out.println("Rotate along Y axis CCW");
		int temp = front;
		front = left;
		left = back;
		back = right;
		right = temp;
	}
	// Affected: top, left, right, down
	else if (command.compare("Z") == 0) {
		//System.out.println("Rotate along Z axis CW");
		int temp = top;
		top = left;
		left = down;
		down = right;
		right = temp;
	}
	else if (command.compare("Z'") == 0) {
		//System.out.println("Rotate along Z axis CCW");
		int temp = top;
		top = right;
		right = down;
		down = left;
		left = temp;
	}

	/*
	 * Modify cube
	 */
	else if (command.compare("U") == 0) {
		//System.out.println("Turn top face CW");
		switch (front) {
		case 0:
			switch (top) {
			case 1: roll(front,0,3,6,left,0,3,6,back,0,3,6,right,8,5,2,true); break;
			case 2: roll(front,6,7,8,left,0,3,6,back,2,1,0,right,8,5,2,true); break;
			case 3: roll(front,8,5,2,left,0,3,6,back,8,5,2,right,8,5,2,true); break;
			case 4: roll(front,2,1,0,left,0,3,6,back,6,7,8,right,8,5,2,true); break;
			} break;
			case 1:
				switch (top) {
				case 0: roll(front,2,1,0,left,2,1,0,back,2,1,0,right,2,1,0,true); break;
				case 2: roll(front,8,5,2,left,6,7,8,back,0,3,6,right,2,1,0,true); break;
				case 4: roll(front,0,3,6,left,6,7,8,back,8,5,2,right,2,1,0,true); break;
				case 5: roll(front,6,7,8,left,6,7,8,back,6,7,8,right,6,7,8,true); break;
				} break;
				case 2:
					switch (top) {
					case 0: roll(front,2,1,0,left,2,1,0,back,2,1,0,right,2,1,0,true); break;
					case 1: roll(front,0,3,6,left,0,3,6,back,8,5,2,right,0,3,6,true); break;
					case 3: roll(front,8,5,2,left,8,5,2,back,0,3,6,right,8,5,2,true); break;
					case 5: roll(front,6,7,8,left,6,7,8,back,6,7,8,right,6,7,8,true); break;
					} break;
					case 3:
						switch (top) {
						case 0: roll(front,2,1,0,left,2,1,0,back,2,1,0,right,2,1,0,true); break;
						case 2: roll(front,0,3,6,left,2,1,0,back,8,5,2,right,6,7,8,true); break;
						case 4: roll(front,8,5,2,left,2,1,0,back,0,3,6,right,6,7,8,true); break;
						case 5: roll(front,6,7,8,left,6,7,8,back,6,7,8,right,6,7,8,true); break;
						} break;
						case 4:
							switch (top) {
							case 0: roll(front,2,1,0,left,2,1,0,back,2,1,0,right,2,1,0,true); break;
							case 1: roll(front,8,5,2,left,0,3,6,back,0,3,6,right,0,3,6,true); break;
							case 3: roll(front,0,3,6,left,8,5,2,back,8,5,2,right,8,5,2,true); break;
							case 5: roll(front,6,7,8,left,6,7,8,back,6,7,8,right,6,7,8,true); break;
							} break;
							case 5:
								switch (top) {
								case 1: roll(front,0,3,6,left,8,5,2,back,0,3,6,right,0,3,6,true); break;
								case 2: roll(front,2,1,0,left,8,5,2,back,6,7,8,right,0,3,6,true); break;
								case 3: roll(front,8,5,2,left,8,5,2,back,8,5,2,right,0,3,6,true); break;
								case 4: roll(front,6,7,8,left,8,5,2,back,2,1,0,right,0,3,6,true); break;
								}
		}
		transpose(top, true);
	}
	else if (command.compare("U'") == 0) {
		//System.out.println("Turn top face CCW");
		switch (front) {
		case 0:
			switch (top) {
			case 1: roll(front,0,3,6,left,0,3,6,back,0,3,6,right,8,5,2,false); break;
			case 2: roll(front,6,7,8,left,0,3,6,back,2,1,0,right,8,5,2,false); break;
			case 3: roll(front,8,5,2,left,0,3,6,back,8,5,2,right,8,5,2,false); break;
			case 4: roll(front,2,1,0,left,0,3,6,back,6,7,8,right,8,5,2,false); break;
			} break;
			case 1:
				switch (top) {
				case 0: roll(front,2,1,0,left,2,1,0,back,2,1,0,right,2,1,0,false); break;
				case 2: roll(front,8,5,2,left,6,7,8,back,0,3,6,right,2,1,0,false); break;
				case 4: roll(front,0,3,6,left,6,7,8,back,8,5,2,right,2,1,0,false); break;
				case 5: roll(front,6,7,8,left,6,7,8,back,6,7,8,right,6,7,8,false); break;
				} break;
				case 2:
					switch (top) {
					case 0: roll(front,2,1,0,left,2,1,0,back,2,1,0,right,2,1,0,false); break;
					case 1: roll(front,0,3,6,left,0,3,6,back,8,5,2,right,0,3,6,false); break;
					case 3: roll(front,8,5,2,left,8,5,2,back,0,3,6,right,8,5,2,false); break;
					case 5: roll(front,6,7,8,left,6,7,8,back,6,7,8,right,6,7,8,false); break;
					} break;
					case 3:
						switch (top) {
						case 0: roll(front,2,1,0,left,2,1,0,back,2,1,0,right,2,1,0,false); break;
						case 2: roll(front,0,3,6,left,2,1,0,back,8,5,2,right,6,7,8,false); break;
						case 4: roll(front,8,5,2,left,2,1,0,back,0,3,6,right,6,7,8,false); break;
						case 5: roll(front,6,7,8,left,6,7,8,back,6,7,8,right,6,7,8,false); break;
						} break;
						case 4:
							switch (top) {
							case 0: roll(front,2,1,0,left,2,1,0,back,2,1,0,right,2,1,0,false); break;
							case 1: roll(front,8,5,2,left,0,3,6,back,0,3,6,right,0,3,6,false); break;
							case 3: roll(front,0,3,6,left,8,5,2,back,8,5,2,right,8,5,2,false); break;
							case 5: roll(front,6,7,8,left,6,7,8,back,6,7,8,right,6,7,8,false); break;
							} break;
							case 5:
								switch (top) {
								case 1: roll(front,0,3,6,left,8,5,2,back,0,3,6,right,0,3,6,false); break;
								case 2: roll(front,2,1,0,left,8,5,2,back,6,7,8,right,0,3,6,false); break;
								case 3: roll(front,8,5,2,left,8,5,2,back,8,5,2,right,0,3,6,false); break;
								case 4: roll(front,6,7,8,left,8,5,2,back,2,1,0,right,0,3,6,false); break;
								}
		}
		transpose(top, false);
	}
	else if (command.compare("D") == 0) {
		// This sequence is written backwards. The argument for clockwise roll should be reversed
		//System.out.println("Turn bottom face CW");
		switch (front) {
		case 0:
			switch(top) {
			case 1: roll(front,2,5,8,left,2,5,8,back,2,5,8,right,6,3,0,false); break;
			case 2: roll(front,0,1,2,left,2,5,8,back,8,7,6,right,6,3,0,false); break;
			case 3: roll(front,6,3,0,left,2,5,8,back,6,3,0,right,6,3,0,false); break;
			case 4: roll(front,8,7,6,left,2,5,8,back,0,1,2,right,6,3,0,false); break;
			} break;
			case 1:
				switch(top) {
				case 0: roll(front,8,7,6,left,8,7,6,back,8,7,6,right,8,7,6,false); break;
				case 2: roll(front,6,3,0,left,0,1,2,back,2,5,8,right,8,7,6,false); break;
				case 4: roll(front,2,5,8,left,0,1,2,back,6,3,0,right,8,7,6,false); break;
				case 5: roll(front,0,1,2,left,0,1,2,back,0,1,2,right,0,1,2,false); break;
				} break;
				case 2:
					switch(top) {
					case 0: roll(front,8,7,6,left,8,7,6,back,8,7,6,right,8,7,6,false); break;
					case 1: roll(front,2,5,8,left,2,5,8,back,6,3,0,right,2,5,8,false); break;
					//case 3: roll(front,2,5,8,left,2,5,8,back,2,5,8,right,6,3,0,false); break;
					case 3: roll(front,6,3,0,left,6,3,0,back,2,5,8,right,6,3,0,false); break;
					case 5: roll(front,0,1,2,left,0,1,2,back,0,1,2,right,0,1,2,false); break;
					} break;
					case 3:
						switch(top) {
						case 0: roll(front,8,7,6,left,8,7,6,back,8,7,6,right,8,7,6,false); break;
						case 2: roll(front,2,5,8,left,8,7,6,back,6,3,0,right,0,1,2,false); break;
						case 4: roll(front,6,3,0,left,8,7,6,back,2,5,8,right,0,1,2,false); break;
						case 5: roll(front,0,1,2,left,0,1,2,back,0,1,2,right,0,1,2,false); break;
						} break;
						case 4:
							switch(top) {
							case 0: roll(front,8,7,6,left,8,7,6,back,8,7,6,right,8,7,6,false); break;
							case 1: roll(front,6,3,0,left,2,5,8,back,2,5,8,right,2,5,8,false); break;
							case 3: roll(front,2,5,8,left,6,3,0,back,6,3,0,right,6,3,0,false); break;
							case 5: roll(front,0,1,2,left,0,1,2,back,0,1,2,right,0,1,2,false); break;
							} break;
							case 5:
								switch(top) {
								case 1: roll(front,2,5,8,left,6,3,0,back,2,5,8,right,2,5,8,false); break;
								case 2: roll(front,8,7,6,left,6,3,0,back,0,1,2,right,2,5,8,false); break;
								case 3: roll(front,6,3,0,left,6,3,0,back,6,3,0,right,2,5,8,false); break;
								case 4: roll(front,0,1,2,left,6,3,0,back,8,7,6,right,2,5,8,false); break;
								}
		}
		transpose(down, true);
	}
	else if (command.compare("D'") == 0) {
		// This sequence is written backwards. The argument for clockwise roll should be reversed
		//System.out.println("Turn bottom face CCW");
		switch (front) {
		case 0:
			switch(top) {
			case 1: roll(front,2,5,8,left,2,5,8,back,2,5,8,right,6,3,0,true); break;
			case 2: roll(front,0,1,2,left,2,5,8,back,8,7,6,right,6,3,0,true); break;
			case 3: roll(front,6,3,0,left,2,5,8,back,6,3,0,right,6,3,0,true); break;
			case 4: roll(front,8,7,6,left,2,5,8,back,0,1,2,right,6,3,0,true); break;
			} break;
			case 1:
				switch(top) {
				case 0: roll(front,8,7,6,left,8,7,6,back,8,7,6,right,8,7,6,true); break;
				case 2: roll(front,6,3,0,left,0,1,2,back,2,5,8,right,8,7,6,true); break;
				case 4: roll(front,2,5,8,left,0,1,2,back,6,3,0,right,8,7,6,true); break;
				case 5: roll(front,0,1,2,left,0,1,2,back,0,1,2,right,0,1,2,true); break;
				} break;
				case 2:
					switch(top) {
					case 0: roll(front,8,7,6,left,8,7,6,back,8,7,6,right,8,7,6,true); break;
					case 1: roll(front,2,5,8,left,2,5,8,back,6,3,0,right,2,5,8,true); break;
					//case 3: roll(front,2,5,8,left,2,5,8,back,2,5,8,right,6,3,0,true); break;
					case 3: roll(front,6,3,0,left,6,3,0,back,2,5,8,right,6,3,0,true); break;
					case 5: roll(front,0,1,2,left,0,1,2,back,0,1,2,right,0,1,2,true); break;
					} break;
					case 3:
						switch(top) {
						case 0: roll(front,8,7,6,left,8,7,6,back,8,7,6,right,8,7,6,true); break;
						case 2: roll(front,2,5,8,left,8,7,6,back,6,3,0,right,0,1,2,true); break;
						case 4: roll(front,6,3,0,left,8,7,6,back,2,5,8,right,0,1,2,true); break;
						case 5: roll(front,0,1,2,left,0,1,2,back,0,1,2,right,0,1,2,true); break;
						} break;
						case 4:
							switch(top) {
							case 0: roll(front,8,7,6,left,8,7,6,back,8,7,6,right,8,7,6,true); break;
							case 1: roll(front,6,3,0,left,2,5,8,back,2,5,8,right,2,5,8,true); break;
							case 3: roll(front,2,5,8,left,6,3,0,back,6,3,0,right,6,3,0,true); break;
							case 5: roll(front,0,1,2,left,0,1,2,back,0,1,2,right,0,1,2,true); break;
							} break;
							case 5:
								switch(top) {
								case 1: roll(front,2,5,8,left,6,3,0,back,2,5,8,right,2,5,8,true); break;
								case 2: roll(front,8,7,6,left,6,3,0,back,0,1,2,right,2,5,8,true); break;
								case 3: roll(front,6,3,0,left,6,3,0,back,6,3,0,right,2,5,8,true); break;
								case 4: roll(front,0,1,2,left,6,3,0,back,8,7,6,right,2,5,8,true); break;
								}
		}
		transpose(down, false);
	}
	else if (command.compare("F") == 0) {
		//System.out.println("Turn front face CW");
		switch (front) {
		case 0: roll(top,2,1,0,right,2,1,0,down,2,1,0,left,2,1,0,true); break;
		case 1:
			switch (top) {
			case 0: roll(top,0,3,6,right,0,3,6,down,0,3,6,left,8,5,2,true); break;
			case 2: roll(top,0,3,6,right,0,3,6,down,8,5,2,left,0,3,6,true); break;
			case 4: roll(top,8,5,2,right,0,3,6,down,0,3,6,left,0,3,6,true); break;
			case 5: roll(top,0,3,6,right,8,5,2,down,0,3,6,left,0,3,6,true); break;
			} break;
			case 2:
				switch (top) {
				case 0: roll(top,6,7,8,right,0,3,6,down,2,1,0,left,8,5,2,true); break;
				case 1: roll(top,8,5,2,right,6,7,8,down,0,3,6,left,2,1,0,true); break;
				case 3: roll(top,0,3,6,right,2,1,0,down,8,5,2,left,6,7,8,true); break;
				case 5: roll(top,2,1,0,right,8,5,2,down,6,7,8,left,0,3,6,true); break;
				} break;
				case 3:
					switch (top) {
					case 0: roll(top,8,5,2,right,0,3,6,down,8,5,2,left,8,5,2,true); break;
					case 2: roll(top,8,5,2,right,8,5,2,down,0,3,6,left,8,5,2,true); break;
					case 4: roll(top,0,3,6,right,8,5,2,down,8,5,2,left,8,5,2,true); break;
					case 5: roll(top,8,5,2,right,8,5,2,down,8,5,2,left,0,3,6,true); break;
					} break;
					case 4:
						switch (top) {
						case 0: roll(top,2,1,0,right,0,3,6,down,6,7,8,left,8,5,2,true); break;
						case 1: roll(top,0,3,6,right,6,7,8,down,8,5,2,left,2,1,0,true); break;
						case 3: roll(top,8,5,2,right,2,1,0,down,0,3,6,left,6,7,8,true); break;
						case 5: roll(top,6,7,8,right,8,5,2,down,2,1,0,left,0,3,6,true); break;
						} break;
						case 5: roll(top,6,7,8,right,6,7,8,down,6,7,8,left,6,7,8,true); break;
		}

		transpose(front, true);
	}
	else if (command.compare("F'") == 0) {
		//System.out.println("Turn front face CCW");
		switch (front) {
		case 0: roll(top,2,1,0,right,2,1,0,down,2,1,0,left,2,1,0,false); break;
		case 1:
			switch (top) {
			case 0: roll(top,0,3,6,right,0,3,6,down,0,3,6,left,8,5,2,false); break;
			case 2: roll(top,0,3,6,right,0,3,6,down,8,5,2,left,0,3,6,false); break;
			case 4: roll(top,8,5,2,right,0,3,6,down,0,3,6,left,0,3,6,false); break;
			case 5: roll(top,0,3,6,right,8,5,2,down,0,3,6,left,0,3,6,false); break;
			} break;
			case 2:
				switch (top) {
				case 0: roll(top,6,7,8,right,0,3,6,down,2,1,0,left,8,5,2,false); break;
				case 1: roll(top,8,5,2,right,6,7,8,down,0,3,6,left,2,1,0,false); break;
				case 3: roll(top,0,3,6,right,2,1,0,down,8,5,2,left,6,7,8,false); break;
				case 5: roll(top,2,1,0,right,8,5,2,down,6,7,8,left,0,3,6,false); break;
				} break;
				case 3:
					switch (top) {
					case 0: roll(top,8,5,2,right,0,3,6,down,8,5,2,left,8,5,2,false); break;
					case 2: roll(top,8,5,2,right,8,5,2,down,0,3,6,left,8,5,2,false); break;
					case 4: roll(top,0,3,6,right,8,5,2,down,8,5,2,left,8,5,2,false); break;
					case 5: roll(top,8,5,2,right,8,5,2,down,8,5,2,left,0,3,6,false); break;
					} break;
					case 4:
						switch (top) {
						case 0: roll(top,2,1,0,right,0,3,6,down,6,7,8,left,8,5,2,false); break;
						case 1: roll(top,0,3,6,right,6,7,8,down,8,5,2,left,2,1,0,false); break;
						case 3: roll(top,8,5,2,right,2,1,0,down,0,3,6,left,6,7,8,false); break;
						case 5: roll(top,6,7,8,right,8,5,2,down,2,1,0,left,0,3,6,false); break;
						} break;
						case 5: roll(top,6,7,8,right,6,7,8,down,6,7,8,left,6,7,8,false); break;
		}

		transpose(front, false);
	}
	else if (command.compare("B") == 0) {
		//System.out.println("Turn back face CW");
		switch (front) {
		case 0: roll(top,6,7,8,left,6,7,8,down,6,7,8,right,6,7,8,true); break;
		case 1:
			switch (top) {
			case 0: roll(top,8,5,2,left,0,3,6,down,8,5,2,right,8,5,2,true); break;
			case 2: roll(top,8,5,2,left,8,5,2,down,0,3,6,right,8,5,2,true); break;
			case 4: roll(top,0,3,6,left,8,5,2,down,8,5,2,right,8,5,2,true); break;
			case 5: roll(top,8,5,2,left,0,3,6,down,8,5,2,right,8,5,2,true); break;
			} break;
			case 2:
				switch (top) {
				case 0: roll(top,2,1,0,left,0,3,6,down,6,7,8,right,8,5,2,true); break;
				case 1: roll(top,0,3,6,left,6,7,8,down,8,5,2,right,2,1,0,true); break;
				case 3: roll(top,8,5,2,left,2,1,0,down,0,3,6,right,6,7,8,true); break;
				case 5: roll(top,6,7,8,left,8,5,2,down,2,1,0,right,0,3,6,true); break;
				} break;
				case 3:
					switch (top) {
					case 0: roll(top,0,3,6,left,0,3,6,down,0,3,6,right,8,5,2,true); break;
					case 2: roll(top,0,3,6,left,0,3,6,down,8,5,2,right,0,3,6,true); break;
					case 4: roll(top,8,5,2,left,0,3,6,down,0,3,6,right,0,3,6,true); break;
					case 5: roll(top,0,3,6,left,8,5,2,down,0,3,6,right,0,3,6,true); break;
					} break;
					case 4:
						switch (top) {
						case 0: roll(top,6,7,8,left,0,3,6,down,2,1,0,right,8,5,2,true); break;
						case 1: roll(top,8,5,2,left,6,7,8,down,0,3,6,right,2,1,0,true); break;
						case 3: roll(top,0,3,6,left,2,1,0,down,8,5,2,right,6,7,8,true); break;
						case 5: roll(top,2,1,0,left,8,5,2,down,6,7,8,right,0,3,6,true); break;
						} break;
						case 5: roll(top,2,1,0,left,2,1,0,down,2,1,0,right,2,1,0,true); break;
		}
		transpose(back, true);
	}
	else if (command.compare("B'") == 0) {
		//System.out.println("Turn back face CCW");
		switch (front) {
		case 0: roll(top,6,7,8,left,6,7,8,down,6,7,8,right,6,7,8,false); break;
		case 1:
			switch (top) {
			case 0: roll(top,8,5,2,left,0,3,6,down,8,5,2,right,8,5,2,false); break;
			case 2: roll(top,8,5,2,left,8,5,2,down,0,3,6,right,8,5,2,false); break;
			case 4: roll(top,0,3,6,left,8,5,2,down,8,5,2,right,8,5,2,false); break;
			case 5: roll(top,8,5,2,left,0,3,6,down,8,5,2,right,8,5,2,false); break;
			} break;
			case 2:
				switch (top) {
				case 0: roll(top,2,1,0,left,0,3,6,down,6,7,8,right,8,5,2,false); break;
				case 1: roll(top,0,3,6,left,6,7,8,down,8,5,2,right,2,1,0,false); break;
				case 3: roll(top,8,5,2,left,2,1,0,down,0,3,6,right,6,7,8,false); break;
				case 5: roll(top,6,7,8,left,8,5,2,down,2,1,0,right,0,3,6,false); break;
				} break;
				case 3:
					switch (top) {
					case 0: roll(top,0,3,6,left,0,3,6,down,0,3,6,right,8,5,2,false); break;
					case 2: roll(top,0,3,6,left,0,3,6,down,8,5,2,right,0,3,6,false); break;
					case 4: roll(top,8,5,2,left,0,3,6,down,0,3,6,right,0,3,6,false); break;
					case 5: roll(top,0,3,6,left,8,5,2,down,0,3,6,right,0,3,6,false); break;
					} break;
					case 4:
						switch (top) {
						case 0: roll(top,6,7,8,left,0,3,6,down,2,1,0,right,8,5,2,false); break;
						case 1: roll(top,8,5,2,left,6,7,8,down,0,3,6,right,2,1,0,false); break;
						case 3: roll(top,0,3,6,left,2,1,0,down,8,5,2,right,6,7,8,false); break;
						case 5: roll(top,2,1,0,left,8,5,2,down,6,7,8,right,0,3,6,false); break;
						} break;
						case 5: roll(top,2,1,0,left,2,1,0,down,2,1,0,right,2,1,0,false); break;
		}
		transpose(back, false);
	}
	else if (command.compare("R") == 0) {
		//System.out.println("Turn right face CW");
		switch (front) {
		case 0:
			switch (top) {
			case 1: roll(top,0,3,6,back,6,7,8,down,8,5,2,front,2,1,0,true); break;
			case 2: roll(top,0,3,6,back,0,3,6,down,8,5,2,front,0,3,6,true); break;
			case 3: roll(top,0,3,6,back,2,1,0,down,8,5,2,front,6,7,8,true); break;
			case 4: roll(top,0,3,6,back,8,5,2,down,8,5,2,front,8,5,2,true); break;
			} break;
			case 1:
				switch (top) {
				case 0: roll(top,6,7,8,back,0,3,6,down,2,1,0,front,8,5,2,true); break;
				case 2: roll(top,6,7,8,back,6,7,8,down,6,7,8,front,6,7,8,true); break;
				case 4: roll(top,2,1,0,back,2,1,0,down,2,1,0,front,2,1,0,true); break;
				case 5: roll(top,6,7,8,back,8,5,2,down,2,1,0,front,0,3,6,true); break;
				} break;
				case 2:
					switch (top) {
					case 0: roll(top,8,5,2,back,0,3,6,down,8,5,2,front,8,5,2,true); break;
					case 1: roll(top,2,1,0,back,2,1,0,down,2,1,0,front,2,1,0,true); break;
					case 3: roll(top,6,7,8,back,6,7,8,down,6,7,8,front,6,7,8,true); break;
					case 5: roll(top,0,3,6,back,8,5,2,down,0,3,6,front,0,3,6,true); break;
					} break;
					case 3:
						switch (top) {
						case 0: roll(top,2,1,0,back,0,3,6,down,6,7,8,front,8,5,2,true); break;
						case 2: roll(top,2,1,0,back,2,1,0,down,2,1,0,front,2,1,0,true); break;
						case 4: roll(top,6,7,8,back,6,7,8,down,6,7,8,front,6,7,8,true); break;
						case 5: roll(top,2,1,0,back,8,5,2,down,6,7,8,front,0,3,6,true); break;
						} break;
						case 4:
							switch (top) {
							case 0: roll(top,0,3,6,back,0,3,6,down,0,3,6,front,8,5,2,true); break;
							case 1: roll(top,6,7,8,back,6,7,8,down,6,7,8,front,6,7,8,true); break;
							case 3: roll(top,2,1,0,back,2,1,0,down,2,1,0,front,2,1,0,true); break;
							case 5: roll(top,8,5,2,back,8,5,2,down,8,5,2,front,0,3,6,true); break;
							} break;
							case 5:
								switch (top) {
								case 1: roll(top,8,5,2,back,6,7,8,down,0,3,6,front,2,1,0,true); break;
								case 2: roll(top,8,5,2,back,8,5,2,down,0,3,6,front,8,5,2,true); break;
								case 3: roll(top,8,5,2,back,2,1,0,down,0,3,6,front,6,7,8,true); break;
								case 4: roll(top,8,5,2,back,0,3,6,down,0,3,6,front,0,3,6,true); break;
								} break;
		}
		transpose(right, true);
	}
	else if (command.compare("R'") == 0) {
		//System.out.println("Turn right face CCW");
		switch (front) {
		case 0:
			switch (top) {
			case 1: roll(top,0,3,6,back,6,7,8,down,8,5,2,front,2,1,0,false); break;
			case 2: roll(top,0,3,6,back,0,3,6,down,8,5,2,front,0,3,6,false); break;
			case 3: roll(top,0,3,6,back,2,1,0,down,8,5,2,front,6,7,8,false); break;
			case 4: roll(top,0,3,6,back,8,5,2,down,8,5,2,front,8,5,2,false); break;
			} break;
			case 1:
				switch (top) {
				case 0: roll(top,6,7,8,back,0,3,6,down,2,1,0,front,8,5,2,false); break;
				case 2: roll(top,6,7,8,back,6,7,8,down,6,7,8,front,6,7,8,false); break;
				case 4: roll(top,2,1,0,back,2,1,0,down,2,1,0,front,2,1,0,false); break;
				case 5: roll(top,6,7,8,back,8,5,2,down,2,1,0,front,0,3,6,false); break;
				} break;
				case 2:
					switch (top) {
					case 0: roll(top,8,5,2,back,0,3,6,down,8,5,2,front,8,5,2,false); break;
					case 1: roll(top,2,1,0,back,2,1,0,down,2,1,0,front,2,1,0,false); break;
					case 3: roll(top,6,7,8,back,6,7,8,down,6,7,8,front,6,7,8,false); break;
					case 5: roll(top,0,3,6,back,8,5,2,down,0,3,6,front,0,3,6,false); break;
					} break;
					case 3:
						switch (top) {
						case 0: roll(top,2,1,0,back,0,3,6,down,6,7,8,front,8,5,2,false); break;
						case 2: roll(top,2,1,0,back,2,1,0,down,2,1,0,front,2,1,0,false); break;
						case 4: roll(top,6,7,8,back,6,7,8,down,6,7,8,front,6,7,8,false); break;
						case 5: roll(top,2,1,0,back,8,5,2,down,6,7,8,front,0,3,6,false); break;
						} break;
						case 4:
							switch (top) {
							case 0: roll(top,0,3,6,back,0,3,6,down,0,3,6,front,8,5,2,false); break;
							case 1: roll(top,6,7,8,back,6,7,8,down,6,7,8,front,6,7,8,false); break;
							case 3: roll(top,2,1,0,back,2,1,0,down,2,1,0,front,2,1,0,false); break;
							case 5: roll(top,8,5,2,back,8,5,2,down,8,5,2,front,0,3,6,false); break;
							} break;
							case 5:
								switch (top) {
								case 1: roll(top,8,5,2,back,6,7,8,down,0,3,6,front,2,1,0,false); break;
								case 2: roll(top,8,5,2,back,8,5,2,down,0,3,6,front,8,5,2,false); break;
								case 3: roll(top,8,5,2,back,2,1,0,down,0,3,6,front,6,7,8,false); break;
								case 4: roll(top,8,5,2,back,0,3,6,down,0,3,6,front,0,3,6,false); break;
								} break;
		}
		transpose(right, false);
	}
	else if (command.compare("L") == 0) {
		// This action is also written backwards.
		//System.out.println("Turn left face CW");
		switch (front) {
		case 0:
			switch (top) {
			case 1: roll(top,2,5,8,back,0,1,2,down,6,3,0,front,8,7,6,false); break;
			case 2: roll(top,2,5,8,back,2,5,8,down,6,3,0,front,2,5,8,false); break;
			case 3: roll(top,2,5,8,back,8,7,6,down,6,3,0,front,0,1,2,false); break;
			case 4: roll(top,2,5,8,back,6,3,0,down,6,3,0,front,6,3,0,false); break;
			} break;
			case 1:
				switch (top) {
				case 0: roll(top,0,1,2,back,2,5,8,down,8,7,6,front,6,3,0,false); break;
				case 2: roll(top,0,1,2,back,0,1,2,down,0,1,2,front,0,1,2,false); break;
				case 4: roll(top,8,7,6,back,8,7,6,down,8,7,6,front,8,7,6,false); break;
				case 5: roll(top,0,1,2,back,6,3,0,down,8,7,6,front,2,5,8,false); break;
				} break;
				case 2:
					switch (top) {
					case 0: roll(top,6,3,0,back,2,5,8,down,6,3,0,front,6,3,0,false); break;
					case 1: roll(top,8,7,6,back,8,7,6,down,8,7,6,front,8,7,6,false); break;
					case 3: roll(top,0,1,2,back,0,1,2,down,0,1,2,front,0,1,2,false); break;
					case 5: roll(top,2,5,8,back,6,3,0,down,2,5,8,front,2,5,8,false); break;
					} break;
					case 3:
						switch (top) {
						case 0: roll(top,8,7,6,back,2,5,8,down,0,1,2,front,6,3,0,false); break;
						case 2: roll(top,8,7,6,back,8,7,6,down,8,7,6,front,8,7,6,false); break;
						case 4: roll(top,0,1,2,back,0,1,2,down,0,1,2,front,0,1,2,false); break;
						case 5: roll(top,8,7,6,back,6,3,0,down,0,1,2,front,2,5,8,false); break;
						} break;
						case 4:
							switch (top) {
							case 0: roll(top,2,5,8,back,2,5,8,down,2,5,8,front,6,3,0,false); break;
							case 1: roll(top,0,1,2,back,0,1,2,down,0,1,2,front,0,1,2,false); break;
							case 3: roll(top,8,7,6,back,8,7,6,down,8,7,6,front,8,7,6,false); break;
							case 5: roll(top,6,3,0,back,6,3,0,down,6,3,0,front,2,5,8,false); break;
							} break;
							case 5:
								switch (top) {
								case 1: roll(top,6,3,0,back,0,1,2,down,2,5,8,front,8,7,6,false); break;
								case 2: roll(top,6,3,0,back,6,3,0,down,2,5,8,front,6,3,0,false); break;
								case 3: roll(top,6,3,0,back,8,7,6,down,2,5,8,front,0,1,2,false); break;
								case 4: roll(top,6,3,0,back,2,5,8,down,2,5,8,front,2,5,8,false); break;
								} break;
		}
		transpose(left, true);
	}
	else if (command.compare("L'") == 0) {
		//System.out.println("Turn left face CCW");
		switch (front) {
		case 0:
			switch (top) {
			case 1: roll(top,2,5,8,back,0,1,2,down,6,3,0,front,8,7,6,true); break;
			case 2: roll(top,2,5,8,back,2,5,8,down,6,3,0,front,2,5,8,true); break;
			case 3: roll(top,2,5,8,back,8,7,6,down,6,3,0,front,0,1,2,true); break;
			case 4: roll(top,2,5,8,back,6,3,0,down,6,3,0,front,6,3,0,true); break;
			} break;
			case 1:
				switch (top) {
				case 0: roll(top,0,1,2,back,2,5,8,down,8,7,6,front,6,3,0,true); break;
				case 2: roll(top,0,1,2,back,0,1,2,down,0,1,2,front,0,1,2,true); break;
				case 4: roll(top,8,7,6,back,8,7,6,down,8,7,6,front,8,7,6,true); break;
				case 5: roll(top,0,1,2,back,6,3,0,down,8,7,6,front,2,5,8,true); break;
				} break;
				case 2:
					switch (top) {
					case 0: roll(top,6,3,0,back,2,5,8,down,6,3,0,front,6,3,0,true); break;
					case 1: roll(top,8,7,6,back,8,7,6,down,8,7,6,front,8,7,6,true); break;
					case 3: roll(top,0,1,2,back,0,1,2,down,0,1,2,front,0,1,2,true); break;
					case 5: roll(top,2,5,8,back,6,3,0,down,2,5,8,front,2,5,8,true); break;
					} break;
					case 3:
						switch (top) {
						case 0: roll(top,8,7,6,back,2,5,8,down,0,1,2,front,6,3,0,true); break;
						case 2: roll(top,8,7,6,back,8,7,6,down,8,7,6,front,8,7,6,true); break;
						case 4: roll(top,0,1,2,back,0,1,2,down,0,1,2,front,0,1,2,true); break;
						case 5: roll(top,8,7,6,back,6,3,0,down,0,1,2,front,2,5,8,true); break;
						} break;
						case 4:
							switch (top) {
							case 0: roll(top,2,5,8,back,2,5,8,down,2,5,8,front,6,3,0,true); break;
							case 1: roll(top,0,1,2,back,0,1,2,down,0,1,2,front,0,1,2,true); break;
							case 3: roll(top,8,7,6,back,8,7,6,down,8,7,6,front,8,7,6,true); break;
							case 5: roll(top,6,3,0,back,6,3,0,down,6,3,0,front,2,5,8,true); break;
							} break;
							case 5:
								switch (top) {
								case 1: roll(top,6,3,0,back,0,1,2,down,2,5,8,front,8,7,6,true); break;
								case 2: roll(top,6,3,0,back,6,3,0,down,2,5,8,front,6,3,0,true); break;
								case 3: roll(top,6,3,0,back,8,7,6,down,2,5,8,front,0,1,2,true); break;
								case 4: roll(top,6,3,0,back,2,5,8,down,2,5,8,front,2,5,8,true); break;
								} break;
		}
		transpose(left, false);
	}
	else {
		cout << "ERR!" << endl;
	}
}

rubik::~rubik() {
	// TODO Auto-generated destructor stub
}
