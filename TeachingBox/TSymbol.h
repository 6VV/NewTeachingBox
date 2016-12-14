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
		//TYPE_POSITION,
		//TYPE_DYNAMIC,
		//TYPE_OVERLAP,
		TYPE_COMPLEX
	};

	enum SymbolCategory
	{
		CATEGORY_METHOD,
		CATEGORY_VARIABLE,
	};

	typedef QString TypeNameType;

	//static QHash<SymbolType, QString> Map_Type;

public:
	TSymbol(const QString& scope="", const QString& name="", const SymbolType type = SymbolType::TYPE_VOID,
		const QString& typeName="",const SymbolCategory category = SymbolCategory::CATEGORY_VARIABLE);
	TSymbol(QDataStream& dataStream);
	TSymbol(const TSymbol& symbol);
	TSymbol& operator=(const TSymbol& symbol);

	SymbolType GetType() const;
	SymbolCategory GetCategory() const;
	QString GetName() const;
	QString GetScope() const;
	QString GetTypeName() const;

	//void SetName(const QString& name);

	void WriteToStream(QDataStream& dataStream) const;

protected:
	QString m_scope;
	QString m_name;
	QString m_typeName;
	int m_type=TYPE_VOID;
	SymbolCategory m_category=CATEGORY_VARIABLE;

};

#endif
