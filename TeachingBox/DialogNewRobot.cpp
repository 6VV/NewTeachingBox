#include "stdafx.h"
#include "DialogNewRobot.h"
#include "Button.h"
#include "TeachingBoxContext.h"
#include "QMessageBox"
#include "RobotDatabase.h"

DialogNewRobot::DialogNewRobot(QWidget* parent)
	:QDialog(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);
	setModal(true);
	setFixedWidth(400);

	initWidget();
	initSignalSlot();
}

void DialogNewRobot::initWidget()
{
	//输入框布局
	nameLineEdit = new QLineEdit(this);
	auto nameLabel = new QLabel(tr("Name"), this);
	idSpinBox = new QSpinBox(this);
	auto idLabel = new QLabel("ID", this);

	auto inputLayout = new QGridLayout();
	inputLayout->addWidget(nameLabel, 0, 0);
	inputLayout->addWidget(nameLineEdit, 0, 1);
	inputLayout->addWidget(idLabel, 1, 0);
	inputLayout->addWidget(idSpinBox, 1, 1);


	//按钮布局
	confirmButton = new Button(tr("Confirm"), this);
	cancelButton = new Button(tr("Cancel"), this);
	confirmButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	cancelButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

	QHBoxLayout* btnLayout = new QHBoxLayout();
	btnLayout->addStretch(1);
	btnLayout->addWidget(confirmButton);
	btnLayout->addWidget(cancelButton);

	//全局布局
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addLayout(inputLayout);
	layout->addLayout(btnLayout);
}

void DialogNewRobot::initSignalSlot()
{
	connect(confirmButton, &QPushButton::clicked, [this]() {
		auto name = nameLineEdit->text();
		auto id = idSpinBox->value();

		if (name.isEmpty())
		{
			QMessageBox::warning(this, tr("Warning"), tr("Name cann't be empty"));
			return;
		}

		if (Database::RobotDatabase::existRobotName(name)) {
			QMessageBox::warning(this, tr("Warning"), tr("Already exist robot name: %1").arg(name));
			return;
		}

		if (Database::RobotDatabase::existRobotId(id)) {
			QMessageBox::warning(this, tr("Warning"), tr("Already exist robot id: %1").arg(id));
			return;
		}

		Database::RobotDatabase::insertRobot(name, id);

		accept();
	});

	connect(cancelButton, &QPushButton::clicked, [this]() {
		reject();
	});
}
