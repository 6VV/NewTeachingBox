#include "stdafx.h"
#include "ToolSysWidgetOrigin.h"
#include "CoordinateSystemTeachInfo.h"



ToolSysWidgetOrigin::ToolSysWidgetOrigin(QStackedWidget* parent/*=nullptr*/)
	:SystemDialogWidgetParent(parent)
{

}

void ToolSysWidgetOrigin::showEvent(QShowEvent *event)
{
	SystemDialogWidgetParent::showEvent(event);

	InitCoorState();
}

QWidget* ToolSysWidgetOrigin::MainWidget()
{
	QGroupBox* box = new QGroupBox(tr("Select teach method"), this);

	QVBoxLayout* layout = new QVBoxLayout(box);

	auto btnFourPointKeepOrientation = new QRadioButton(tr("4 points XYZ"), box);

	layout->addStretch(1);
	layout->addWidget(new QLabel(tr("Keep orientation")));
	layout->addWidget(btnFourPointKeepOrientation);
	layout->addStretch(1);

	btnFourPointKeepOrientation->setChecked(true);

	return box;
}

QString ToolSysWidgetOrigin::IllustrationPixmapPath()
{
	return ":/new/image/Resources/Image/tool_sys_illustration.png";
}

void ToolSysWidgetOrigin::InitCoorState()
{
	m_coorInfo->method = CoordinateSystemTeachInfo::TOOL_SYS_FOUR_POINTS;
	m_coorInfo->values = {};
}
