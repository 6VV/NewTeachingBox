#include "stdafx.h"
#include "TRefSysWidget.h"
#include "ComboBoxInTree.h"
#include "LineEditInTree.h"



TRefSysWidget::TRefSysWidget(TRefSys* variate)
	:TVariateWidget(variate)
{

}

TRefSysWidget::~TRefSysWidget()
{

}

void TRefSysWidget::UpdateVariate()
{
	static_cast<TRefSys*>(m_variate)->SetValue(m_value);
}

void TRefSysWidget::OnValueChanged()
{
	WidgetItemInTree* widget = dynamic_cast<WidgetItemInTree*>(sender());
	QTreeWidgetItem* variateItem = widget->GetParentItem();
	QTreeWidget* treeWidget = widget->GetTreeWidget();

	QString baseSysBox = static_cast<QComboBox*>(treeWidget->itemWidget(variateItem->child(0), 1))->currentText();
	m_value.baseSys = baseSysBox;

	for (int i = 0; i < 6;++i)
	{
		double value = static_cast<QLineEdit*>(treeWidget->itemWidget(variateItem->child(i + 1), 1))->text().toDouble();
		m_value.offset[i] = value;
	}
}

void TRefSysWidget::WriteContentToTreeWidgetItem(QTreeWidgetItem* parentItem, QTreeWidget* treeWidget)
{
	auto value = static_cast<TRefSys*>(m_variate)->GetValue();

	QTreeWidgetItem* baseSysItem = new QTreeWidgetItem(parentItem, QStringList{ "Base Sys" });
	ComboBoxInTree* baseSysComboBox = new ComboBoxInTree(parentItem, treeWidget);
	baseSysComboBox->addItem(value.baseSys);
	treeWidget->setItemWidget(baseSysItem, 1, baseSysComboBox);
	connect(baseSysComboBox, &QComboBox::currentTextChanged, this, &TRefSysWidget::SlotOnValueChanged);

	QStringList offsets{ "x", "y", "z", "a", "b", "c" };
	for (int i = 0; i < offsets.length();++i)
	{
		auto treeItem = new QTreeWidgetItem(parentItem, QStringList{ offsets[i] });
		parentItem->addChild(treeItem);

		LineEditInTree* lineEdit = new LineEditInTree(parentItem, treeWidget,
			QString::number(value.offset[i]), RegExp::STR_REG_FLOAT);
		connect(lineEdit, &QLineEdit::textChanged, this, &TRefSysWidget::SlotOnValueChanged);

		treeWidget->setItemWidget(treeItem, 1, lineEdit);
	}

}
