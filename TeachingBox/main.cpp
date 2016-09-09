#include "stdafx.h"
#include "TeachingBox.h"
#include <QtWidgets/QApplication>
#include "QTranslator"


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	TeachingBox w;
	w.show();

	return a.exec();
}

