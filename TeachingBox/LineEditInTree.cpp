#include "stdafx.h"
#include "LineEditInTree.h"



LineEditInTree::LineEditInTree(QTreeWidgetItem* const parentItem, QTreeWidget* const treeWidget, 
	const QString& text/*=""*/, const QString& regExp/*=CRegExpManager::STR_REG_ANY_CHAR*/)
	:LineEditWithRegExpAndKeyboard(text,regExp,treeWidget)
	, WidgetItemInTree(parentItem,treeWidget)
{
}

LineEditInTree::~LineEditInTree()
{

}
