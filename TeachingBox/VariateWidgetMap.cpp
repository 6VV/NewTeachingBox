#include "stdafx.h"
#include "VariateWidgetMap.h"
#include <assert.h>



VariateWidgetMap::VariateWidgetMapType& VariateWidgetMap::VaraiteWidgetMap()
{
	static VariateWidgetMapType map{};
	return map;
}

std::shared_ptr<VariateValueTreeWidgetItem> VariateWidgetMap::GetVariateWidget(const QString& type)
{
	auto iter = VaraiteWidgetMap().find(type);
	assert(iter != VaraiteWidgetMap().end());
	return iter->second;
}
