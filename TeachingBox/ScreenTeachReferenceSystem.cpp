#include "stdafx.h"
#include "ScreenTeachReferenceSystem.h"
#include "QBoxLayout"



ScreenTeachReferenceSystem::ScreenTeachReferenceSystem(QWidget* parent/*=nullptr*/)
	:InternationalWidget(parent)
{
	Init();
}

void ScreenTeachReferenceSystem::UpdateText()
{
}

QWidget* ScreenTeachReferenceSystem::GetReferenceSystemWidget()
{
	QGroupBox* box = new QGroupBox(this);

	box->setTitle(tr("System"));
	QHBoxLayout* layout = new QHBoxLayout(box);

	QLabel* lbReference = new QLabel(tr("Reference System"), this);
	lbReference->setAlignment(Qt::AlignCenter);
	QComboBox* comboBoxReference = new QComboBox(this);

	layout->addWidget(lbReference);
	layout->addWidget(comboBoxReference);

	return box;
}

QLayout* ScreenTeachReferenceSystem::GetTeachLayout()
{
	QVBoxLayout* layout = new QVBoxLayout(this);

	layout->addWidget(GetTeachToolWidget());
	layout->addWidget(GetTeachMethodWidget());

	return layout;
}

QWidget* ScreenTeachReferenceSystem::GetTeachMethodWidget()
{
	QGroupBox* box = new QGroupBox(tr("Select teach method"),this);

	return box;
}

QWidget* ScreenTeachReferenceSystem::GetTeachToolWidget()
{
	QGroupBox* box = new QGroupBox(tr("Tool for teaching"), this);

	return box;
}

QWidget* ScreenTeachReferenceSystem::GetIllustrationWidget()
{
	QGroupBox* box = new QGroupBox(tr("Illustration"), this);

	return box;
}

void ScreenTeachReferenceSystem::Init()
{
	QGridLayout* layout = new QGridLayout(this);

	layout->addWidget(GetReferenceSystemWidget(), 0, 0, 1, 2);
	layout->addLayout(GetTeachLayout(), 1, 0);
	layout->addWidget(GetIllustrationWidget(), 1, 1);

	UpdateText();
}
