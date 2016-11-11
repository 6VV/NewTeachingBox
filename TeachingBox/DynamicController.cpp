#include "stdafx.h"
#include "DynamicController.h"
#include <thread>
#include <chrono>
#include <future>

double DynamicController::Dynovr() const
{
	return m_dynovr;
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
		++m_dynovr;
		return;
	}

}

void DynamicController::AccelerateThread()
{
	while (m_isOperateDyn)
	{
		if (++m_dynovr > 100)
		{
			m_dynovr = 100;
			break;
		}

		UpdateLabels();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

inline
void DynamicController::UpdateLabels()
{
	for (auto label : m_lables)
	{
		label->setText(DynovrText());
	}
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
		--m_dynovr;
		return;
	}
}

void DynamicController::DecelerateThread()
{
	while (m_isOperateDyn)
	{
		if (--m_dynovr < 0)
		{
			m_dynovr = 0;
			break;
		}

		UpdateLabels();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void DynamicController::Stop()
{
	m_isOperateDyn = false;
}

inline
const QString DynamicController::DynovrText() const
{
	return QString::number(m_dynovr) + QString("%");
}

void DynamicController::AddLabel(QLabel* label)
{
	m_lables.push_back(label);

	label->setText(DynovrText());
}

DynamicController* DynamicController::GetInstance()
{
	return SingleTon<DynamicController>::GetInstance();
}
