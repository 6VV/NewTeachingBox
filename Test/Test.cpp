#include "Test.h"
#include "..\QScintilla_gpl-2.9.3\Qt4Qt5\Qsci\qsciscintilla.h"

Test::Test(QWidget *parent)
	: QMainWindow(parent)
{
	setCentralWidget(new QsciScintilla());
}
