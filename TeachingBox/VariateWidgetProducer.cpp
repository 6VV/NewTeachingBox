#include "stdafx.h"
#include "VariateWidgetProducer.h"
#include "TVariate.h"
#include "ComboBoxWithParentTreeItem.h"
#include "ProjectContext.h"



const QString VariateWidgetProducer::IMAGE_LOGO_SYSTEM{ ":/new/image/Resources/Image/S.PNG" };

const QString VariateWidgetProducer::IMAGE_LOGO_COORPERATER{ ":/new/image/Resources/Image/C.PNG" };

const QString VariateWidgetProducer::IMAGE_LOGO_GLOBAL{ ":/new/image/Resources/Image/G.PNG" };

const QString VariateWidgetProducer::IMAGE_LOGO_PROJECT{ ":/new/image/Resources/Image/P.PNG" };

const QString VariateWidgetProducer::IMAGE_LOGO_LOCAL{ ":/new/image/Resources/Image/L.PNG" };

const QMap<VariateWidgetProducer::SymbolType, QString> VariateWidgetProducer::TYPE_HEADER_MAP{
	{ SymbolType::TYPE_POSITION, "p" },
	{ SymbolType::TYPE_DYNAMIC, "dyn" },
	{ SymbolType::TYPE_OVERLAP, "ovl" },
};

VariateWidgetProducer::VariateWidgetProducer()
{

}

VariateWidgetProducer::~VariateWidgetProducer()
{

}

QMap<QString, QStringList> VariateWidgetProducer::GetVariateMap(SymbolType type, const QMap<QString, QVector<TVariate*>>& variateMap) const
{
	QMap<QString, QStringList> result;

	for (auto iter = variateMap.begin(); iter != variateMap.end(); ++iter)
	{
		QStringList variateNames;
		for (auto variate : iter.value())
		{
			if (variate->GetType() == type)
			{
				variateNames.append(variate->GetName());
			}
		}

		result[iter.key()] = variateNames;
	}

	return result;
}

ComboBoxWithParentItem* VariateWidgetProducer::GetComboBox(SymbolType type, const QMap<QString, QVector<TVariate*>>& variateMap, QWidget* parent/*=nullptr*/) const
{

	auto variateComboBox = new ComboBoxWithParentItem(parent);
	auto variates = GetVariateMap(type, variateMap);

	for (auto iter = variates.begin(); iter != variates.end(); ++iter)
	{
		QIcon icon;
		if (iter.key() == ProjectContext::ScopeSystem())
		{
			icon.addPixmap(QPixmap(IMAGE_LOGO_SYSTEM));
		}
		else if (iter.key() == ProjectContext::ScopeCooperate())
		{
			icon.addPixmap(QPixmap(IMAGE_LOGO_COORPERATER));
		}
		else if (iter.key() == ProjectContext::ScopeGlobal())
		{
			icon.addPixmap(QPixmap(IMAGE_LOGO_GLOBAL));
		}
		else
		{
			if (iter.key().contains("."))
			{
				icon.addPixmap(QPixmap(IMAGE_LOGO_LOCAL));
			}
			else
			{
				icon.addPixmap(QPixmap(IMAGE_LOGO_PROJECT));
			}
		}

		for (auto var : iter.value())
		{
			variateComboBox->addItem(icon, var);
		}
	}

	return variateComboBox;
}

QString VariateWidgetProducer::GetSuggestName(SymbolType type, const QMap<QString, QVector<TVariate*>>& variateMap) const
{
	std::vector<int> suggestNamesExisted;

	auto header = TYPE_HEADER_MAP[type];

	QRegExp regExp("^" + header + "([0 - 9] + )$");
	for (auto iter = variateMap.begin(); iter != variateMap.end(); ++iter)
	{
		for (auto variate : iter.value())
		{
			if (regExp.exactMatch(variate->GetName()))
			{
				suggestNamesExisted.push_back(regExp.capturedTexts().at(1).toInt());
			}
		}
	}

	std::sort(suggestNamesExisted.begin(), suggestNamesExisted.end());

	int size = suggestNamesExisted.size();
	for (int i = 0; i < size; ++i)
	{
		if (suggestNamesExisted.at(i) != i)
		{
			return header + QString::number(i);
		}
	}

	return header + QString::number(suggestNamesExisted.size());
}

