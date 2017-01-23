#include "stdafx.h"
#include "InternationalWidget.h"
#include <QEvent>



InternationalWidget::InternationalWidget(QWidget* parent/*=0*/)
	:QWidget(parent)
{

}

InternationalWidget::~InternationalWidget()
{

}

void InternationalWidget::changeEvent(QEvent *e)
{
	QWidget::changeEvent(e);

	switch (e->type())
	{
	case QEvent::LanguageChange:{
		UpdateText();
	}break;
	default:
		break;
	}
}
