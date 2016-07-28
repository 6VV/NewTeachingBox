#include "stdafx.h"
#include "ScreenFactory.h"
#include "ScreenSetting.h"



ScreenFactory::~ScreenFactory()
{
	Clear();
}

QWidget* ScreenFactory::Create(const NScreenType::ScreenType type, QWidget* parent)
{
	auto result = Find(type);
	if (!result)
	{
		result = CreateWithoutCheck(type, parent);
		m_screens[type] = result;
	}

	return result;
}

void ScreenFactory::Destroy(const NScreenType::ScreenType type)
{
	delete Find(type);
	m_screens.remove(type);
}

void ScreenFactory::Clear()
{
	for (auto var : m_screens)
	{
		delete var;
	}
	m_screens.clear();
}

QWidget* ScreenFactory::Find(const NScreenType::ScreenType type)
{
	auto iter = m_screens.find(type);
	if (iter==m_screens.end())
	{
		return nullptr;
	}

	return iter.value();
}

QWidget* ScreenFactory::CreateWithoutCheck(const NScreenType::ScreenType type, QWidget* parent)
{
	switch (type)
	{
	case NScreenType::SETTING:{
		return new ScreenSetting(parent);
	}break;
	default:{
		return nullptr;
	}
	}
}

