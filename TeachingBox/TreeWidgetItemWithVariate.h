#ifndef _TEACHING_BOX_TREE_WIDGET_ITEM_WITH_VARIATE_H_
#define _TEACHING_BOX_TREE_WIDGET_ITEM_WITH_VARIATE_H_

#include "QTreeWidget"

class TVariate;

class TreeWidgetItemWithVariate:public QTreeWidgetItem
{
public:
	TreeWidgetItemWithVariate(QTreeWidgetItem* parentItem,TVariate* variate);
	~TreeWidgetItemWithVariate();
	
private:
	TVariate* m_variate;
};

#endif