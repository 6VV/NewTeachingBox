#include "stdafx.h"
#include "ToolSysWidgetOnePoint6D.h"
#include "QGridLayout"
#include "QCheckBox"
#include "CoordinateSystemTeachInfo.h"


ToolSysWidgetOnePoint6D::ToolSysWidgetOnePoint6D(QStackedWidget* parent)
	:SystemDialogWidgetParent(parent)
{

}

QWidget* ToolSysWidgetOnePoint6D::MainWidget()
{
	QGroupBox* box = new QGroupBox(tr("Method 1 points 6D"));
	QVBoxLayout* layout = new QVBoxLayout(box);

	auto btnTeach = new QPushButton(tr("Teach"), box);
	layout->addLayout(DirectionLayout());
	layout->addWidget(PointWidgetABC());
	layout->addWidget(btnTeach);

	layout->setStretch(1, 1);

	connect(btnTeach, &QPushButton::clicked, [this]{
		GetRemotePose();
	});

	return box;
}

QString ToolSysWidgetOnePoint6D::IllustrationPixmapPath()
{
	return ":/new/image/Resources/Image/tool_sys_1_point_6D.png";
}

QLayout* ToolSysWidgetOnePoint6D::DirectionLayout()
{
	QGridLayout* layout = new QGridLayout(this);

	m_axisBox = new QComboBox(this);
	m_axisBox->addItems({ "X", "Y", "Z" });

	m_invertBox = new QCheckBox(this);

	connect(m_axisBox, &QComboBox::currentTextChanged, [this]{
		UpdateCoorDirection();
	});
	connect(m_invertBox, &QCheckBox::stateChanged, [this]{
		UpdateCoorDirection();
	});

	layout->addWidget(new QLabel(tr("Axis")),0,0);
	layout->addWidget(new QLabel(tr("Invert")), 0, 1);
	layout->addWidget(m_axisBox, 1, 0);
	layout->addWidget(m_invertBox, 1, 1);

	return layout;
}

void ToolSysWidgetOnePoint6D::UpdateCoorDirection()
{
	CoordinateSystemTeachInfo::Orientation axis=CoordinateSystemTeachInfo::X;
	if (m_invertBox->isChecked())
	{
		if (m_axisBox->currentText()=="X")
		{
			axis = CoordinateSystemTeachInfo::IX;
		}
		else if (m_axisBox->currentText() == "Y")
		{
			axis = CoordinateSystemTeachInfo::IY;
		}
		else
		{
			axis = CoordinateSystemTeachInfo::IZ;
		}
	}
	else
	{
		if (m_axisBox->currentText() == "X")
		{
			axis = CoordinateSystemTeachInfo::X;
		}
		else if (m_axisBox->currentText() == "Y")
		{
			axis = CoordinateSystemTeachInfo::Y;
		}
		else
		{
			axis = CoordinateSystemTeachInfo::Z;
		}
	}

	if (IsTeached())
	{
		m_coorInfo->UpdateOrientation(axis);
	}
}

void ToolSysWidgetOnePoint6D::OnReseivePose(const tPoseEuler& pose /*= */)
{
	SystemDialogWidgetParent::OnReseivePose(pose);

	if (IsTeached())
	{
		m_coorInfo->UpdatePoseEuler(pose);
	}
	else
	{
		m_coorInfo->AddPoseEuler(pose);
		UpdateCoorDirection();
	}

	UpdateButtonState();
}

