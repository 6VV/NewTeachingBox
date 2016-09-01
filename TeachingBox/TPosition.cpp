#include "stdafx.h"
#include "TPosition.h"
#include "TreeWidgetItemWithVariate.h"
#include "RegExp.h"
#include "LineEditInTree.h"


TPosition::TPosition(QDataStream& dataStream) : TVariate(dataStream)
{
	double value;

	for (int i = 0; i < AXIS_SIZE;++i)
	{
		dataStream >> value;
		m_value.m_AxisPosition[i] = value;
		//m_value.push_back(value);
	}
}

TPosition::TPosition(const QString& scope, const QString& name, const tAxesAllPositions& value)
	:TVariate(scope, name, TSymbol::TYPE_POSITION)
{
	m_value = value;
}

const tAxesAllPositions TPosition::GetValue() const
{
	return m_value;
}

void TPosition::ReadTreeWidgetItem(QTreeWidgetItem* parentItem, QTreeWidget* treeWidget)
{
	TreeWidgetItemWithVariate* variateItem = new TreeWidgetItemWithVariate(parentItem, this);

	QVector<QTreeWidgetItem*> treeItems;
	for (int i = 0; i < AXIS_SIZE;++i)
	{
		QString name = "Axis"+QString::number(i + 1);

		treeItems.push_back(new QTreeWidgetItem(variateItem, QStringList{ name }));
	}

	QVector<LineEditInTree*> lineEdits;
	for (int i = 0; i < treeItems.size();++i)
	{
		LineEditInTree* lineEdit = new LineEditInTree(variateItem,treeWidget,
			QString::number(m_value.m_AxisPosition[i]), RegExp::STR_REG_FLOAT);

		lineEdits.push_back(lineEdit);
		treeWidget->setItemWidget(treeItems.at(i), 1, lineEdit);

		connect(lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(SlotOnTextChanged()));
	}

}

void TPosition::ReadValueStream(QDataStream& dataStream)const
{
	for (int i = 0; i < AXIS_SIZE;++i)
	{
		dataStream << m_value.m_AxisPosition[i];
	}
}

void TPosition::UpdateFromValue(const TVariate& variate)
{
	m_value = static_cast<const TPosition&>(variate).m_value;
}

void TPosition::SlotOnTextChanged()
{
	LineEditInTree* currentWidget = static_cast<LineEditInTree*>(sender());
	QTreeWidgetItem* parentItem = currentWidget->GetParentItem();
	QTreeWidget* treeWidget = currentWidget->GetTreeWidget();

	tAxesAllPositions position{};
	for (int i = 0; i < parentItem->childCount();++i)
	{
		QLineEdit* lineEdit=static_cast<QLineEdit*>(treeWidget->itemWidget(parentItem->child(i), 1));
		position.m_AxisPosition[i] = lineEdit->text().toDouble();
	}

	m_value = position;
	UpdateRamAndDatabaseFrom(*this);
}
