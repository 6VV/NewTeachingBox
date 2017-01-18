#include "stdafx.h"
#include "RefSysWidgetOnePointKeepOrientation.h"
#include "Button.h"
#include "CoordinateSystemTeachInfo.h"


RefSysWidgetOnePointKeepOrientation::RefSysWidgetOnePointKeepOrientation(QStackedWidget* parent)
	:SystemDialogWidgetParent(parent)
{

}

QWidget* RefSysWidgetOnePointKeepOrientation::MainWidget()
{
	QGroupBox* groupBox = new QGroupBox(tr("Origin Point"), this);

	QVBoxLayout* layout = new QVBoxLayout(groupBox);

	auto teachButton = new Button(tr("Teach"), this);

	layout->addWidget(PointWidgetXYZ());
	layout->addWidget(teachButton);

	layout->setStretch(0, 1);

	connect(teachButton, &Button::clicked, [this]{
		GetRemotePose();
	});

	return groupBox;
}

QString RefSysWidgetOnePointKeepOrientation::IllustrationPixmapPath()
{
	return ":/new/image/Resources/Image/ref_sys_1_points_keep_origin_step1.png";
}

void RefSysWidgetOnePointKeepOrientation::OnReseivePose(const tPoseEuler& pose/* = */)
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
