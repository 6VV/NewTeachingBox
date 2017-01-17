#include "stdafx.h"
#include "WidgetWithBorderAndIcon.h"



WidgetWithBorderAndIcon::WidgetWithBorderAndIcon(QWidget* widget, const QString& iconPath, QWidget* parent /*= 0*/)
	:LabelWithBorder(parent)
	, m_widget(widget)
	, m_icon(new QLabel(this))
	, m_iconPath(iconPath)
{
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->setSpacing(0);
	layout->setMargin(0);

	m_icon->setPixmap(QPixmap(iconPath).scaledToHeight(m_icon->height()));
	widget->setFixedHeight(this->height());

	layout->addWidget(m_icon);
	layout->addWidget(widget);
	layout->setStretch(1, 1);
}

void WidgetWithBorderAndIcon::showEvent(QShowEvent *)
{
	m_icon->setPixmap(QPixmap(m_iconPath).scaledToHeight(m_icon->height()));
	m_widget->setFixedHeight(this->height());
}

void WidgetWithBorderAndIcon::AddStyleSheet(const QString& styleSheet)
{
	setStyleSheet(ORIGIN_STYLE_SHEET + styleSheet);
}

void WidgetWithBorderAndIcon::SetIcon(const QString& iconPath, int height)
{
	m_iconPath = iconPath;
	if (height==0)
	{
		m_icon->setPixmap(QPixmap(iconPath).scaledToHeight(m_icon->height()));
	}
	else
	{
		m_icon->setPixmap(QPixmap(iconPath).scaledToHeight(height));
	}
}
