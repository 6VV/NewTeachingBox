#include "stdafx.h"
#include "Language.h"


const std::map<QString, QString> Language::LANGUAGES{
	{ English(), "en" },
	{ Chinese(), "zh" },
};

const QString Language::English()
{
	return "English";
}

const QString Language::Chinese()
{
	return QStringLiteral("中文");
}

