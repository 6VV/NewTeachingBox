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
#include "ToolSysDialog.h"
#include "DataStruct.h"



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
	UpdateWidgetState();
}

//TVariate* ScreenToolSystem::GetCurrentVariate()
//{
//}

QWidget* ScreenToolSystem::CreateDataWidget()
{
	m_dataBox = new QGroupBox(this);

	m_ltX = new LineEditWithRegExpAndKeyboard("0.00", RegExp::STR_REG_FLOAT, this);
	m_ltY = new LineEditWithRegExpAndKeyboard("0.00", RegExp::STR_REG_FLOAT, this);
	m_ltZ = new LineEditWithRegExpAndKeyboard("0.00", RegExp::STR_REG_FLOAT, this);
	m_ltA = new LineEditWithRegExpAndKeyboard("0.00", RegExp::STR_REG_FLOAT, this);
	m_ltB = new LineEditWithRegExpAndKeyboard("0.00", RegExp::STR_REG_FLOAT, this);
	m_ltC = new LineEditWithRegExpAndKeyboard("0.00", RegExp::STR_REG_FLOAT, this);

	m_dataLineEditList.push_back(m_ltX);
	m_dataLineEditList.push_back(m_ltY);
	m_dataLineEditList.push_back(m_ltZ);
	m_dataLineEditList.push_back(m_ltA);
	m_dataLineEditList.push_back(m_ltB);
	m_dataLineEditList.push_back(m_ltC);

	QGridLayout* layout = new QGridLayout(m_dataBox);

	std::vector<std::tuple<QString, QLineEdit*, QString>> datas = { 
		std::make_tuple("X", m_ltX, QStringLiteral("mm")), std::make_tuple("Y", m_ltY, QStringLiteral("mm")), std::make_tuple("Z", m_ltZ, QStringLiteral("mm")),
		std::make_tuple("A", m_ltA, QStringLiteral("mm")), std::make_tuple("B", m_ltB, QStringLiteral("mm")), std::make_tuple("C", m_ltC, QStringLiteral("mm")), };

	for (size_t i = 0; i < datas.size();++i)
	{
		layout->addWidget(new QLabel(std::get<0>(datas.at(i))),i,0);
		layout->addWidget(std::get<1>(datas.at(i)),i,1);
		layout->addWidget(new QLabel(std::get<2>(datas.at(i))), i, 2);
	}

	return m_dataBox;
}

QWidget* ScreenToolSystem::CreateIllustrationWidget()
{
	m_illustrationBox = new QGroupBox(this);

	return m_illustrationBox;
}

QWidget* ScreenToolSystem::CreateToolWidget()
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

QWidget* ScreenToolSystem::CreateButtonWidget()
{
	QWidget* widget = new QWidget(this);

	QHBoxLayout* layout = new QHBoxLayout(widget);

	m_btnEdit = new Button(this);
	m_btnDelete = new Button(this);
	m_btnSave = new Button(this);

	layout->addWidget(m_btnEdit);
	layout->addWidget(m_btnDelete);
	layout->addWidget(m_btnSave);

	connect(m_btnEdit, &QPushButton::clicked, [this]{
		auto variate = GetVariate();
		if (variate==nullptr)
		{
			return;
		}
		(new ToolSysDialog(variate, this))->show();
	});
	connect(m_btnDelete, &QPushButton::clicked, [this]{
		auto variate = GetVariate();
		if (variate==nullptr)
		{
			return;
		}
		switch (QMessageBox::information(this, tr("Delete variate"), tr("Delete variate: ") + variate->GetName(), QMessageBox::Ok | QMessageBox::Cancel))
		{
		case QMessageBox::Ok:{
			TVariateManager::GetInstance()->DeleteVariate(variate->GetScope(), variate->GetName());
			UpdateWidgetState();
		}break;
		default:
			break;
		}
	});
	connect(m_btnSave, &QPushButton::clicked, [this]{
		auto variate = GetVariate();
		if (variate==nullptr)
		{
			return;
		}

		TToolSys::ValueType value{};

		for (size_t i = 0; i < value.size(); ++i)
		{
			value[i] = m_dataLineEditList[i]->text().toDouble();
		}

		TVariateManager::GetInstance()->UpdateVariate(std::shared_ptr<TVariate>(new TToolSys{ { variate->GetScope(), variate->GetName() }, value }));
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

	layout->addWidget(CreateToolWidget(), 0, 0, 1, 2);
	layout->addWidget(CreateDataWidget(), 1, 0);
	layout->addWidget(CreateIllustrationWidget(), 1, 1);
	layout->addWidget(CreateButtonWidget(), 2, 0, 1, 2);

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

void ScreenToolSystem::UpdateWidgetState()
{
	m_comboBoxTool->disconnect();	/*断开所有连接，以便于更新控件信息*/

	/*更新工具坐标系信息，列出当前所有可选的工具坐标系*/
	auto scope = Context::projectContext.CurrentScope();
	VariateWidgetProducer::UpdateComboBoxWithWholeName(TToolSys::TypeName(), TVariateManager::GetInstance()->GetAllVariatesMapScollUp(scope), m_comboBoxTool);

	OnDataChanged();

	connect(m_comboBoxTool, &QComboBox::currentTextChanged, this, &ScreenToolSystem::OnDataChanged);
}

void ScreenToolSystem::OnReceive(const tPoseEuler& poseEuler)
{
	m_ltX->setText(QString::number(poseEuler.m_PositionCartesian.m_X));
	m_ltY->setText(QString::number(poseEuler.m_PositionCartesian.m_Y));
	m_ltZ->setText(QString::number(poseEuler.m_PositionCartesian.m_Z));
	m_ltA->setText(QString::number(poseEuler.m_PostureEuler.m_A));
	m_ltB->setText(QString::number(poseEuler.m_PostureEuler.m_B));
	m_ltC->setText(QString::number(poseEuler.m_PostureEuler.m_C));

	TToolSys::ValueType value{};
	value[0] = poseEuler.m_PositionCartesian.m_X;
	value[1] = poseEuler.m_PositionCartesian.m_Y;
	value[2] = poseEuler.m_PositionCartesian.m_Z;
	value[3] = poseEuler.m_PostureEuler.m_A;
	value[4] = poseEuler.m_PostureEuler.m_B;
	value[5] = poseEuler.m_PostureEuler.m_C;

	GetVariate()->SetValue(value);
}

