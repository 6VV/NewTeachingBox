#include "stdafx.h"
#include "RefSysWidgetThreePointsWithOriginStep1.h"
#include "Button.h"
#include "CoordinateSystemTeachInfo.h"


RefSysWidgetThreePointsWithOriginStep1::RefSysWidgetThreePointsWithOriginStep1(QStackedWidget* parent)
	:SystemDialogWidgetParent(parent)
{

}

QWidget* RefSysWidgetThreePointsWithOriginStep1::MainWidget()
{
	QGroupBox* groupBox = new QGroupBox(tr("Origin Point"), this);

	QVBoxLayout* layout = new QVBoxLayout(groupBox);
	layout->addWidget(PointWidgetXYZ());

	auto teachButton = new Button(tr("Teach"), this);
	connect(teachButton, &Button::clicked, [this]{
		GetRemotePose();
	});

	layout->addWidget(teachButton);

	layout->setStretch(0, 1);

	return groupBox;
}

QString RefSysWidgetThreePointsWithOriginStep1::IllustrationPixmapPath()
{
	return ":/new/image/Resources/Image/ref_sys_3_points_with_origin_step1.png";
}

void RefSysWidgetThreePointsWithOriginStep1::OnReseivePose(const tPoseEuler& pose/* = */)
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

