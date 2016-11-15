#include "stdafx.h"
#include "ScreenManager.h"
#include "QStackedWidget"
#include "ScreenService.h"
#include "ScreenVariate.h"
#include "ScreenProject.h"
#include "ScreenProgram.h"
#include "ScreenCoordinate.h"



ScreenManager* ScreenManager::GetInstance()
{
	return SingleTon<ScreenManager>::GetInstance();
}

void ScreenManager::ChangeScreen(ScreenType screenType)
{
	if (m_mainWidget==nullptr)
	{
		return;
	}

	QWidget* widget = GetScreen(screenType, m_mainWidget);
	if (m_mainWidget->indexOf(widget) == -1)
	{
		m_mainWidget->addWidget(widget);
	}
	m_mainWidget->setCurrentWidget(widget);

}

QWidget* ScreenManager::GetWidget(QWidget* parent)
{
	if (m_mainWidget==nullptr)
	{
		m_mainWidget = new QStackedWidget(parent);
	}

	return m_mainWidget;
}

ScreenManager::ScreenManager()
{
}

QWidget* ScreenManager::GetScreen(const ScreenType type, QWidget* parent)
{
	auto result = Find(type);
	if (!result)
	{
		result = CreateWithoutCheck(type, parent);
		m_screens[type] = result;
	}

	return result;
}

QWidget* ScreenManager::CreateWithoutCheck(const ScreenType type, QWidget* parent)
{
	switch (type)
	{
	case ScreenType::SERVICE:{
		return new ScreenService(parent);
	}break;
	case ScreenType::VARIATE:{
		return new ScreenVariate(parent);
	}break;
	case ScreenType::PROJECT:{
		return new ScreenProject(parent);
	}break;
	case ScreenType::PROGRAM:{
		return new ScreenProgram(parent);
	}break;
	case ScreenType::COORDINATE:{
		return new ScreenCoordiante(parent);
	}break;
	default:{
		return nullptr;
	}
	}
}

QWidget* ScreenManager::Find(const ScreenType type)
{
	auto iter = m_screens.find(type);
	if (iter == m_screens.end())
	{
		return nullptr;
	}

	return iter.value();
}
