#include "stdafx.h"
#include "TeachingBoxContext.h"
#include "User.h"
#include "Language.h"


TeachingBoxContext* TeachingBoxContext::GetInstance()
{
	static TeachingBoxContext context;
	return &context;
}

TeachingBoxContext::TeachingBoxContext()
	:m_language(Language::English())
{

}

QString TeachingBoxContext::GetLanguage()
{
	return m_language;
}

User TeachingBoxContext::GetUser()
{
	return m_user;
}



QRect TeachingBoxContext::GetScreenRect()
{
	return QRect{ m_teachingBoxRect.left() + m_screenRect.left(),
		m_teachingBoxRect.top() + m_screenRect.top(),
		m_screenRect.width(),
		m_screenRect.height() };
	//return g_screenRect;
}

bool TeachingBoxContext::IsServoOn()
{
	return m_isServoOn;
}

void TeachingBoxContext::SetIsMotOn(bool isMotOn)
{
	m_isMotOn = isMotOn;
}

bool TeachingBoxContext::IsMotOn()
{
	return m_isMotOn;
}

void TeachingBoxContext::SetTeachingBoxRect(const QRect& rect)
{
	m_teachingBoxRect = rect;
}

void TeachingBoxContext::SetScreenRect(const QRect& rect)
{
	m_screenRect = rect;
}

void TeachingBoxContext::SetIsServoOn(bool isServoOn)
{
	m_isServoOn = isServoOn;
}

void TeachingBoxContext::SetLanguage(const QString& language)
{
	m_language = language;
}

void TeachingBoxContext::SetUser(const User& user)
{
	m_user = user;
}
