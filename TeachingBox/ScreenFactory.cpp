#include "stdafx.h"
#include "ScreenFactory.h"
#include "ScreenService.h"


ScreenFactory::~ScreenFactory()
{
	Clear();
}

QWidget* ScreenFactory::Create(const ScreenType::ScreenType type, QWidget* parent)
{
	auto result = Find(type);
	if (!result)
	{
		result = CreateWithoutCheck(type, parent);
		m_screens[type] = result;
	}

	return result;
}

void ScreenFactory::Destroy(const ScreenType::ScreenType type)
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

QWidget* ScreenFactory::Find(const ScreenType::ScreenType type)
{
	auto iter = m_screens.find(type);
	if (iter==m_screens.end())
	{
		return nullptr;
	}

	return iter.value();
}

QWidget* ScreenFactory::CreateWithoutCheck(const ScreenType::ScreenType type, QWidget* parent)
{
	switch (type)
	{
	case ScreenType::SERVICE:{
		return new ScreenService(parent);
	}break;
	default:{
		return nullptr;
	}
	}
}

