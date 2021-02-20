#include "stdafx.h"
#include "RefSysWidgetOrigin.h"
#include "CoordinateSystemTeachInfo.h"




RefSysWidgetOrigin::RefSysWidgetOrigin(SystemDialogWidgetParent* threePointsWithOrigin,
	SystemDialogWidgetParent* threePointsWithoutOrigin, SystemDialogWidgetParent* onePointKeepOrientation, QStackedWidget* parent /*= nullptr*/)
	:SystemDialogWidgetParent(parent)
	, m_threePointsWithOrigin(threePointsWithOrigin)
	, m_threePointsWithoutOrigin(threePointsWithoutOrigin)
	, m_onePointKeepOrientation(onePointKeepOrientation)
{

}

QWidget* RefSysWidgetOrigin::MainWidget()
{
	QWidget* widget = new QWidget(this);

	QVBoxLayout* layout = new QVBoxLayout(widget);

	layout->addWidget(GetTeachToolWidget());
	layout->addWidget(GetTeachMethodWidget());

	return widget;
}

QString RefSysWidgetOrigin::IllustrationPixmapPath()
{
	return ":/new/image/Resources/Image/ref_sys_illustration.png";
}

void RefSysWidgetOrigin::OnReseivePose(const tPoseEuler&/* = */)
{
}

void RefSysWidgetOrigin::showEvent(QShowEvent *event)
{
	SystemDialogWidgetParent::showEvent(event);

	InitCoorInfo();

	qDebug() << "show event";
}

QWidget* RefSysWidgetOrigin::GetTeachMethodWidget()
{
	QGroupBox* box = new QGroupBox(tr("Select teach method"), this);

	QGridLayout* layout = new QGridLayout(box);

	QRadioButton* threePointsWithOriginButton = new QRadioButton(this);
	QRadioButton* threePointsWithoutOriginButton = new QRadioButton(this);
	QRadioButton* onePointWithOrientation = new QRadioButton(this);

	layout->addWidget(threePointsWithOriginButton, 0, 0);
	layout->addWidget(threePointsWithoutOriginButton, 1, 0);
	layout->addWidget(onePointWithOrientation, 2, 0);
	layout->addWidget(new QLabel(tr("3 points(with origin)")), 0, 1);
	layout->addWidget(new QLabel(tr("3 points(without origin)")), 1, 1);
	layout->addWidget(new QLabel(tr("1 points(keep orientation)")), 2, 1);

	layout->setColumnStretch(1, 1);

	QButtonGroup* buttonGroup = new QButtonGroup(this);
	buttonGroup->addButton(threePointsWithOriginButton,THREE_POINTS_WITH_ORIGIN);
	buttonGroup->addButton(threePointsWithoutOriginButton,THREE_POINTS_WITHOUT_ORIGIN);
	buttonGroup->addButton(onePointWithOrientation,ONE_POINT_KEEP_ORIENTATION);

	SetNextWidget(m_threePointsWithOrigin);
	InitCoorInfo();

	connect(buttonGroup, static_cast<void (QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), [this](int id){
		switch (id)
		{
		case THREE_POINTS_WITH_ORIGIN:{
			SetNextWidget(m_threePointsWithOrigin);
			m_coorInfo->method = CoordinateSystemTeachInfo::REF_SYS_THREE_POINTS_WITH_ORIGIN;
		}break;
		case THREE_POINTS_WITHOUT_ORIGIN:{
			SetNextWidget(m_threePointsWithoutOrigin);
			m_coorInfo->method = CoordinateSystemTeachInfo::REF_SYS_THREE_POINTS_WITHOUT_ORIGIN;
		}break;
		case  ONE_POINT_KEEP_ORIENTATION:{
			SetNextWidget(m_onePointKeepOrientation);
			m_coorInfo->method = CoordinateSystemTeachInfo::REF_SYS_ONE_POINT_KEEP_ORIENTATION;
		}break;
		default:
			break;
		}
	});

	threePointsWithOriginButton->setChecked(true);

	return box;
}

QWidget* RefSysWidgetOrigin::GetTeachToolWidget()
{
	QGroupBox* box = new QGroupBox(tr("Tool for teaching"), this);

	return box;
}

void RefSysWidgetOrigin::InitCoorInfo()
{
	//m_coorInfo->index = -1;
	m_coorInfo->method = CoordinateSystemTeachInfo::REF_SYS_THREE_POINTS_WITH_ORIGIN;
	m_coorInfo->values = {};
}
