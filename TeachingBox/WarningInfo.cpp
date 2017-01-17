#include "stdafx.h"
#include "WarningInfo.h"



const QString WarningInfo::DATE_TIME_FORMAT = "yyyy-MM-dd hh:mm:ss";


WarningInfo::WarningInfo(const WarningInfo& warningInfo)
	:m_id(warningInfo.m_id)
	, m_category(warningInfo.m_category)
	, m_state(warningInfo.m_state)
	, m_dateTime(warningInfo.m_dateTime)
	, m_describe(warningInfo.m_describe)
{

}

WarningInfo::WarningInfo(Id id, const QString& describe/* = {}*/, const QDateTime& dateTime /*= QDateTime::currentDateTime()*/)
	:m_id(id)
	, m_dateTime(dateTime.toString(DATE_TIME_FORMAT))
	, m_describe(describe)
{
	auto iter = s_warningMap.find(id);
	if (iter == s_warningMap.end())
	{
		m_category = Category::CATEFORY_INFO;
		m_state = State::STATE_WITHOUT_SOLVE;
	}
	else
	{
		m_category = iter->second.category;
		m_state = iter->second.state;
		if (m_describe.isEmpty())
		{
			m_describe = iter->second.describe;
		}
	}
}

QString WarningInfo::GetDateTime() const
{
	return m_dateTime;
}

QString WarningInfo::GetDescribe() const
{
	return m_describe;
}

WarningInfo::Category WarningInfo::GetCategory() const
{
	return m_category;
}

WarningInfo::State WarningInfo::GetState() const
{
	return m_state;
}

void WarningInfo::SetDateTime(const QString& dateTime)
{
	m_dateTime = dateTime;
}

void WarningInfo::SetState(State state)
{
	m_state = state;
}

std::map<WarningInfo::Id, WarningInfo::WarningMapInfo> WarningInfo::s_warningMap{
	{ Id::ID_INTERPERTER_ERROR, {Category::CATEFORY_INFO,"interpreter error",WarningInfo::STATE_WITHOUT_SOLVE} },
	{ Id::ID_INTERNET_DISCONNECT, { Category::CATEFORY_ERROR, "internet disconnect", WarningInfo::STATE_TO_BE_SOLVED } },
	{ Id::ID_WARNING_TEST, { Category::CATEFORY_WARNING, "internet disconnect", WarningInfo::STATE_TO_BE_SOLVED } },
	{ Id::ID_PRESS_AUTO_SERVO_BUTTON_AT_MANUAL_MODE, { Category::CATEFORY_ERROR, tr("cann't press auto servo button at manual mode"), WarningInfo::STATE_TO_BE_SOLVED } },
	{ Id::ID_PRESS_MANUAL_SERVO_BUTTON_AT_AUTO_MODE, { Category::CATEFORY_ERROR, tr("cann't press manual servo button at auto mode"), WarningInfo::STATE_TO_BE_SOLVED } },
};

WarningInfo::WarningMapInfo::WarningMapInfo(Category category, const QString& describe, State state)
	:category(category)
	, describe(describe)
	, state(state)
{

}
