#include "stdafx.h"
#include "ScreenWarningHeader.h"
#include "QBoxLayout"
#include "ConfirmButton.h"
#include "TeachingBoxBroadcast.h"
#include "WarningInfo.h"

#include "WidgetWithBorderAndIcon.h"
#include "WarningModel.h"


ScreenWarningHeader::ScreenWarningHeader(QWidget* parent/*=0*/)
	:InternationalWidget(parent)
	, m_btnConfrim(new ConfirmButton(this))
{
	Init();
}

ScreenWarningHeader::~ScreenWarningHeader()
{

}

void ScreenWarningHeader::UpdateText()
{
	m_btnConfrim->setText(tr("Confirm"));
}

void ScreenWarningHeader::ChangeWarningInfo(const WarningInfo& warningInfo)
{
	auto category = warningInfo.GetCategory();
	QString iconPath{};
	QColor backgroundColor{ 100, 100, 100, 100 };
	switch (category)
	{
	case WarningInfo::CATEFORY_INFO:{iconPath = WarningModel::CATEFORY_INFO_ICON_PATH; }break;
	case WarningInfo::CATEFORY_WARNING:{
		iconPath = WarningModel::CATEFORY_WARNING_ICON_PATH;
		backgroundColor = QColor::fromRgb(0xFF, 0xD7, 0x00, 100);
	} break;
	case WarningInfo::CATEFORY_ERROR:{
		iconPath = WarningModel::CATEFORY_ERROR_ICON_PATH;
		backgroundColor = QColor::fromRgb(0xFF, 0x30, 0x30, 100);
	} break;
	default:
		break;
	}

	ChangeDisplay(iconPath, warningInfo.GetDescribe(), backgroundColor);
}

void ScreenWarningHeader::ChangeDisplay(const QString& iconPath, const QString& text, const QColor& backgroundColor)
{
	m_warningWidget->SetIcon(iconPath, m_warningWidget->height() / 2);
	m_lbWarningText->setText(text);

	m_warningWidget->setAutoFillBackground(true);
	QPalette palette;
	palette.setColor(QPalette::Background, backgroundColor);
	m_warningWidget->setPalette(palette);
}

void ScreenWarningHeader::Init()
{
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->setMargin(0);
	layout->setSpacing(0);

	m_lbWarningText = new QLabel(this);
	m_lbWarningText->setAlignment(Qt::AlignCenter);
	m_warningWidget = new WidgetWithBorderAndIcon(m_lbWarningText, "", this);

	layout->addWidget(m_warningWidget, 8);
	layout->addWidget(m_btnConfrim, 1);

	connect(TeachingBoxBroadcast::GetInstance(), &TeachingBoxBroadcast::WarningThrowed, this, &ScreenWarningHeader::ChangeWarningInfo); 
	connect(TeachingBoxBroadcast::GetInstance(), &TeachingBoxBroadcast::WarningStateChanged, this,&ScreenWarningHeader::ChangeCurrentInfo);
	connect(m_btnConfrim, &Button::clicked, [this]{
		int index = WarningModel::GetInstance()->NextToBeSolved();
		if (index==-1)
		{
			return;
		}
		WarningModel::GetInstance()->SolveRow(index);
		ChangeCurrentInfo();
	});

	UpdateText();
}

void ScreenWarningHeader::ChangeCurrentInfo()
{
	auto index = WarningModel::GetInstance()->NextToBeSolved();
	if (index == -1)
	{
		ChangeDisplay(WarningModel::STATE_SOLVED_ICON_PATH, "", QColor::fromRgb(0xB4, 0xEE, 0xB4, 100));
		return;
	}
	ChangeWarningInfo(WarningModel::GetInstance()->GetWarningInfo(index));
}
