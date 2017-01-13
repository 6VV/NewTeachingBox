#include "stdafx.h"
#include "ScreenToolSystem.h"
#include "Button.h"
#include "LineEditWithRegExpAndKeyboard.h"
#include <vector>
#include "QString"
#include "VariateWidgetProducer.h"
#include "TVariateManager.h"
#include "Context.h"
#include <assert.h>
#include "TToolSys.h"
#include "DialogTeachToolSystem.h"



ScreenToolSystem::ScreenToolSystem(QWidget* parent /*= nullptr*/)
	:InternationalWidget(parent)
{
	Init();
}

ScreenToolSystem::~ScreenToolSystem()
{

}

void ScreenToolSystem::UpdateText()
{
	m_btnAdd->setText(tr("Add"));
	m_btnEdit->setText(tr("Edit"));
	m_btnDelete->setText(tr("Delete"));
	m_btnSave->setText(tr("Save"));

	m_toolBox->setTitle(tr("Tool"));
	m_dataBox->setTitle(tr("Tool settings"));
	m_illustrationBox->setTitle(tr("Illustration"));

	m_lbTool->setText(tr("Tool selection"));
}


void ScreenToolSystem::showEvent(QShowEvent *)
{
	m_comboBoxTool->disconnect();	/*断开所有连接，以便于更新控件信息*/

	/*更新工具坐标系信息，列出当前所有可选的工具坐标系*/
	auto scope = Context::projectContext.CurrentScope();
	VariateWidgetProducer::UpdateComboBoxWithWholeName(TToolSys::TypeName(), TVariateManager::GetInstance()->GetAllVariatesMapScollUp(scope), m_comboBoxTool);

	OnDataChanged();

	connect(m_comboBoxTool, &QComboBox::currentTextChanged, this, &ScreenToolSystem::OnDataChanged);
}

//TVariate* ScreenToolSystem::GetCurrentVariate()
//{
//}

QWidget* ScreenToolSystem::GetDataWidget()
{
	m_dataBox = new QGroupBox(this);

	auto ltX = new LineEditWithRegExpAndKeyboard("0.00", RegExp::STR_REG_FLOAT, this);
	auto ltY = new LineEditWithRegExpAndKeyboard("0.00", RegExp::STR_REG_FLOAT, this);
	auto ltZ = new LineEditWithRegExpAndKeyboard("0.00", RegExp::STR_REG_FLOAT, this);
	auto ltA = new LineEditWithRegExpAndKeyboard("0.00", RegExp::STR_REG_FLOAT, this);
	auto ltB = new LineEditWithRegExpAndKeyboard("0.00", RegExp::STR_REG_FLOAT, this);
	auto ltC = new LineEditWithRegExpAndKeyboard("0.00", RegExp::STR_REG_FLOAT, this);

	m_dataLineEditList.push_back(ltX);
	m_dataLineEditList.push_back(ltY);
	m_dataLineEditList.push_back(ltZ);
	m_dataLineEditList.push_back(ltA);
	m_dataLineEditList.push_back(ltB);
	m_dataLineEditList.push_back(ltC);

	QGridLayout* layout = new QGridLayout(m_dataBox);

	std::vector<std::tuple<QString, QLineEdit*, QString>> datas = { 
		std::make_tuple("X", ltX, QStringLiteral("mm")), std::make_tuple("Y", ltY, QStringLiteral("mm")), std::make_tuple("Z", ltZ, QStringLiteral("mm")),
		std::make_tuple("A", ltA, QStringLiteral("mm")), std::make_tuple("B", ltB, QStringLiteral("mm")), std::make_tuple("C", ltC, QStringLiteral("mm")), };

	for (size_t i = 0; i < datas.size();++i)
	{
		layout->addWidget(new QLabel(std::get<0>(datas.at(i))),i,0);
		layout->addWidget(std::get<1>(datas.at(i)),i,1);
		layout->addWidget(new QLabel(std::get<2>(datas.at(i))), i, 2);
	}

	return m_dataBox;
}

QWidget* ScreenToolSystem::GetIllustrationWidget()
{
	m_illustrationBox = new QGroupBox(this);

	return m_illustrationBox;
}

QWidget* ScreenToolSystem::GetToolWidget()
{
	m_toolBox = new QGroupBox(this);

	QHBoxLayout* layout = new QHBoxLayout(m_toolBox);

	m_lbTool = new QLabel(this);
	m_lbTool->setAlignment(Qt::AlignCenter);
	m_comboBoxTool = new QComboBox(this);

	layout->addWidget(m_lbTool);
	layout->addWidget(m_comboBoxTool);

	return m_toolBox;
}

QWidget* ScreenToolSystem::GetButtonWidget()
{
	QWidget* widget = new QWidget(this);

	QHBoxLayout* layout = new QHBoxLayout(widget);

	m_btnAdd = new Button(this);
	m_btnEdit = new Button(this);
	m_btnDelete = new Button(this);
	m_btnSave = new Button(this);

	layout->addWidget(m_btnAdd);
	layout->addWidget(m_btnEdit);
	layout->addWidget(m_btnDelete);
	layout->addWidget(m_btnSave);

	connect(m_btnAdd, &QPushButton::clicked, [this]{
		QMessageBox::warning(this, tr(""), "not implement", QMessageBox::Cancel);
	});
	connect(m_btnEdit, &QPushButton::clicked, [this]{
		(new DialogTeachToolSystem(GetVariate(),this))->show();
	});
	connect(m_btnDelete, &QPushButton::clicked, [this]{
		QMessageBox::warning(this, tr(""), "not implement", QMessageBox::Cancel);
	});
	connect(m_btnSave, &QPushButton::clicked, [this]{
		QMessageBox::warning(this, tr(""), "not implement", QMessageBox::Cancel);
	});

	return widget;
}

inline
TToolSys* ScreenToolSystem::GetVariate()
{
	return std::static_pointer_cast<TToolSys>(TVariateManager::GetInstance()->GetVariateSrollUp(GetVariateScope(), GetVariateName())).get();	/*获取当前参考坐标系变量*/
}

inline
QString ScreenToolSystem::GetVariateName()
{
	auto wholeName = m_comboBoxTool->currentText();
	auto nameList = wholeName.split(".");

	assert(nameList.size() > 1);
	return nameList.at(nameList.size() - 1);
}

inline
QString ScreenToolSystem::GetVariateScope()
{
	auto wholeName = m_comboBoxTool->currentText();
	return wholeName.left(wholeName.size() - GetVariateName().size() - 1);
}

void ScreenToolSystem::Init()
{
	QGridLayout* layout = new QGridLayout(this);

	layout->addWidget(GetToolWidget(), 0, 0, 1, 2);
	layout->addWidget(GetDataWidget(), 1, 0);
	layout->addWidget(GetIllustrationWidget(), 1, 1);
	layout->addWidget(GetButtonWidget(), 2, 0, 1, 2);

	layout->setColumnStretch(0, 1);
	layout->setColumnStretch(1, 1);
	layout->setRowStretch(1, 1);

	UpdateText();
}

void ScreenToolSystem::OnDataChanged()
{
	auto scope = Context::projectContext.CurrentScope();
	auto variate = TVariateManager::GetInstance()->GetVariateSrollUp(GetVariateScope(),GetVariateName());

	assert(variate != nullptr);

	auto values = std::static_pointer_cast<TToolSys>(variate)->GetValue();
	
	assert(values.size() == static_cast<size_t>(m_dataLineEditList.size()));

	for (size_t i = 0; i < values.size();++i)
	{
		m_dataLineEditList.at(i)->setText(QString::number(values[i]));
	}
}

