#ifndef _TEACHING_BOX_TEST_TREE_WIDGET_ITEM_H_
#define _TEACHING_BOX_TEST_TREE_WIDGET_ITEM_H_

#include "QTreeWidget"
#include "QDebug"

class TestTreeWidgetItem:public QTreeWidgetItem
{
public:
	TestTreeWidgetItem(const QString& text);
	~TestTreeWidgetItem(){ qDebug() << "delete treeWidgetItem"; };
	
};

class TestTreeWidget:public QWidget
{
	Q_OBJECT

public:
	TestTreeWidget();

private slots:
	void SlotOnAddItem();
	void SlotOnClearItem();

private:
	QTreeWidget* m_treeWidget;
	QPushButton* m_btnAddItem;
	QPushButton* m_btnClear;
};

#endif