#ifndef _WARNING_LIGHT_H_
#define _WARNING_LIGHT_H_

#include "QWidget"
#include "QColor"

class WarningLight:public QWidget
{
	Q_OBJECT
private:
	static const QColor COLOR_ON;
	static const QColor COLOR_OFF;

public:
	WarningLight(QWidget* parent=0);

	void LightOn();
	void LightOff();

private:
	void paintEvent(QPaintEvent*) override;
	QColor m_color = COLOR_OFF;
};

#endif