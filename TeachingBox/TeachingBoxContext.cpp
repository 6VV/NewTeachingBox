#include "stdafx.h"
#include "TeachingBoxContext.h"
#include "User.h"
#include "Language.h"
#include "TeachingBoxBroadcast.h"
#include "RemoteManager.h"
#include "TRefSys.h"
#include "TToolSys.h"


TeachingBoxContext* TeachingBoxContext::GetInstance()
{
	static TeachingBoxContext context;
	return &context;
}

TeachingBoxContext::TeachingBoxContext()
	:m_user(User{})
{
	m_language = m_user.GetLanguage();
}

std::shared_ptr<TVariate> TeachingBoxContext::GetCurrentRefSys()
{
	return m_currentRefSys;
}

std::shared_ptr<TVariate> TeachingBoxContext::GetCurrentToolSys()
{
	return m_currentToolSys;
}

TeachingBoxContext::JogState TeachingBoxContext::GetJogState()
{
	return m_jogState;
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

void TeachingBoxContext::SetCurrentRefSys(std::shared_ptr<TVariate> refSys)
{
	m_currentRefSys = refSys;

	tPoseEuler pose{};
	auto value = std::dynamic_pointer_cast<TRefSys>(m_currentRefSys)->GetValue();
	pose.m_PositionCartesian.m_X = value[0];
	pose.m_PositionCartesian.m_Y = value[1];
	pose.m_PositionCartesian.m_Z = value[2];
	pose.m_PostureEuler.m_A = value[3];
	pose.m_PostureEuler.m_B = value[4];
	pose.m_PostureEuler.m_C = value[5];

	RemoteManager::GetInstance()->SendSpecialCommand(CommandId::SET_JOG_REF_SYS, pose);
}

void TeachingBoxContext::SetCurrentToolSys(std::shared_ptr<TVariate> toolSys)
{
	m_currentToolSys = toolSys;

	tPoseEuler pose{};
	auto value = std::dynamic_pointer_cast<TToolSys>(m_currentToolSys)->GetValue();
	pose.m_PositionCartesian.m_X = value[0];
	pose.m_PositionCartesian.m_Y = value[1];
	pose.m_PositionCartesian.m_Z = value[2];
	pose.m_PostureEuler.m_A = value[3];
	pose.m_PostureEuler.m_B = value[4];
	pose.m_PostureEuler.m_C = value[5];

	RemoteManager::GetInstance()->SendSpecialCommand(CommandId::SET_JOG_TOOL_SYS, pose);
}

void TeachingBoxContext::SetIsMotOn(bool isMotOn)
{
	m_isMotOn = isMotOn;
}

void TeachingBoxContext::SetJog(JogState jogState)
{
	if (m_jogState != jogState)
	{
		m_jogState = jogState;
		emit(TeachingBoxBroadcast::GetInstance()->GetInstance()->JogStateChanged(jogState));
	}
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
