#include "stdafx.h"
#include "ToolSysDialog.h"
#include "QBoxLayout"
#include "TToolSys.h"
#include "ToolSysWidgetOrigin.h"
#include "ToolSysWIdgetFourPoints.h"
#include "CoordinateSystemTeachInfo.h"
#include "ToolSysWidgetOnePoint6D.h"
#include "ToolSysWidgetEnd.h"
#include "ICoordinate.h"



ToolSysDialog::ToolSysDialog(TToolSys* oldVariate, ICoordinate* iCoor, QWidget* parent /*= nullptr*/)
	:DialogParent(parent)
	, m_oldVariate(oldVariate)
	, m_iCoor(iCoor)
{
	Init();
}

QWidget* ToolSysDialog::CreateToolWidget()
{
	QGroupBox* box = new QGroupBox(tr("Tool"), this);
	QHBoxLayout* layout = new QHBoxLayout(box);

	auto lbTool = new QLabel(tr("Tool"), box);
	lbTool->setAlignment(Qt::AlignCenter);

	auto variateBox = new QComboBox(box);
	variateBox->addItem(m_oldVariate->GetScope() + "." + m_oldVariate->GetName());
	variateBox->setEnabled(false);

	layout->addWidget(lbTool);
	layout->addWidget(variateBox);

	return box;
}

void ToolSysDialog::Init()
{
	QVBoxLayout* layout = new QVBoxLayout(this);
	m_stackedWidget = new QStackedWidget(this);

	layout->addWidget(CreateToolWidget());
	layout->addWidget(m_stackedWidget);

	layout->setStretch(1, 1);

	m_widgetOrigin = new ToolSysWidgetOrigin(m_stackedWidget);
	m_fourPointsStep1 = new ToolSysWidgetFourPoints(m_stackedWidget, ":/new/image/Resources/Image/tool_sys_4_points_step1.png", tr("Method 4 points XYZ step1"));
	m_fourPointsStep2 = new ToolSysWidgetFourPoints(m_stackedWidget, ":/new/image/Resources/Image/tool_sys_4_points_step2.png", tr("Method 4 points XYZ step2"));
	m_fourPointsStep3 = new ToolSysWidgetFourPoints(m_stackedWidget, ":/new/image/Resources/Image/tool_sys_4_points_step3.png", tr("Method 4 points XYZ step3"));
	m_fourPointsStep4 = new ToolSysWidgetFourPoints(m_stackedWidget, ":/new/image/Resources/Image/tool_sys_4_points_step4.png", tr("Method 4 points XYZ step4"));
	m_onePoint6D = new ToolSysWidgetOnePoint6D(m_stackedWidget);
	m_widgetEnd = new ToolSysWidgetEnd(m_stackedWidget);

	m_widgetOrigin->SetCoorInfo(std::make_shared<CoordinateSystemTeachInfo>());
	m_widgetOrigin->SetNextWidget(m_fourPointsStep1);
	m_fourPointsStep1->SetNextWidget(m_fourPointsStep2);
	m_fourPointsStep2->SetNextWidget(m_fourPointsStep3);
	m_fourPointsStep3->SetNextWidget(m_fourPointsStep4);
	m_fourPointsStep4->SetNextWidget(m_onePoint6D);
	m_onePoint6D->SetNextWidget(m_widgetEnd);

	m_stackedWidget->addWidget(m_widgetOrigin);
	m_stackedWidget->addWidget(m_fourPointsStep1);
	m_stackedWidget->addWidget(m_fourPointsStep2);
	m_stackedWidget->addWidget(m_fourPointsStep3);
	m_stackedWidget->addWidget(m_fourPointsStep4);
	m_stackedWidget->addWidget(m_onePoint6D);
	m_stackedWidget->addWidget(m_widgetEnd);

	m_stackedWidget->setCurrentWidget(m_widgetOrigin);

	for (int i = 0; i < m_stackedWidget->count();++i)
	{
		connect(dynamic_cast<SystemDialogWidgetParent*>(m_stackedWidget->widget(i)), &SystemDialogWidgetParent::SignalOnCancelClicked, [this]{
			delete this;
		});
	}

	connect(dynamic_cast<SystemDialogWidgetParent*>(m_widgetEnd), &ToolSysWidgetEnd::SignalCompletePose, [this](const tPoseEuler& poseEuler){
		m_iCoor->OnReceive(poseEuler);
		delete this;
	});
}

void ToolSysDialog::UpdateText()
{
}


