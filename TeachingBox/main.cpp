#include "stdafx.h"
#include "teachingbox.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TeachingBox w;
	w.show();
	return a.exec();
}
