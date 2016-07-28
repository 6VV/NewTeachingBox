#include "stdafx.h"
#include "WarningLight.h"
#include "QPainter"
#include "QPen"

const QColor WarningLight::COLOR_ON = Qt::red;

const QColor WarningLight::COLOR_OFF = Qt::black;

WarningLight::WarningLight(QWidget* parent/*=0*/)
	:QWidget(parent)
{
	update();
}

void WarningLight::LightOn()
{
	m_color = COLOR_ON;
	update();
}

void WarningLight::LightOff()
{
	m_color = COLOR_OFF;
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

