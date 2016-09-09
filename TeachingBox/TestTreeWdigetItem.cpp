#include "stdafx.h"
#include "TestTreeWdigetItem.h"
#include "QPushButton"
#include "QBoxLayout"



TestTreeWidget::TestTreeWidget()
	:m_treeWidget(new QTreeWidget(this))
	,m_btnClear(new QPushButton(this))
	, m_btnAddItem(new QPushButton(this))
{
	QVBoxLayout* layout = new QVBoxLayout(this);

	QHBoxLayout* buttonLayout = new QHBoxLayout(this);
	buttonLayout->addWidget(m_btnAddItem);
	buttonLayout->addWidget(m_btnClear);

	m_btnAddItem->setText("Add Item");
	m_btnClear->setText("Clear Item");
	connect(m_btnAddItem, SIGNAL(clicked()), this, SLOT(SlotOnAddItem()));
	connect(m_btnClear, SIGNAL(clicked()), this, SLOT(SlotOnClearItem()));

	layout->addWidget(m_treeWidget);
	layout->addLayout(buttonLayout);
	layout->setStretch(0, 1);
}

void TestTreeWidget::SlotOnAddItem()
{
	m_treeWidget->addTopLevelItem(new TestTreeWidgetItem(QString::number(m_treeWidget->topLevelItemCount())));
}

void TestTreeWidget::SlotOnClearItem()
{
	m_treeWidget->clear();
}

TestTreeWidgetItem::TestTreeWidgetItem(const QString& text)
	:QTreeWidgetItem(QStringList{text})
{

}
