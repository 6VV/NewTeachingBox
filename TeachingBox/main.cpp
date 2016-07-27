#include "stdafx.h"
#include "TeachingBox.h"
#include <QtWidgets/QApplication>
#include "QTranslator"


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QTranslator* translator = new QTranslator;
	translator->load(":/TeachingBox/teachingbox_zh.qm");
	a.installTranslator(translator);

	TeachingBox w;
	w.show();
	return a.exec();
}

