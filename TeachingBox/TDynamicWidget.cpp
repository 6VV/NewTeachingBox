#include "stdafx.h"
#include "TDynamicWidget.h"
#include "TDynamic.h"
#include "LineEditInTree.h"
#include "DataStruct.h"



TDynamicWidget::TDynamicWidget(TDynamic* dynamic)
	:TVariateWidget(dynamic)
{

}

TDynamicWidget::~TDynamicWidget()
{

}

void TDynamicWidget::UpdateVariate()
{
	static_cast<TDynamic*>(m_variate)->SetValue(m_value);
}

void TDynamicWidget::WriteContentToTreeWidgetItem(QTreeWidgetItem* parentItem, QTreeWidget* treeWidget)
{
	QStringList variateNames = QStringList{ "Velocity", "Acceleration", "Deceleration",
		"PostureVelocity", "PostureAcceleration", "PostureDeceleration" };

	QVector<QTreeWidgetItem*> items;
	for (auto var : variateNames)
	{
		items.push_back(new QTreeWidgetItem(parentItem, QStringList(var)));
	}

	auto value = static_cast<TDynamic*>(m_variate)->GetValue();
	QStringList variateValues = QStringList{
		QString::number(value.m_Velocity),
		QString::number(value.m_Acceleration),
		QString::number(value.m_Deceleration),
		QString::number(value.m_PostureVelocity),
		QString::number(value.m_PostureAcceleration),
		QString::number(value.m_PostureDeceleration) };

	QVector<LineEditInTree*> lineEdits;
	for (int i = 0; i < variateValues.size(); ++i)
	{
		LineEditInTree* lineEdit = new LineEditInTree(parentItem, treeWidget,
			variateValues.at(i), RegExp::STR_REG_FLOAT);

		connect(lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(SlotOnValueChanged()));

		lineEdits.push_back(lineEdit);
		treeWidget->setItemWidget(items.at(i), 1, lineEdit);
	}
}

void TDynamicWidget::OnValueChanged()
{
	LineEditInTree* currentWidget = static_cast<LineEditInTree*>(sender());
	QTreeWidgetItem* parentItem = currentWidget->GetParentItem();
	QTreeWidget* treeWidget = currentWidget->GetTreeWidget();

	//tDynamicConstraint value;
	m_value.m_Velocity = static_cast<QLineEdit*>(treeWidget->itemWidget(parentItem->child(0), 1))->text().toDouble();
	m_value.m_Acceleration = static_cast<QLineEdit*>(treeWidget->itemWidget(parentItem->child(1), 1))->text().toDouble();
	m_value.m_Deceleration = static_cast<QLineEdit*>(treeWidget->itemWidget(parentItem->child(2), 1))->text().toDouble();
	m_value.m_PostureVelocity = static_cast<QLineEdit*>(treeWidget->itemWidget(parentItem->child(3), 1))->text().toDouble();
	m_value.m_PostureAcceleration = static_cast<QLineEdit*>(treeWidget->itemWidget(parentItem->child(4), 1))->text().toDouble();
	m_value.m_PostureDeceleration = static_cast<QLineEdit*>(treeWidget->itemWidget(parentItem->child(5), 1))->text().toDouble();

	//static_cast<TDynamic*>(m_variate)->SetValue(value);
}
