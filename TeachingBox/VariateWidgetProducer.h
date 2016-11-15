#ifndef _TEACHING_BOX_VARIATE_WIDGET_RPODUCER_H_
#define _TEACHING_BOX_VARIATE_WIDGET_RPODUCER_H_

#include "QString"
#include "TSymbol.h"

class TVariate;
class ComboBoxWithParentItem;

class VariateWidgetProducer
{
	typedef TSymbol::SymbolType SymbolType;
	static const QMap<SymbolType, QString> TYPE_HEADER_MAP;

public:
	static const QString IMAGE_LOGO_SYSTEM;
	static const QString IMAGE_LOGO_COORPERATER;
	static const QString IMAGE_LOGO_GLOBAL;
	static const QString IMAGE_LOGO_PROJECT;
	static const QString IMAGE_LOGO_LOCAL;

public:
	VariateWidgetProducer();
	~VariateWidgetProducer();

	/*获取某类型变量的comboBox控件*/
	ComboBoxWithParentItem* GetComboBox(SymbolType type, const QMap<QString, QVector<TVariate*>>& variateMap,QWidget* parent = nullptr) const;
	
	QString GetSuggestName(SymbolType type, const QMap<QString, QVector<TVariate*>>& variateMap) const;	/*获取建议的名字*/

private:
	/*获取作用域中某类型变量*/
	QMap<QString, QStringList> GetVariateMap(SymbolType type, const QMap<QString, QVector<TVariate*>>& variateMap) const;

private:

};

#endif