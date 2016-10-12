#include "stdafx.h"
#include "TPositionWidget.h"
#include "TPosition.h"
#include "TreeWidgetItemWithVariate.h"
#include "LineEditInTree.h"


TPositionWidget::TPositionWidget(TPosition* positon)
	:TVariateWidget(positon)
{

}

TPositionWidget::~TPositionWidget()
{

}

void TPositionWidget::ReadContentTreeWidgetItem(QTreeWidgetItem* parentItem, QTreeWidget* treeWidget)
{
	QVector<QTreeWidgetItem*> treeItems;
	for (int i = 0; i < AXIS_SIZE; ++i)
	{
		QString name = "Axis" + QString::number(i + 1);

		treeItems.push_back(new QTreeWidgetItem(parentItem, QStringList{ name }));
	}

	QVector<LineEditInTree*> lineEdits;
	auto value = static_cast<TPosition*>(m_variate)->GetValue();
	for (int i = 0; i < treeItems.size(); ++i)
	{
		LineEditInTree* lineEdit = new LineEditInTree(parentItem, treeWidget,
			QString::number(value.m_AxisPosition[i]), RegExp::STR_REG_FLOAT);

		lineEdits.push_back(lineEdit);
		treeWidget->setItemWidget(treeItems.at(i), 1, lineEdit);

		connect(lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(SlotOnValueChanged()));
	}
}

void TPositionWidget::OnValueChanged()
{
	LineEditInTree* currentWidget = static_cast<LineEditInTree*>(sender());
	QTreeWidgetItem* parentItem = currentWidget->GetParentItem();
	QTreeWidget* treeWidget = currentWidget->GetTreeWidget();

	tAxesAllPositions position{};
	for (int i = 0; i < parentItem->childCount(); ++i)
	{
		QLineEdit* lineEdit = static_cast<QLineEdit*>(treeWidget->itemWidget(parentItem->child(i), 1));
		position.m_AxisPosition[i] = lineEdit->text().toDouble();
	}

	static_cast<TPosition*>(m_variate)->SetValue(position);
}
