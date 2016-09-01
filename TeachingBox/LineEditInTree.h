#ifndef _TEACHING_BOX_LINE_EIDT_IN_TREE_H_
#define _TEACHING_BOX_LINE_EIDT_IN_TREE_H_

#include "LineEditWithRegExpAndKeyboard.h"
#include "WidgetItemInTree.h"

class LineEditInTree:public LineEditWithRegExpAndKeyboard,public WidgetItemInTree
{
public:
	LineEditInTree(QTreeWidgetItem* const parentItem,QTreeWidget* const treeWidget,
		const QString& text="", const QString& regExp=RegExp::STR_REG_ANY_CHAR);
	~LineEditInTree();
	
private:
};

#endif