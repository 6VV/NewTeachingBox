#include "stdafx.h"
#include "TInteger.h"
#include "TVariateType.h"
#include "RegExp.h"
#include "TSymbol.h"
#include "TreeWidgetItemWithVariate.h"
#include "LineEditWithRegExpAndKeyboard.h"



TInteger::TInteger(const QString& scope, const QString& name, const int value)
	:TVariate(scope,name,TSymbol::TYPE_INTERGER)
{
	m_value = value;
}

TInteger::TInteger(QDataStream& dataStream) :TVariate(dataStream)
{
	dataStream >> m_value;
}

TInteger::TInteger(const TInteger& variate)
	: TVariate(variate)
{
	m_value = variate.m_value;
}

int TInteger::GetValue()
{
	return m_value;
}

void TInteger::SetValue(const int value)
{
	m_value = value;
}

void TInteger::ReadValueStream(QDataStream& dataStream)const
{
	dataStream << m_value;
}

void TInteger::UpdateFromValue(const TVariate& variate)
{
	m_value = static_cast<const TInteger&>(variate).m_value;
}

void TInteger::SlotOnTextChanged(const QString& newValue)
{
	UpdateRamAndDatabaseFrom(TInteger(m_symbol.GetScope(), m_symbol.GetName(), newValue.toInt()));
}


TVariate* TInteger::Clone() const
{
	return new TInteger(*this);
}

void TInteger::ReadTreeWidgetItem(QTreeWidgetItem* parentItem, QTreeWidget* treeWidget)
{
	TreeWidgetItemWithVariate* VariateItem = new TreeWidgetItemWithVariate(parentItem, this);
	QTreeWidgetItem* item = new QTreeWidgetItem(VariateItem, QStringList{ "Value" });

	LineEditWithRegExpAndKeyboard* lineEditValue = new LineEditWithRegExpAndKeyboard(
		QString::number(m_value), RegExp::STR_REG_INT);

	treeWidget->setItemWidget(item, 1, lineEditValue);

	connect(lineEditValue, SIGNAL(textChanged(const QString&)), this, SLOT(SlotOnTextChanged(const QString&)));
}

