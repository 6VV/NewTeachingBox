#include "stdafx.h"
#include "RefSysWidgetEnd.h"
#include "Button.h"
#include "CoordinateAdapter.h"
#include "CoordinateSystemTeachInfo.h"

RefSysWidgetEnd::RefSysWidgetEnd(QStackedWidget* parent /*= nullptr*/)
	:SystemDialogWidgetParent(parent)
{
	m_btnNext->setText(tr("Complete"));
}

QWidget* RefSysWidgetEnd::MainWidget()
{
	auto groupBox = new QGroupBox(tr("Reference system"), this);
	auto layout = new QGridLayout(groupBox);

	auto lbX = new QLabel("X", groupBox);
	auto lbY = new QLabel("Y", groupBox);
	auto lbZ = new QLabel("Z", groupBox);
	auto lbA = new QLabel("A", groupBox);
	auto lbB = new QLabel("B", groupBox);
	auto lbC = new QLabel("C", groupBox);

	m_ltX = new QLineEdit(groupBox);
	m_ltY = new QLineEdit(groupBox);
	m_ltZ = new QLineEdit(groupBox);
	m_ltA = new QLineEdit(groupBox);
	m_ltB = new QLineEdit(groupBox);
	m_ltC = new QLineEdit(groupBox);

	m_ltX->setEnabled(false);
	m_ltY->setEnabled(false);
	m_ltZ->setEnabled(false);
	m_ltA->setEnabled(false);
	m_ltB->setEnabled(false);
	m_ltC->setEnabled(false);


	layout->addWidget(lbX, 0, 0);
	layout->addWidget(lbY, 1, 0);
	layout->addWidget(lbZ, 2, 0);
	layout->addWidget(lbA, 3, 0);
	layout->addWidget(lbB, 4, 0);
	layout->addWidget(lbC, 5, 0);

	layout->addWidget(m_ltX, 0, 1);
	layout->addWidget(m_ltY, 1, 1);
	layout->addWidget(m_ltZ, 2, 1);
	layout->addWidget(m_ltA, 3, 1);
	layout->addWidget(m_ltB, 4, 1);
	layout->addWidget(m_ltC, 5, 1);

	return groupBox;
}

QString RefSysWidgetEnd::IllustrationPixmapPath()
{
	return ":/new/image/Resources/Image/ref_sys_end.png";
}

void RefSysWidgetEnd::OnReseivePose(const tPoseEuler&/* = */)
{

}


bool RefSysWidgetEnd::HaveNext()
{
	return true;
}

void RefSysWidgetEnd::showEvent(QShowEvent *event)
{
	SystemDialogWidgetParent::showEvent(event);

	tPoseEuler m_poseEuler{};
	switch (m_coorInfo->method)
	{
	case CoordinateSystemTeachInfo::REF_SYS_THREE_POINTS_WITH_ORIGIN : {
		int xy = 1;
		int zyzxyz = 1;
		switch (m_coorInfo->values.at(1).orientation)
		{
		case CoordinateSystemTeachInfo::X:{xy = 1; }break;
		case CoordinateSystemTeachInfo::Y:{xy = 2; }break;
		case CoordinateSystemTeachInfo::Z:{xy = 3; }break;
		default:
			break;
		}
		switch (m_coorInfo->values.at(2).orientation)
		{
		case CoordinateSystemTeachInfo::XY:{zyzxyz = 1; }break;
		case CoordinateSystemTeachInfo::ZX:{zyzxyz = 2; }break;
		case CoordinateSystemTeachInfo::YZ:{zyzxyz = 3; }break;
		default:
			break;
		}
		m_poseEuler=CoordinateAdapter::CartTeachThreeBase(*m_coorInfo->values.at(0).poseEuler, *m_coorInfo->values.at(1).poseEuler,
			*m_coorInfo->values.at(2).poseEuler, xy, zyzxyz);
	}break;
	case CoordinateSystemTeachInfo::REF_SYS_THREE_POINTS_WITHOUT_ORIGIN:{
		int xy = 1;
		int zyzxyz = 1;
		switch (m_coorInfo->values.at(0).orientation)
		{
		case CoordinateSystemTeachInfo::X:{xy = 1; }break;
		case CoordinateSystemTeachInfo::Y:{xy = 2; }break;
		case CoordinateSystemTeachInfo::Z:{xy = 3; }break;
		default:
			break;
		}
		switch (m_coorInfo->values.at(2).orientation)
		{
		case CoordinateSystemTeachInfo::X:{zyzxyz = 1; }break;
		case CoordinateSystemTeachInfo::Y:{zyzxyz = 2; }break;
		case CoordinateSystemTeachInfo::Z:{zyzxyz = 3; }break;
		default:
			break;
		}
		m_poseEuler = CoordinateAdapter::CartTeachThreeNoBase(*m_coorInfo->values.at(0).poseEuler, *m_coorInfo->values.at(1).poseEuler,
			*m_coorInfo->values.at(2).poseEuler, xy, zyzxyz);
	}break;
	case  CoordinateSystemTeachInfo::REF_SYS_ONE_POINT_KEEP_ORIENTATION:{
		m_poseEuler = CoordinateAdapter::CartTeachOne(m_coorInfo->values.at(0).poseEuler->m_PositionCartesian);
	}break;
	default:
		break;
	}

	m_ltX->setText(QString::number(m_poseEuler.m_PositionCartesian.m_X));
	m_ltY->setText(QString::number(m_poseEuler.m_PositionCartesian.m_Y));
	m_ltZ->setText(QString::number(m_poseEuler.m_PositionCartesian.m_Z));
	m_ltA->setText(QString::number(m_poseEuler.m_PostureEuler.m_A));
	m_ltB->setText(QString::number(m_poseEuler.m_PostureEuler.m_B));
	m_ltC->setText(QString::number(m_poseEuler.m_PostureEuler.m_C));
}

void RefSysWidgetEnd::OnNextButtonClicked()
{
	emit(SignalCompletePose(m_poseEuler));
	emit(SignalOnCancelClicked());
}
