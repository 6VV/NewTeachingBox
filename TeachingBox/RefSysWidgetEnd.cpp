#include "stdafx.h"
#include "RefSysWidgetEnd.h"
#include "Button.h"


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

void RefSysWidgetEnd::OnNextButtonClicked()
{
	emit(SignalOnCancelClicked());
}
