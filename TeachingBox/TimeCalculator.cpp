#include "stdafx.h"
#include "TimeCalculator.h"
#include <chrono>


std::chrono::steady_clock::time_point TimeCalculator::m_startTime{};

void TimeCalculator::Start()
{
	m_startTime=std::chrono::steady_clock::now();
}

void TimeCalculator::End(const QString& text/*=""*/)
{
	qDebug() << text + " : " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_startTime).count();
	m_startTime = std::chrono::steady_clock::now();
}

