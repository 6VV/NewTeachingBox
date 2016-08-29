#include "stdafx.h"
#include "User.h"
#include "Language.h"



User::User()
	:m_name("")
	, m_password("")
	, m_authority(1)
	, m_language(Language::ENGLISH)
{

}

User::User(const QString& name, const QString& password, int authority, const QString& language)
	:m_name(name)
	, m_password(password)
	, m_authority(authority)
	, m_language(language)
{

}

QString User::GetName() const
{
	return m_name;
}

QString User::GetPassword() const
{
	return m_password;
}

int User::GetAuthority() const
{
	return m_authority;
}

QString User::GetLanguage() const
{
	return m_language;
}

