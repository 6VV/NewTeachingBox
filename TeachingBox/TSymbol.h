#ifndef _TEACHING_BOX_T_SYMBOL_H_
#define _TEACHING_BOX_T_SYMBOL_H_

#include "QString"
#include "QHash"
#include "QObject"

class TSymbol:public QObject
{
	Q_OBJECT
public:
	/*变量类型
	修改变量类型时需同时更新该枚举类型及CInitMap类*/
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
		TYPE_REF_SYS,
		TYPE_TOOL_SYS,
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

};

#endif
