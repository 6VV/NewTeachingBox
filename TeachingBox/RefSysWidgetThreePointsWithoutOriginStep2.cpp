#include "stdafx.h"
#include "RefSysWidgetThreePointsWithoutOriginStep2.h"
#include "Button.h"
#include "CoordinateSystemTeachInfo.h"


RefSysWidgetThreePointsWithoutOriginStep2::RefSysWidgetThreePointsWithoutOriginStep2(QStackedWidget* parent)
	:SystemDialogWidgetParent(parent)
{

}

QWidget* RefSysWidgetThreePointsWithoutOriginStep2::MainWidget()
{
	QGroupBox* groupBox = new QGroupBox(tr("Second point on axis"), this);

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

QString RefSysWidgetThreePointsWithoutOriginStep2::IllustrationPixmapPath()
{
	return ":/new/image/Resources/Image/ref_sys_3_points_without_origin_step2.png";
}

void RefSysWidgetThreePointsWithoutOriginStep2::OnReseivePose(const tPoseEuler& pose/* = */)
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
