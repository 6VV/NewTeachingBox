#include "stdafx.h"
#include "TeachingBoxContext.h"
#include "User.h"
#include "Language.h"


namespace
{
	User g_user{};
	QString g_language = Language::ENGLISH;
	QPoint g_screenPos{};
	QPoint g_teachingBoxPos{};
	QSize g_screenSize{};
	QRect g_teachingBoxRect{};
	QRect g_screenRect{};
}

QString TeachingBoxContext::GetLanguage()
{
	return g_language;
}

User TeachingBoxContext::GetUser()
{
	return g_user;
}



QRect TeachingBoxContext::GetScreenRect()
{
	return QRect{ g_teachingBoxRect.left() + g_screenRect.left(),
		g_teachingBoxRect.top() + g_screenRect.top(),
		g_screenRect.width(),
		g_screenRect.height() };
	//return g_screenRect;
}

void TeachingBoxContext::SetTeachingBoxRect(const QRect& rect)
{
	g_teachingBoxRect = rect;
}

void TeachingBoxContext::SetScreenRect(const QRect& rect)
{
	g_screenRect = rect;
}

void TeachingBoxContext::SetLanguage(const QString& language)
{
	g_language = language;
}

void TeachingBoxContext::SetUser(const User& user)
{
	g_user = user;
}
