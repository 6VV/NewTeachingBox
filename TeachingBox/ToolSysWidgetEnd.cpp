#include "stdafx.h"
#include "ToolSysWidgetEnd.h"
#include "Button.h"
#include "CoordinateAdapter.h"
#include "CoordinateSystemTeachInfo.h"

ToolSysWidgetEnd::ToolSysWidgetEnd(QStackedWidget* parent)
	:SystemDialogWidgetParent(parent)
{
	m_btnNext->setText(tr("Complete"));
}

void ToolSysWidgetEnd::showEvent(QShowEvent *event)
{
	SystemDialogWidgetParent::showEvent(event);

	m_poseEuler.m_PositionCartesian = CoordinateAdapter::ToolFrameSetWithFourPoints(*m_coorInfo->values.at(0).poseEuler,
		*m_coorInfo->values.at(1).poseEuler, *m_coorInfo->values.at(2).poseEuler, *m_coorInfo->values.at(3).poseEuler);

	int axis = 1;
	unsigned char invert = 0;
	switch (m_coorInfo->values.at(4).orientation)
	{
	case CoordinateSystemTeachInfo::IX:{
		axis = 1;
		invert = 1;
	}break;
	case CoordinateSystemTeachInfo::IY:{
		axis = 2;
		invert = 1;
	}break;
	case CoordinateSystemTeachInfo::IZ:{
		axis = 3;
		invert = 1;
	}break;
	case CoordinateSystemTeachInfo::X:{
		axis = 1;
		invert = 0;
	}break;
	case CoordinateSystemTeachInfo::Y:{
		axis = 2;
		invert = 0;
	}break;
	case CoordinateSystemTeachInfo::Z:{
		axis = 3;
		invert = 0;
	}break;
	default:
		break;
	}
	m_poseEuler.m_PostureEuler = CoordinateAdapter::ToolFrameSetWithOnePoint(*m_coorInfo->values.at(4).poseEuler, axis, invert);

	m_ltX->setText(QString::number(m_poseEuler.m_PositionCartesian.m_X));
	m_ltY->setText(QString::number(m_poseEuler.m_PositionCartesian.m_Y));
	m_ltZ->setText(QString::number(m_poseEuler.m_PositionCartesian.m_Z));
	m_ltA->setText(QString::number(m_poseEuler.m_PostureEuler.m_A));
	m_ltB->setText(QString::number(m_poseEuler.m_PostureEuler.m_B));
	m_ltC->setText(QString::number(m_poseEuler.m_PostureEuler.m_C));
}

QWidget* ToolSysWidgetEnd::MainWidget()
{
	auto groupBox = new QGroupBox(tr("Tool system"), this);
	auto layout = new QVBoxLayout(groupBox);

	layout->addWidget(PointWidgetXYZABC());

	return groupBox;
}

QString ToolSysWidgetEnd::IllustrationPixmapPath()
{
	return ":/new/image/Resources/Image/tool_sys_end.png";
}

bool ToolSysWidgetEnd::HaveNext()
{
	return true;
}

void ToolSysWidgetEnd::OnReseivePose(const tPoseEuler&/* = */)
{
}

void ToolSysWidgetEnd::OnNextButtonClicked()
{
	emit(SignalCompletePose(m_poseEuler));
}
