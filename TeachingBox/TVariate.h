#ifndef _TEACHING_BOX_TVARIATE_H_
#define _TEACHING_BOX_TVARIATE_H_

#include "TSymbol.h"

class TVariateWidget;
class TreeWidgetItemWithVariate;

class TVariate:public QObject
{
	Q_OBJECT

public:
	typedef QSet<TVariate*> SET;

public:
	TVariate(const QString& scope, const QString& name,TSymbol::SymbolType type);
	TVariate(const TVariate& variate);
	TVariate(QDataStream& dataStream);
	virtual ~TVariate();

public:
	virtual TVariate* Clone() const = 0;

	QString GetScope() const;
	QString GetName() const;
	TSymbol::SymbolType GetType() const;

	void SetName(const QString& name);
	void Save();

	void ReadContentIntoItem(TreeWidgetItemWithVariate* parentItem, QTreeWidget* treeWidget);

	void ReadTreeWidgetItem(QTreeWidgetItem* parentItem, QTreeWidget* treeWidget);
	void ReadTreeWidgetItem(QTreeWidgetItem* parentItem, QTreeWidget* treeWidget, 
		const TSymbol::SymbolType type);

	void ReadDataStream(QDataStream& dataStream) const;
	void ReadCollection(SET& collection,const TSymbol::SymbolType type);

	void UpdateFromVariate(const TVariate& variate);

protected:
	virtual void ReadValueStream(QDataStream& dataStream) const=0;
	virtual void UpdateFromValue(const TVariate& variate) =0;

	void UpdateRamAndDatabaseFrom(const TVariate& variate) const;

protected:
	TSymbol m_symbol;

	TVariateWidget* m_variateWidget=nullptr;
};

#endif