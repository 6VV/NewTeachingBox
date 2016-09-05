#ifndef _TEACHING_BOX_T_SYMBOL_H_
#define _TEACHING_BOX_T_SYMBOL_H_

#include "QString"
#include "QObject"
#include "QHash"

class TSymbol:public QObject
{
	Q_OBJECT
public:
	enum SymbolType
	{
		TYPE_VOID,
		TYPE_INTERGER,
		TYPE_DOUBLE,
		TYPE_STRING,
		TYPE_BOOL,
		TYPE_POSITION,
		TYPE_DYNAMIC,
		TYPE_OVERLAP,
	};

	enum SymbolCategory
	{
		CATEGORY_METHOD,
		CATEGORY_VARIABLE,
	};

	static QHash<SymbolType, QString> Map_Type;

public:
	TSymbol(const QString& scope, const QString& name, const SymbolCategory category, const SymbolType type);
	TSymbol(QDataStream& dataStream);
	TSymbol(const TSymbol& symbol);
	TSymbol& operator=(const TSymbol& symbol);

	SymbolType GetType() const;
	SymbolCategory GetCategory() const;
	QString GetName() const;
	QString GetScope() const;

	void SetName(const QString& name);

	void ReadDataStream(QDataStream& dataStream) const;

protected:
	QString m_scope;
	QString m_name;
	int m_type=TYPE_VOID;
	SymbolCategory m_category=CATEGORY_VARIABLE;

private:
	class CInitMap
	{
	public:
		CInitMap(QHash<TSymbol::SymbolType, QString>& mapType)
		{
			mapType.insert(TYPE_VOID, "VOID");
			mapType.insert(TYPE_INTERGER, "INTERGER");
			mapType.insert(TYPE_DOUBLE, "DOUBLE");
			mapType.insert(TYPE_STRING, "STRING");
			mapType.insert(TYPE_BOOL, "BOOL");
			mapType.insert(TYPE_POSITION, "POSITION");
			mapType.insert(TYPE_DYNAMIC, "DYNAMIC");
			mapType.insert(TYPE_OVERLAP, "OVERLAP");
		}
	};
	static CInitMap m_init;


};

#endif