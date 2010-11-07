/*
 * rubik.h
 *
 *  Created on: Nov 7, 2010
 *      Author: gbudiman
 */

#ifndef RUBIK_H_
#define RUBIK_H_
#include <iostream>
#include <string.h>
using namespace std;

class rubik {
public:
	rubik();
	void reset();
	string display();
	void transpose(int face, bool clockwise);
	void setState(string s);
	void roll(int f1, int c11, int c12, int c13,
            int f2, int c21, int c22, int c23,
            int f3, int c31, int c32, int c33,
            int f4, int c41, int c42, int c43, bool clockwise);
	void process(string c);

	virtual ~rubik();

	char cube[6][9];
	int topCells[9];
	int leftCells[9];
	int frontCells[9];
	int rightCells[9];
	int backCells[9];
	int downCells[9];

	int top;
	int left;
	int front;
	int right;
	int back;
	int down;
};

#endif /* RUBIK_H_ */
