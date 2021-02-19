#include "stdafx.h"
#include "ScreenRobot.h"
#include "Button.h"
#include "DialogNewRobot.h"
#include "RobotDatabase.h"
#include "TeachingBoxBroadcast.h"

ScreenRobot::ScreenRobot(QWidget* parent /*= nullptr*/)
	:InternationalWidget(parent)
{
	initWidget();
	initSignalSlot();

	updateTable();
}

void ScreenRobot::UpdateText()
{
	if (addButton != nullptr)
	{
		addButton->setText(tr("Add"));
	}

	if (deleteButton != nullptr)
	{
		deleteButton->setText(tr("Delete"));
	}
}

void ScreenRobot::initWidget()
{
	tableWidget = new QTableWidget(this);
	tableWidget->setColumnCount(2);
	tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	tableWidget->setHorizontalHeaderLabels({tr("Name"),("ID")});

	addButton = new Button(this);
	deleteButton = new Button(this);

	auto buttonLayout = new QVBoxLayout();
	buttonLayout->addWidget(addButton);
	buttonLayout->addWidget(deleteButton);
	buttonLayout->addStretch(1);

	auto layout = new QHBoxLayout(this);
	layout->addWidget(tableWidget);
	layout->addLayout(buttonLayout);
	layout->setStretch(0, 1);
}

void ScreenRobot::initSignalSlot()
{
	connect(addButton, &QPushButton::clicked, [this]() {
		auto dialog = new DialogNewRobot(this);
		if (dialog->exec() == QDialog::Accepted) {
			updateTable();
		}
	});
	connect(deleteButton, &QPushButton::clicked, [this]() {
		auto item = tableWidget->currentItem();
		if (item == nullptr)
		{
			QMessageBox::information(this, tr("Information"), tr("Please select a robot"));
			return;
		}

		auto name = tableWidget->item(item->row(), 0)->text();
		if (QMessageBox::question(this, tr("Delete Robot"), tr("Confirm delete robot: %1").arg(name), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Cancel) == QMessageBox::Ok)
		{
			Database::RobotDatabase::deleteRobot(name);
			updateTable();
		}
	});
}

void ScreenRobot::updateTable()
{
	while (tableWidget->rowCount()>0)
	{
		tableWidget->removeRow(0);
	}

	auto robots = Database::RobotDatabase::selectRobot();
	for (int i = 0; i < robots.length(); ++i)
	{
		tableWidget->insertRow(i);
		tableWidget->setItem(i, 0, new QTableWidgetItem(robots[i].name));
		tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(robots[i].id)));
	}

	emit(TeachingBoxBroadcast::GetInstance()->RobotInfoChanged());
}
