﻿#include "stdafx.h"
#include "TDynamic.h"
#include "TreeWidgetItemWithVariate.h"
#include "RegExp.h"
#include "LineEditInTree.h"



TDynamic::TDynamic(const QString& scope, const QString& name, const tDynamicConstraint& value)
	:TVariate(scope,name,TSymbol::TYPE_DYNAMIC)
{
	m_value = value;
}

TDynamic::TDynamic(QDataStream& dataStream) : TVariate(dataStream)
{
	WriteValueStream(dataStream);
}

const tDynamicConstraint& TDynamic::GetValue() const
{
	return m_value;
}

void TDynamic::SetValue(const tDynamicConstraint& value)
{
	m_value = value;
}

void TDynamic::WriteValueStream(QDataStream& dataStream)
{
	dataStream >> m_value.m_Velocity;
	dataStream >> m_value.m_Acceleration;
	dataStream >> m_value.m_Deceleration;

	dataStream >> m_value.m_PostureVelocity;
	dataStream >> m_value.m_PostureAcceleration;
	dataStream >> m_value.m_PostureDeceleration;
}

void TDynamic::SlotOnTextChanged()
{
	LineEditInTree* currentWidget = static_cast<LineEditInTree*>(sender());
	QTreeWidgetItem* parentItem = currentWidget->GetParentItem();
	QTreeWidget* treeWidget = currentWidget->GetTreeWidget();

	m_value.m_Velocity = static_cast<QLineEdit*>(treeWidget->itemWidget(parentItem->child(0), 1))->text().toDouble();
	m_value.m_Acceleration = static_cast<QLineEdit*>(treeWidget->itemWidget(parentItem->child(1), 1))->text().toDouble();
	m_value.m_Deceleration = static_cast<QLineEdit*>(treeWidget->itemWidget(parentItem->child(2), 1))->text().toDouble();
	m_value.m_PostureVelocity = static_cast<QLineEdit*>(treeWidget->itemWidget(parentItem->child(3), 1))->text().toDouble();
	m_value.m_PostureDeceleration = static_cast<QLineEdit*>(treeWidget->itemWidget(parentItem->child(4), 1))->text().toDouble();
	m_value.m_PostureDeceleration = static_cast<QLineEdit*>(treeWidget->itemWidget(parentItem->child(5), 1))->text().toDouble();

	UpdateRamAndDatabaseFrom(*this);
}

void TDynamic::ReadTreeWidgetItem(QTreeWidgetItem* parentItem, QTreeWidget* treeWidget)
{
	TreeWidgetItemWithVariate* itemVariate = new TreeWidgetItemWithVariate(parentItem, this);

	QStringList variateNames = QStringList{ "Velocity", "Acceleration", "Deceleration",
		"PostureVelocity", "PostureAcceleration", "PostureDeceleration" };

	QVector<QTreeWidgetItem*> items;
	for (auto var : variateNames)
	{
		items.push_back(new QTreeWidgetItem(itemVariate, QStringList(var)));
	}

	QStringList variateValues = QStringList{
		QString::number(m_value.m_Velocity),
		QString::number(m_value.m_Acceleration),
		QString::number(m_value.m_Deceleration), 
		QString::number(m_value.m_PostureVelocity),
		QString::number(m_value.m_PostureAcceleration),
		QString::number(m_value.m_PostureDeceleration) };

	QVector<LineEditInTree*> lineEdits;
	for (int i = 0; i < variateValues.size(); ++i)
	{
		LineEditInTree* lineEdit = new LineEditInTree(itemVariate,treeWidget,
			variateValues.at(i), RegExp::STR_REG_FLOAT);

		connect(lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(SlotOnTextChanged()));

		lineEdits.push_back(lineEdit);
		treeWidget->setItemWidget(items.at(i), 1, lineEdit);
	}
}

void TDynamic::ReadValueStream(QDataStream& dataStream)const
{
	dataStream << m_value.m_Velocity;
	dataStream << m_value.m_Acceleration;
	dataStream << m_value.m_Deceleration;

	dataStream << m_value.m_PostureVelocity;
	dataStream << m_value.m_PostureAcceleration;
	dataStream << m_value.m_PostureDeceleration;
}

void TDynamic::UpdateFromValue(const TVariate& variate)
{
	m_value = static_cast<const TDynamic&>(variate).m_value;
}
