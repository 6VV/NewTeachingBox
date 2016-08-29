#ifndef _TEACHING_BOX_LANGUAGE_H_
#define _TEACHING_BOX_LANGUAGE_H_

#include <map>
#include "QString"

class Language
{
public:
	static const QString ENGLISH;
	static const QString CHINESE;

	static const std::map<QString, QString> LANGUAGES;
};

#endif