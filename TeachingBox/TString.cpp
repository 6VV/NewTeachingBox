#include "stdafx.h"
#include "TString.h"
#include "TreeWidgetItemWithVariate.h"



TString::TString(const QString& scope, const QString& name, const QString& value)
	:TVariate(scope,name,TSymbol::TYPE_STRING)
{
	m_value = value;
}

TString::TString(QDataStream& dataStream) : TVariate(dataStream)
{
	dataStream >> m_value;
}

TString::TString(const TString& variate)
	: TVariate(variate)
{
	m_value = variate.m_value;
}

const QString& TString::GetValue() const
{
	return m_value;
}

void TString::SetValue(const QString& value)
{
	m_value = value;
}

void TString::ReadTreeWidgetItem(QTreeWidgetItem* parentItem, QTreeWidget* treeWidget)
{
	TreeWidgetItemWithVariate* VariateItem = new TreeWidgetItemWithVariate(parentItem, this);
	QTreeWidgetItem* item = new QTreeWidgetItem(VariateItem, QStringList("Value"));

	QLineEdit* lineEditValue = new QLineEdit(m_value);

	treeWidget->setItemWidget(item, 1, lineEditValue);

	connect(lineEditValue, SIGNAL(textChanged(const QString&)), this, SLOT(SlotOnTextChanged(const QString&)));
}

void TString::ReadValueStream(QDataStream& dataStream)const
{
	dataStream << m_value;
}

void TString::UpdateFromValue(const TVariate& variate)
{
	m_value = static_cast<const TString&>(variate).m_value;
}

void TString::SlotOnTextChanged(const QString& text)
{
	m_value = text;
	UpdateRamAndDatabaseFrom(*this);
}

TVariate* TString::Clone() const
{
	return new TString(*this);
}
