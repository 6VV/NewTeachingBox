#include "stdafx.h"
#include "VariateWidgetProducer.h"
#include "TVariate.h"
#include "ProjectContext.h"
#include "TPosition.h"
#include "TDynamic.h"
#include "TOverlap.h"



const QString VariateWidgetProducer::IMAGE_LOGO_SYSTEM{ ":/new/image/Resources/Image/S.PNG" };

const QString VariateWidgetProducer::IMAGE_LOGO_COORPERATER{ ":/new/image/Resources/Image/C.PNG" };

const QString VariateWidgetProducer::IMAGE_LOGO_GLOBAL{ ":/new/image/Resources/Image/G.PNG" };

const QString VariateWidgetProducer::IMAGE_LOGO_PROJECT{ ":/new/image/Resources/Image/P.PNG" };

const QString VariateWidgetProducer::IMAGE_LOGO_LOCAL{ ":/new/image/Resources/Image/L.PNG" };


const QMap<QString, QString> VariateWidgetProducer::TYPE_HEADER_NAME_MAP{
	{ TPosition::TypeName(), "p" },
	{ TDynamic::TypeName(), "dyn" },
	{ TOverlap::TypeName(), "ovl" },
};


VariateWidgetProducer::VariateWidgetProducer()
{

}

VariateWidgetProducer::~VariateWidgetProducer()
{

}

QMap<QString, QStringList> VariateWidgetProducer::GetVariateMap(SymbolType type, const QMap<QString, QVector<std::shared_ptr<TVariate>>>& variateMap)
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

QString VariateWidgetProducer::GetSuggestName(const QString& typeName, const QMap<QString, QVector<std::shared_ptr<TVariate>>>& variateMap)
{
	std::vector<int> suggestNamesExisted;

	auto header = TYPE_HEADER_NAME_MAP[typeName];

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

void VariateWidgetProducer::UpdateComboBoxWithWholeName(const QString& typeName, const QMap<QString, QVector<std::shared_ptr<TVariate>>>& variateMap, QComboBox* comboBox)
{
	comboBox->clear();

	auto variates = std::move(GetVariateMap(typeName, variateMap));

	for (auto iter = variates.begin(); iter != variates.end(); ++iter)
	{
		for (auto var : iter.value())
		{
			QIcon icon(QPixmap(GetIconPath(iter.key())));
			comboBox->addItem(icon, iter.key() + "." + var);
		}
	}
}

void VariateWidgetProducer::UpdateComboBoxWithSimpleName(const QString& typeName, const QMap<QString, QVector<std::shared_ptr<TVariate>>>& variateMap, QComboBox* comboBox)
{
	comboBox->clear();

	auto variates = std::move(GetVariateMap(typeName, variateMap));

	for (auto iter = variates.begin(); iter != variates.end(); ++iter)
	{
		for (auto var : iter.value())
		{
			comboBox->addItem(QIcon(GetIconPath(iter.key())), var);
		}
	}
}

QString VariateWidgetProducer::GetIconPath(const QString& scope)
{
	if (scope == ProjectContext::ScopeSystem())
	{
		return IMAGE_LOGO_SYSTEM;
	}
	else if (scope == ProjectContext::ScopeCooperate())
	{
		return IMAGE_LOGO_COORPERATER;
	}
	else if (scope == ProjectContext::ScopeGlobal())
	{
		return IMAGE_LOGO_GLOBAL;
	}
	else
	{
		if (scope.contains("."))
		{
			return IMAGE_LOGO_LOCAL;
		}
		else
		{
			return IMAGE_LOGO_PROJECT;
		}
	}
}

QMap<QString, QStringList> VariateWidgetProducer::GetVariateMap(const QString& typeName, const QMap<QString, QVector<std::shared_ptr<TVariate>>>& variateMap)
{
	QMap<QString, QStringList> result;

	for (auto iter = variateMap.begin(); iter != variateMap.end(); ++iter)
	{
		QStringList variateNames;
		for (auto variate : iter.value())
		{
			if (variate->GetTypeName() == typeName)
			{
				variateNames.append(variate->GetName());
			}
		}

		result[iter.key()] = variateNames;
	}

	return result;
}
