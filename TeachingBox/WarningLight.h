#ifndef _WARNING_LIGHT_H_
#define _WARNING_LIGHT_H_

#include "QWidget"
#include "QColor"

class WarningLight:public QWidget
{
	Q_OBJECT
private:
	static const int DIAMETER = 30;

public:
	WarningLight(QWidget* parent=0);

	void Warn();
	void Normal();

private:
	void paintEvent(QPaintEvent*) override;
	QColor m_color = Qt::green;
};

#endif