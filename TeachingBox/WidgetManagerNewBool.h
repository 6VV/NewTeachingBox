#ifndef _TEACHING_BOX_VARIATE_WIDGET_WIDGET_MANAGER_NEW_BOOL_H_
#define _TEACHING_BOX_VARIATE_WIDGET_WIDGET_MANAGER_NEW_BOOL_H_

#include "WidgetManagerNewVariate.h"

namespace VariateWidget
{
	class WidgetManagerNewBool:public WidgetManagerNewVariate
	{
	public:
		WidgetManagerNewBool(QTableWidget* tableWidget, int startRowCount);
		~WidgetManagerNewBool();

		virtual std::shared_ptr<TVariate> GetVariate(const QString& name, const QString& scope) override;

		virtual void InitParameter() override;

	};
}

#endif