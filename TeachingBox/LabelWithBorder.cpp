#include "stdafx.h"
#include "LabelWithBorder.h"



LabelWithBorder::LabelWithBorder(QWidget* parent /*= 0*/)
	:QLabel(parent)
{
	Init();
}

LabelWithBorder::LabelWithBorder(const QString& text, QWidget* parent /*= 0*/)
	: QLabel(text, parent)
{
	Init();
}


void LabelWithBorder::Init()
{
	this->setStyleSheet("border: 1px groove gray; background-color: rgba(255, 193, 245, 0%); ");
	this->setAlignment(Qt::AlignCenter);
}
