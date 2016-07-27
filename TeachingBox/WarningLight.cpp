#include "stdafx.h"
#include "WarningLight.h"
#include "QPainter"
#include "QPen"



WarningLight::WarningLight(QWidget* parent/*=0*/)
	:QWidget(parent)
{
	update();
}

void WarningLight::Warn()
{
	m_color = Qt::red;
	update();
}

void WarningLight::Normal()
{
	m_color = Qt::green;
	update();
}

void WarningLight::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	QPen pen;
	pen.setColor(m_color);
	pen.setWidth(1);
	painter.setPen(pen);
	painter.setBrush(QBrush(m_color));
	painter.drawEllipse(QRect(0, 0, std::min<int>(width(), height())-2, std::min<int>(width(), height())-2));
}

