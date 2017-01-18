#include "stdafx.h"
#include "RefSysDialog.h"
#include "VariateWidgetProducer.h"
#include "TRefSys.h"
#include "RefSysWidgetThreePointsWithOriginStep1.h"
#include "ICoordinate.h"
#include "RefSysWidgetThreePointsWithOriginStep2.h"
#include "Button.h"
#include "RefSysWidgetThreePointsWithOriginStep3.h"
#include "RefSysWidgetOrigin.h"
#include "RefSysWidgetThreePointsWithoutOriginStep1.h"
#include "RefSysWidgetThreePointsWithoutOriginStep2.h"
#include "RefSysWidgetThreePointsWithoutOriginStep3.h"
#include "RefSysWidgetOnePointKeepOrientation.h"
#include "RefSysWidgetEnd.h"
#include "CoordinateSystemTeachInfo.h"



RefSysDialog::RefSysDialog(TRefSys* oldVariate, ICoordinate* iCoor,QWidget* parent/*=nullptr*/)
	:DialogParent(parent)
	, m_oldVariate(oldVariate)
	, m_iCoordinate(iCoor)
{
	Init();
}

QWidget* RefSysDialog::ReferenceSystemWidget()
{
	QGroupBox* box = new QGroupBox(this);

	box->setTitle(tr("System"));
	QHBoxLayout* layout = new QHBoxLayout(box);

	QLabel* lbReference = new QLabel(tr("Reference System"), this);
	lbReference->setAlignment(Qt::AlignCenter);

	QComboBox* comboBoxReference = new QComboBox(this);
	comboBoxReference->addItem(QIcon(VariateWidgetProducer::GetIconPath(m_oldVariate->GetScope())),
		m_oldVariate->GetScope() + "." + m_oldVariate->GetName());
	comboBoxReference->setEnabled(false);

	layout->addWidget(lbReference);
	layout->addWidget(comboBoxReference);

	return box;
}

void RefSysDialog::Init()
{
	QVBoxLayout* layout = new QVBoxLayout(this);
	m_stackedWidget = new QStackedWidget(this);

	m_threePointsWithOrigin1 = new RefSysWidgetThreePointsWithOriginStep1(m_stackedWidget);
	m_threePointsWithOrigin2 = new RefSysWidgetThreePointsWithOriginStep2(m_stackedWidget);
	m_threePointsWithOrigin3 = new RefSysWidgetThreePointsWithOriginStep3(m_stackedWidget);
	m_threePointsWithoutOrigin1 = new RefSysWidgetThreePointsWithoutOriginStep1(m_stackedWidget);
	m_threePointsWithoutOrigin2 = new RefSysWidgetThreePointsWithoutOriginStep2(m_stackedWidget);
	m_threePointsWithoutOrigin3 = new RefSysWidgetThreePointsWithoutOriginStep3(m_stackedWidget);
	m_onePointKeepOrientation = new RefSysWidgetOnePointKeepOrientation(m_stackedWidget);
	m_endWidget = new RefSysWidgetEnd(m_stackedWidget);
	m_originWidget = new RefSysWidgetOrigin(m_threePointsWithOrigin1, m_threePointsWithoutOrigin1, m_onePointKeepOrientation, m_stackedWidget);
	m_originWidget->SetCoorInfo(std::make_shared<CoordinateSystemTeachInfo>());
	m_originWidget->SetNextWidget(m_threePointsWithOrigin1);

	m_threePointsWithOrigin1->SetNextWidget(m_threePointsWithOrigin2);
	m_threePointsWithOrigin2->SetNextWidget(m_threePointsWithOrigin3);
	m_threePointsWithOrigin3->SetNextWidget(m_endWidget);

	m_threePointsWithoutOrigin1->SetNextWidget(m_threePointsWithoutOrigin2);
	m_threePointsWithoutOrigin2->SetNextWidget(m_threePointsWithoutOrigin3);
	m_threePointsWithoutOrigin3->SetNextWidget(m_endWidget);

	m_onePointKeepOrientation->SetNextWidget(m_endWidget);

	m_stackedWidget->addWidget(m_originWidget);
	m_stackedWidget->addWidget(m_threePointsWithOrigin1);
	m_stackedWidget->addWidget(m_threePointsWithOrigin2);
	m_stackedWidget->addWidget(m_threePointsWithOrigin3);
	m_stackedWidget->addWidget(m_threePointsWithoutOrigin1);
	m_stackedWidget->addWidget(m_threePointsWithoutOrigin2);
	m_stackedWidget->addWidget(m_threePointsWithoutOrigin3);
	m_stackedWidget->addWidget(m_onePointKeepOrientation);
	m_stackedWidget->addWidget(m_endWidget);

	m_stackedWidget->setCurrentWidget(m_originWidget);

	layout->addWidget(ReferenceSystemWidget());
	layout->addWidget(m_stackedWidget);

	layout->setStretch(1, 1);

	for (int i = 0; i < m_stackedWidget->count();++i)
	{
		connect(dynamic_cast<SystemDialogWidgetParent*>(m_stackedWidget->widget(i)), &SystemDialogWidgetParent::SignalOnCancelClicked, [this]{
			delete this;
		});
	}
}

void RefSysDialog::UpdateText()
{
}

