#include "stdafx.h"
#include <QtWidgets/QApplication>
#include "SciCodeEditor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SciCodeEditor w;
    w.show();
    return a.exec();
}
