#include "stdafx.h"
#include "ScreenWarning.h"
#include "ConfirmButton.h"
#include "QBoxLayout"
#include "WarningModel.h"
#include "WarningInfo.h"
#include "DateDelegate.h"
#include "TeachingBoxBroadcast.h"



ScreenWarning::ScreenWarning(QWidget* parent /*= nullptr*/)
	:ScreenMainParent(parent)
	, m_btnConfirm(new ConfirmButton(this))
	, m_btnConfirmAll(new ConfirmButton(this))
	, m_btnDelete(new Button(this))
	, m_btnDeleteAll(new Button(this))
{
	UpdateText();

	connect(TeachingBoxBroadcast::GetInstance(), &TeachingBoxBroadcast::WarningThrowed, [this]{
		static bool isFirstAdd = true;
		if (isFirstAdd)
		{
			m_warningWidget->resizeColumnToContents(2);
		}
	});
	connect(m_btnConfirm, &Button::clicked, [this]{
		auto index = m_warningWidget->currentIndex();
		int row = index.row();
		if (!index.isValid()){
			row = m_model->NextToBeSolvedAtCurrentCategory();
		}

		m_model->SolveRowAtCurrentCategory(row);
		emit(TeachingBoxBroadcast::GetInstance()->WarningStateChanged());
	});
	connect(m_btnConfirmAll, &Button::clicked, [this]{
		m_model->SolveAllAtCurrentCategory();
		emit(TeachingBoxBroadcast::GetInstance()->WarningStateChanged()); 
	});
	connect(m_btnDelete, &Button::clicked, [this]{
		auto index = m_warningWidget->currentIndex();
		if (!index.isValid()){
			m_model->RemoveBack();
		}
		else{
			m_model->RemoveRow(index.row());
		}
		
	});
	connect(m_btnDeleteAll, &Button::clicked, [this]{
		m_model->RemoveAll();
	});
}

QList<QWidget*> ScreenWarning::GetButtonList()
{
	QList<QWidget*> result{};

	m_btnDelete->setIcon(QIcon(QPixmap(":/new/image/Resources/Image/wrong_icon.png")));
	m_btnDeleteAll->setIcon(QIcon(QPixmap(":/new/image/Resources/Image/wrong_icon.png")));

	result.append(m_btnConfirm);
	result.append(m_btnConfirmAll);
	result.append(m_btnDelete);
	result.append(m_btnDeleteAll);

	auto box = new QComboBox(this);
	box->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	box->addItem(QIcon(QPixmap(":/new/image/Resources/Image/all_icon.png")), tr("All"),WarningInfo::CATEGORY_ALL);
	box->addItem(QIcon(QPixmap(WarningModel::CATEFORY_INFO_ICON_PATH)), tr("Info"), WarningInfo::CATEFORY_INFO);
	box->addItem(QIcon(QPixmap(WarningModel::CATEFORY_WARNING_ICON_PATH)), tr("Warning"), WarningInfo::CATEFORY_WARNING);
	box->addItem(QIcon(QPixmap(WarningModel::CATEFORY_ERROR_ICON_PATH)), tr("Error"), WarningInfo::CATEFORY_ERROR);

	connect(box, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [this,box](int index){
		m_model->ChangeMode(static_cast<WarningInfo::Category>(box->itemData(index).toInt()));
	});

	result.append(box);

	/*Test按键仅用于测试*/
	auto btnTest = new Button("Test", this);
	btnTest->setToolTip(tr("just for test"));
	connect(btnTest, &Button::clicked, [this]{
		static int id = 0;
		emit(TeachingBoxBroadcast::GetInstance()->WarningThrowed(WarningInfo{ static_cast<WarningInfo::Id>(id%3), "Test "+QString::number(id++) }));
	});
	result.append(btnTest);

	return result;
}

QLayout* ScreenWarning::GetMainLayout()
{
	QVBoxLayout* layout = new QVBoxLayout(this);

	m_warningWidget = new QTableView(this);
	layout->addWidget(m_warningWidget);

	//m_warningWidget->horizontalHeader()->sectionResizeMode(QHeaderView::ResizeToContents);
	m_warningWidget->horizontalHeader()->sectionResized(0, 0, m_warningWidget->width() / 8);
	m_warningWidget->horizontalHeader()->sectionResized(0, 1, m_warningWidget->width() / 8);
	m_warningWidget->horizontalHeader()->sectionResized(0, 2, m_warningWidget->width() / 4);
	m_warningWidget->horizontalHeader()->setStretchLastSection(true);
	m_warningWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
	//m_warningWidget->setEditTriggers(QAbstractItemView::SelectedClicked);
	
	m_model = WarningModel::GetInstance();
	m_warningWidget->setModel(m_model);

	m_dateDelegate = new DateDelegate(this);
	m_warningWidget->setItemDelegateForColumn(2, m_dateDelegate);

	m_warningWidget->resizeColumnToContents(2);

	return layout;
}

void ScreenWarning::UpdateText()
{
	m_btnConfirm->setText(tr("Confirm"));
	m_btnConfirmAll->setText(tr("Confirm All"));

	m_btnDelete->setText(tr("Delete"));
	m_btnDeleteAll->setText(tr("Delete All"));
}



