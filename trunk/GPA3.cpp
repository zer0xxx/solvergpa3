#include <QtCore>
#include <QCoreApplication>
#include <iostream>
#include "rubik.h"

using namespace std;

int main(int argc, char *argv[])
{
	string state;
	string commands;
	if (argc > 1) {
		rubik* cube = new rubik();
		cube->setState(argv[1]);
		cube->process("B'");
		cube->process("R");
		cube->process("F");
		cube->process("U");
		cube->process("L");
		cube->process("X");
		cube->process("D");
		cube->display();
		if (argc > 2) {
			commands = argv[1];
		}
	}
	else {
		cout << "Cube state required" << endl;
	}
    //QCoreApplication a(argc, argv);
	
    //return a.exec();
	return 0;
}
