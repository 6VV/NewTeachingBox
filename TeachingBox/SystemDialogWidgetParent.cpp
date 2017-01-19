#include "stdafx.h"
#include "SystemDialogWidgetParent.h"
#include "QBoxLayout"
#include "Button.h"
#include "RemoteFeedbackController.h"
#include "RemoteManager.h"
#include "CoordinateSystemTeachInfo.h"



SystemDialogWidgetParent::SystemDialogWidgetParent(QStackedWidget* parent)
	:QWidget(parent)
	, m_parentWidget(parent)
{
	Init();
}

SystemDialogWidgetParent::~SystemDialogWidgetParent()
{
}

bool SystemDialogWidgetParent::HavePre()
{
	return m_preWidget != nullptr;
}

bool SystemDialogWidgetParent::HaveNext()
{
	return m_nextWidget != nullptr && IsTeached();
}


void SystemDialogWidgetParent::showEvent(QShowEvent *)
{
	if (m_isFirstShow)
	{
		m_isFirstShow = false;

		m_layoutMain->addWidget(MainWidget());
		m_layoutMain->addWidget(IllustrationWidget());

		m_layoutMain->setStretch(0, 1);
		m_layoutMain->setStretch(1, 1);
	}

	RemoteFeedbackController::GetInstance()->AddListener(this);

	UpdateButtonState();
}


void SystemDialogWidgetParent::UpdateButtonState()
{
	m_btnPre->setEnabled(HavePre());
	m_btnNext->setEnabled(HaveNext());
}

void SystemDialogWidgetParent::hideEvent(QHideEvent *event)
{
	QWidget::hideEvent(event);

	RemoteFeedbackController::GetInstance()->DeleteListener(this);
}

void SystemDialogWidgetParent::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);
	m_lbPixmap->setPixmap(QPixmap(IllustrationPixmapPath()).scaled(m_lbPixmap->size()));
}

void SystemDialogWidgetParent::OnNextButtonClicked()
{
	if (m_nextWidget != nullptr)
	{
		++m_coorInfo->index;
		m_nextWidget->SetCoorInfo(m_coorInfo);

		m_parentWidget->setCurrentWidget(m_nextWidget);
		m_nextWidget->m_preWidget = this;
	}
}

void SystemDialogWidgetParent::GetRemotePose()
{
	RemoteManager::GetInstance()->SendCommandToGetPose();
}

bool SystemDialogWidgetParent::IsTeached()
{
	return	static_cast<int>(m_coorInfo->values.size()) > m_coorInfo->index;
}

QWidget* SystemDialogWidgetParent::PointWidgetXYZ()
{
	QWidget* widget = new QWidget(this);
	QGridLayout* layout = new QGridLayout(widget);

	m_ltX = new QLineEdit("0.00", this);
	m_ltY = new QLineEdit("0.00", this);
	m_ltZ = new QLineEdit("0.00", this);

	m_ltX->setEnabled(false);
	m_ltY->setEnabled(false);
	m_ltZ->setEnabled(false);

	layout->addWidget(new QLabel("X"), 0, 0);
	layout->addWidget(m_ltX, 0, 1);
	layout->addWidget(new QLabel("mm"), 0, 2);

	layout->addWidget(new QLabel("Y"), 1, 0);
	layout->addWidget(m_ltY, 1, 1);
	layout->addWidget(new QLabel("mm"), 1, 2);

	layout->addWidget(new QLabel("Z"), 2, 0);
	layout->addWidget(m_ltZ, 2, 1);
	layout->addWidget(new QLabel("mm"), 2, 2);

	return widget;
}

QWidget* SystemDialogWidgetParent::PointWidgetABC()
{
	QWidget* widget = new QWidget(this);
	QGridLayout* layout = new QGridLayout(widget);

	m_ltA = new QLineEdit("0.00");
	m_ltB = new QLineEdit("0.00");
	m_ltC = new QLineEdit("0.00");

	m_ltA->setEnabled(false);
	m_ltB->setEnabled(false);
	m_ltC->setEnabled(false);

	QVector<QLineEdit*> ltLists{ m_ltA, m_ltB, m_ltC };
	QVector<QString> lbNames{ "A", "B", "C" };
	QVector<QString> lbUnits{ QStringLiteral("°"), QStringLiteral("°"), QStringLiteral("°") };

	for (int i = 0; i < ltLists.size(); ++i)
	{
		layout->addWidget(new QLabel(lbNames[i]), i, 0);
		layout->addWidget(ltLists[i], i, 1);
		layout->addWidget(new QLabel(lbUnits[i]), i, 2);
	}

	return widget;
}

QWidget* SystemDialogWidgetParent::PointWidgetXYZABC()
{
	QWidget* widget = new QWidget(this);
	QGridLayout* layout = new QGridLayout(widget);

	m_ltX = new QLineEdit("0.00");
	m_ltY = new QLineEdit("0.00");
	m_ltZ = new QLineEdit("0.00");
	m_ltA = new QLineEdit("0.00");
	m_ltB = new QLineEdit("0.00");
	m_ltC = new QLineEdit("0.00");

	m_ltX->setEnabled(false);
	m_ltY->setEnabled(false);
	m_ltZ->setEnabled(false);
	m_ltA->setEnabled(false);
	m_ltB->setEnabled(false);
	m_ltC->setEnabled(false);

	QVector<QLineEdit*> ltLists{ m_ltX, m_ltY, m_ltZ, m_ltA, m_ltB, m_ltC };
	QVector<QString> lbNames{ "X", "Y", "Z", "A", "B", "C" };
	QVector<QString> lbUnits{ "mm", "mm", "mm", QStringLiteral("°"), QStringLiteral("°"), QStringLiteral("°") };

	for (int i = 0; i < ltLists.size(); ++i)
	{
		layout->addWidget(new QLabel(lbNames[i]), i, 0);
		layout->addWidget(ltLists[i], i, 1);
		layout->addWidget(new QLabel(lbUnits[i]), i, 2);
	}

	return widget;
}

void SystemDialogWidgetParent::Init()
{
	QVBoxLayout* layout = new QVBoxLayout(this);
	m_layoutMain = new QHBoxLayout(this);
	layout->addLayout(m_layoutMain);
	layout->addLayout(ButtonLayout());

	layout->setStretch(0, 1);
}

void SystemDialogWidgetParent::SetNextWidget(SystemDialogWidgetParent* widget)
{
	this->m_nextWidget = widget;

	widget->m_preWidget = this;
}

void SystemDialogWidgetParent::SetCoorInfo(std::shared_ptr<CoordinateSystemTeachInfo> coorInfo)
{
	m_coorInfo = coorInfo;
}

void SystemDialogWidgetParent::SetPreWidget(SystemDialogWidgetParent* widget)
{
	m_preWidget = widget;
}

QLayout* SystemDialogWidgetParent::ButtonLayout()
{
	QHBoxLayout* layout = new QHBoxLayout(this);
	m_btnPre = new Button(tr("Pre"),this);
	m_btnNext = new Button(tr("Next"),this);
	m_btnCancel = new Button(tr("Cancel"),this);

	layout->addWidget(m_btnPre);
	layout->addWidget(m_btnNext);
	layout->addWidget(m_btnCancel);

	connect(m_btnPre, &Button::clicked, [this]{
		if (m_preWidget != nullptr)
		{
			--m_coorInfo->index;
			m_parentWidget->setCurrentWidget(m_preWidget);
		}
	});

	connect(m_btnNext, &Button::clicked, [this]{
		OnNextButtonClicked();
	});

	connect(m_btnCancel, &Button::clicked, [this]{
		emit(SignalOnCancelClicked());
	});

	return layout;
}

void SystemDialogWidgetParent::OnReseivePose(const tPoseEuler& pose/*= */)
{
	if (m_ltX!=nullptr && m_ltY!=nullptr && m_ltZ!=nullptr)
	{
		m_ltX->setText(QString::number(pose.m_PositionCartesian.m_X));
		m_ltY->setText(QString::number(pose.m_PositionCartesian.m_Y));
		m_ltZ->setText(QString::number(pose.m_PositionCartesian.m_Z));
	}
	if (m_ltA != nullptr && m_ltB != nullptr && m_ltC != nullptr)
	{
		m_ltA->setText(QString::number(pose.m_PostureEuler.m_A));
		m_ltB->setText(QString::number(pose.m_PostureEuler.m_B));
		m_ltC->setText(QString::number(pose.m_PostureEuler.m_C));
	}
}

QWidget* SystemDialogWidgetParent::IllustrationWidget()
{
	QGroupBox* box = new QGroupBox(tr("Illustration"), this);
	QVBoxLayout* layout = new QVBoxLayout(box);
	m_lbPixmap = new QLabel(this);
	m_lbPixmap->setScaledContents(true);
	layout->addWidget(m_lbPixmap);

	return box;
}