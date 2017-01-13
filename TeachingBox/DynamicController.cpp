#include "stdafx.h"
#include "DynamicController.h"
#include <thread>
#include <chrono>
#include <future>

double DynamicController::Speed() const
{
	return m_speed;
}

/*************************************************
//  Function: 		DynamicController::Accelerate()
//  Description: 	用于连续增加动态倍率参数，每次增加1。
//					增加过程放于单独的线程中，若无法放于其它线程中，则将动态倍率参数增加1。
//  Parameter:      void
//  Return: 		void
//  Others: 		
*************************************************/
void DynamicController::Accelerate()
{
	m_isOperateDyn = true;

	try
	{
		/*强制必须异步调用*/
		std::async(std::launch::async, &DynamicController::AccelerateThread, this);
	}
	catch (std::exception&)
	{
		/*若无法异步调用，每次增加1*/
		++m_speed;
		return;
	}

}

void DynamicController::AccelerateThread()
{
	while (m_isOperateDyn)
	{
		if (++m_speed > 100)
		{
			m_speed = 100;
			break;
		}

		UpdateSpeed();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

inline
void DynamicController::UpdateSpeed()
{
	m_speedComboBox->setCurrentText(SpeedText(m_speed));
}

void DynamicController::Decelerate()
{
	m_isOperateDyn = true;

	try
	{
		std::async(std::launch::async, &DynamicController::DecelerateThread, this);
	}
	catch (std::exception&)
	{
		/*若无法异步调用，每次减去1*/
		--m_speed;
		return;
	}
}

void DynamicController::DecelerateThread()
{
	while (m_isOperateDyn)
	{
		if (--m_speed < 0)
		{
			m_speed = 0;
			break;
		}

		UpdateSpeed();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

const QString DynamicController::SpeedText(double speed) const
{
	return QString::number(speed) + QString("%");
}

void DynamicController::Stop()
{
	m_isOperateDyn = false;
}

void DynamicController::AddWidget(QComboBox* speedComboBox)
{
	m_speedComboBox = speedComboBox;

	connect(speedComboBox, static_cast<void(QComboBox::*)(const QString& text)>(&QComboBox::activated), [this](const QString& text){
		m_speed = text.left(text.size() - 1).toDouble();
	});
}

DynamicController* DynamicController::GetInstance()
{
	return SingleTon<DynamicController>::GetInstance();
}
