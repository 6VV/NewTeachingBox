#include "stdafx.h"
#include "ScreenVariate.h"
#include "QTreeWidget"
#include "VariateScope.h"
#include "ButtonGroup.h"



ScreenVariate::ScreenVariate(QWidget* parent /*= 0*/)
	:ScreenMainParent(parent)
	, m_treeWidget(new QTreeWidget(this))
	, m_btnVariate(new Button(this))
	, m_btnTeach (new Button(this))
	, m_btnCheck(new Button(this))
	, m_btnClearUnused (new Button(this))

{
	Init();
}

ScreenVariate::~ScreenVariate()
{

}

void ScreenVariate::SlotOnVariateButtonClicked()
{
	m_btnGroupVariate->show();
}

QList<QPushButton*> ScreenVariate::GetButtonList()
{
	QList<QPushButton*> btnList;
	btnList.push_back(m_btnVariate);
	btnList.push_back(m_btnTeach);
	btnList.push_back(m_btnClearUnused);
	btnList.push_back(m_btnCheck);

	return btnList;
}

QLayout* ScreenVariate::GetMainLayout()
{
	QHBoxLayout* layout=new QHBoxLayout(this);
	layout->addWidget(m_treeWidget);

	return layout;
}

void ScreenVariate::Init()
{
	InitTreeWidget();
	InitButtonWidget();
	InitSignalSlot();

	UpdateText();
}

void ScreenVariate::InitTreeWidget()
{
	m_treeWidget->setColumnCount(2);
	m_treeWidget->header()->setSectionResizeMode(QHeaderView::Stretch);	//平均分布各列

	m_treeWidget->addTopLevelItem(new QTreeWidgetItem(QStringList{ VariateScope::SCOPE_SYSTEM }));
	m_treeWidget->addTopLevelItem(new QTreeWidgetItem(QStringList{ VariateScope::SCOPE_SYNERGIC }));
	m_treeWidget->addTopLevelItem(new QTreeWidgetItem(QStringList{ VariateScope::SCOPE_GLOBAL }));
	m_treeWidget->addTopLevelItem(new QTreeWidgetItem(QStringList{ VariateScope::SCOPE_PROJECT }));
}

void ScreenVariate::InitButtonWidget()
{
	m_btnCopy = new Button(this);
	m_btnCut = new Button(this);
	m_btnPaste = new Button(this);
	m_btnRename = new Button(this);
	m_btnNew = new Button(this);
	m_btnDelete = new Button(this);

	QList<Button*> btnList;
	btnList.append(m_btnCopy);
	btnList.append(m_btnCut);
	btnList.append(m_btnPaste);
	btnList.append(m_btnRename);
	btnList.append(m_btnNew);
	btnList.append(m_btnDelete);

	m_btnGroupVariate = new ButtonGroup(btnList, m_btnVariate);
}

void ScreenVariate::InitSignalSlot()
{
	connect(m_btnVariate, SIGNAL(clicked()), this, SLOT(SlotOnVariateButtonClicked()));
}

void ScreenVariate::UpdateText()
{
	m_btnVariate->setText(tr("Variate"));
	m_btnTeach->setText(tr("Teach"));
	m_btnClearUnused->setText(tr("Clear Unused"));
	m_btnCheck->setText(tr("Check"));

	m_btnCopy->setText(tr("Copy"));
	m_btnCut->setText(tr("Cut"));
	m_btnPaste->setText(tr("Paste"));
	m_btnRename->setText(tr("Rename"));
	m_btnNew->setText(tr("New"));
	m_btnDelete->setText(tr("Delete"));

	QStringList headStrings;
	headStrings.append(tr("Variate"));
	headStrings.append(tr("Value"));
	m_treeWidget->setHeaderLabels(headStrings);
}
