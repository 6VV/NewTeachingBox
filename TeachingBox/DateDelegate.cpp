#include "stdafx.h"
#include "DateDelegate.h"
#include "QDateTimeEdit"
#include "WarningInfo.h"



DateDelegate::DateDelegate(QObject* parent /*= nullptr*/)
	:QItemDelegate(parent)
{

}

QWidget * DateDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, const QModelIndex &index) const
{
	QDateTimeEdit* editor = new QDateTimeEdit(parent);
	editor->setDisplayFormat(WarningInfo::DATE_TIME_FORMAT);
	editor->setCalendarPopup(true);
	editor->installEventFilter(const_cast<DateDelegate*>(this));

	setEditorData(editor, index);

	return editor;
}

void DateDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	auto dateStr = index.model()->data(index).toString();
	auto dateTime = QDateTime::fromString(dateStr, WarningInfo::DATE_TIME_FORMAT);
	static_cast<QDateTimeEdit*>(editor)->setDateTime(dateTime);
}

void DateDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	auto dateTime = static_cast<QDateTimeEdit*>(editor)->dateTime();
	model->setData(index, dateTime.toString(WarningInfo::DATE_TIME_FORMAT));
}

void DateDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/*index*/) const
{
	editor->setGeometry(option.rect);
}
