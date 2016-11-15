#ifndef _TEACHING_BOX_T_REF_SYS_WIDGET_H_
#define _TEACHING_BOX_T_REF_SYS_WIDGET_H_

#include "TVariateWidget.h"
#include "TRefSys.h"

class TRefSysWidget :public TVariateWidget
{
public:
	TRefSysWidget(TRefSys* variate);
	~TRefSysWidget();

	virtual void UpdateVariate() override;

private:
	virtual void OnValueChanged() override;
	virtual void WriteContentToTreeWidgetItem(QTreeWidgetItem* parentItem, QTreeWidget* treeWidget) override;

private:
	TRefSys::ValueType m_value;
};

#endif