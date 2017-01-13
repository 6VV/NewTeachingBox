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


int LabelWithBorder::GetBorderWidth() const
{
	return BORDER_WIDTH;
}

void LabelWithBorder::Init()
{
	QLabel::setStyleSheet(ORIGIN_STYLE_SHEET);
	this->setAlignment(Qt::AlignCenter);
}
