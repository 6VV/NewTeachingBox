#ifndef _TEACHING_BOX_LANGUAGE_H_
#define _TEACHING_BOX_LANGUAGE_H_

#include <map>
#include "QString"

class Language
{
public:
	static const QString English();
	static const QString Chinese();

	static const std::map<QString, QString> LANGUAGES;
};

#endif