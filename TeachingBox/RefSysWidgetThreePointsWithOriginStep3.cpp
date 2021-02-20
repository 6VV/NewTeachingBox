#include "stdafx.h"
#include "RefSysWidgetThreePointsWithOriginStep3.h"
#include "Button.h"
#include "CoordinateSystemTeachInfo.h"


RefSysWidgetThreePointsWithOriginStep3::RefSysWidgetThreePointsWithOriginStep3(QStackedWidget* parent)
	:SystemDialogWidgetParent(parent)
{

}

QWidget* RefSysWidgetThreePointsWithOriginStep3::MainWidget()
{
	QGroupBox* groupBox = new QGroupBox(tr("Plane Point"), this);

	QVBoxLayout* layout = new QVBoxLayout(groupBox);

	auto btnXY = new QRadioButton("XY", this);
	auto btnZX = new QRadioButton("ZX", this);
	auto btnYZ = new QRadioButton("YZ", this);
	m_btnGroup = new QButtonGroup(this);
	m_btnGroup->addButton(btnXY,CoordinateSystemTeachInfo::XY);
	m_btnGroup->addButton(btnZX, CoordinateSystemTeachInfo::ZX);
	m_btnGroup->addButton(btnYZ, CoordinateSystemTeachInfo::YZ);

	connect(m_btnGroup, static_cast<void (QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), [this](int id){
		if (IsTeached())
		{
			m_coorInfo->UpdateOrientation(static_cast<CoordinateSystemTeachInfo::Orientation>(id));
		}
	});

	QHBoxLayout* radioLayout = new QHBoxLayout(this);
	radioLayout->addWidget(btnXY);
	radioLayout->addWidget(btnZX);
	radioLayout->addWidget(btnYZ);

	btnXY->setChecked(true);

	layout->addLayout(radioLayout);
	layout->addWidget(PointWidgetXYZ());

	auto teachButton = new Button(tr("Teach"), this);
	connect(teachButton, &Button::clicked, [this]{
		GetRemotePose();
	});

	layout->addWidget(teachButton);

	layout->setStretch(1, 1);

	return groupBox;
}

QString RefSysWidgetThreePointsWithOriginStep3::IllustrationPixmapPath()
{
	return ":/new/image/Resources/Image/ref_sys_3_points_with_origin_step3.png";
}

void RefSysWidgetThreePointsWithOriginStep3::OnReseivePose(const tPoseEuler& pose/* = */)
{
	SystemDialogWidgetParent::OnReseivePose(pose);

	if (IsTeached())
	{
		m_coorInfo->UpdatePoseEuler(pose);
	}
	else
	{
		m_coorInfo->AddCoorSysInfo({ static_cast<CoordinateSystemTeachInfo::Orientation>(m_btnGroup->checkedId()), std::make_shared<tPoseEuler>(pose) });
	}

	UpdateButtonState();
}
