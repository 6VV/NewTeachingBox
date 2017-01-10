#include "stdafx.h"
#include "VariateWidgetMap.h"
#include <assert.h>
#include "TVariateFactory.h"
#include "TComplex.h"



VariateWidgetMap::VariateWidgetMapType& VariateWidgetMap::VaraiteWidgetMap()
{
	static VariateWidgetMapType map{};
	return map;
}

std::shared_ptr<VariateValueTreeWidgetItem> VariateWidgetMap::GetVariateWidget(const QString& type)
{

	auto iter = VaraiteWidgetMap().find(type);

	if (iter == VaraiteWidgetMap().end())
	{
		auto fun = TVariateFactory::GetFun(type);
		assert(fun != nullptr);
		if (fun != nullptr)
		{
			iter = VaraiteWidgetMap().find(TComplex::TypeName());
		}
	}

	return iter->second;
}
