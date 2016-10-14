#ifndef _TEACHING_BOX_TREE_WIDGET_ITEM_WITH_VARIATE_H_
#define _TEACHING_BOX_TREE_WIDGET_ITEM_WITH_VARIATE_H_

#include "QTreeWidget"

class TVariate;

class TreeWidgetItemWithVariate:public QTreeWidgetItem
{
public:
	TreeWidgetItemWithVariate(QTreeWidgetItem* parentItem,TVariate* variate);
	~TreeWidgetItemWithVariate();
	
	void IsSave(bool isSave);

	void Variate(TVariate* variate);

private:
	TVariate* m_variate;
	bool m_isSave=false;
};

#endif