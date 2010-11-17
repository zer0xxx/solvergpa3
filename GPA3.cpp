#include <QtCore>
#include <QCoreApplication>
#include <iostream>
#include "rubik.h"
#include "solver.h"

using namespace std;

int main(int argc, char *argv[])
{
	solver* s;
	if (argc > 1) {
		if (argc > 2) {
			s = new solver(string(argv[1]), argv[2]);
			// cout << argv[2] << endl;
		}
		else {
			s = new solver(string(argv[1]), "0");
		}
		s->solve();
	}
	else {
		cout << "Cube state required" << endl;
	}
    //QCoreApplication a(argc, argv);
	
    //return a.exec();
	return 0;
}
