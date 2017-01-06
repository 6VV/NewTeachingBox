#include "stdafx.h"
#include "KeyboardLineEdit.h"



KeyboardLineEidt::KeyboardLineEidt(QWidget* parent/*=nullptr*/)
	:QLineEdit(parent)
{

}

void KeyboardLineEidt::OnInsert(const QString& text)
{
	insert(text);
}




