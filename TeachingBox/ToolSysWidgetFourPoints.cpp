#include "stdafx.h"
#include "ToolSysWidgetFourPoints.h"
#include "CoordinateSystemTeachInfo.h"
#include "Button.h"



ToolSysWidgetFourPoints::ToolSysWidgetFourPoints(QStackedWidget* parent, const QString& pixmapPath/*=""*/, const QString& title/*=""*/)
	:SystemDialogWidgetParent(parent)
	, m_pixmapPath(pixmapPath)
	, m_title(title)
{

}

QWidget* ToolSysWidgetFourPoints::MainWidget()
{
	QGroupBox* box = new QGroupBox(m_title);
	QVBoxLayout* layout = new QVBoxLayout(box);
	
	auto btnTeach = new QPushButton(tr("Teach"), box);

	layout->addWidget(PointWidgetXYZABC());
	layout->addWidget(btnTeach);

	layout->setStretch(0, 1);

	connect(btnTeach, &Button::clicked, [this]{
		GetRemotePose();
	});

	return box;
}

QString ToolSysWidgetFourPoints::IllustrationPixmapPath()
{
	return m_pixmapPath;
}

void ToolSysWidgetFourPoints::OnReseivePose(const tPoseEuler& pose/* = */)
{
	SystemDialogWidgetParent::OnReseivePose(pose);

	if (IsTeached())
	{
		m_coorInfo->UpdatePoseEuler(pose);
	}
	else
	{
		m_coorInfo->AddPoseEuler(pose);
	}

	UpdateButtonState();
}

