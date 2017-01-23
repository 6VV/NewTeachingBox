#include "stdafx.h"
#include "Keyboard.h"
#include "QBoxLayout"
#include "QList"
#include "TeachingBoxContext.h"
#include "KeyBoardButton.h"
#include "KeyboardInterface.h"
#include "KeyboardLineEdit.h"
#include "SimpleKeyboard.h"



Keyboard::Keyboard(QWidget* parent/*=0*/) :QWidget(parent)
{
	Init();
}

Keyboard::~Keyboard()
{
}

Keyboard* Keyboard::GetInstance()
{
	return SingleTon<Keyboard>::GetInstance();
}


void Keyboard::SetEchoMode(QLineEdit::EchoMode echoMode)
{
	m_lineEditText->setEchoMode(echoMode);
}

void Keyboard::SetCurrentText(const QString& currentText)
{
	m_lineEditText->setText(currentText);
	m_lineEditText->selectAll();
}

void Keyboard::SetKeyboardInterface(KeyboardInterface* keyboardInterface)
{
	m_keyboardInterface = keyboardInterface;
}


void Keyboard::Init()
{
	m_lineEditText = new KeyboardLineEidt(this);
	m_simpleKeyboard = new SimpleKeyboard( m_lineEditText);
	InitLayout();
}

void Keyboard::InitLayout()
{
	this->setWindowFlags(Qt::Popup);
	
	/*设置位置及大小*/
	QRect rect = TeachingBoxContext::GetInstance()->GetScreenRect();
	this->setGeometry(rect.left(), (rect.top()+rect.bottom())/2, rect.width(), rect.height()/2);

	/*总布局*/
	auto mainLayout = new QVBoxLayout(this);
	QHBoxLayout* layoutText = new QHBoxLayout;
	QHBoxLayout* layoutKeyboard = new QHBoxLayout;
	QHBoxLayout* layoutButton = new QHBoxLayout;

	mainLayout->setMargin(0);
	mainLayout->setSpacing(0);
	layoutText->setSpacing(0);
	layoutKeyboard->setSpacing(0);
	layoutButton->setSpacing(0);

	mainLayout->addLayout(layoutText);
	mainLayout->addLayout(layoutKeyboard);
	mainLayout->addLayout(layoutButton);

	mainLayout->setStretch(0, 1);
	mainLayout->setStretch(1, 5);
	mainLayout->setStretch(2, 1);

	layoutText->addWidget(m_lineEditText);	
	layoutKeyboard->addWidget(m_simpleKeyboard);

	/*初始化确认、取消按键*/
	m_btnCancle = new KeyboardButton(QCoreApplication::translate(CLASS_NAME, "Cancle"));
	m_btnConfirm = new KeyboardButton(QCoreApplication::translate(CLASS_NAME, "Confirm"));

	layoutButton->addWidget(m_btnCancle);
	layoutButton->addWidget(m_btnConfirm);

	connect(m_btnConfirm, &QPushButton::clicked, [this]{
		this->hide();

		/*若函数不为空*/
		if (m_keyboardInterface != NULL)
		{
			m_keyboardInterface->KeyboardEdit(m_lineEditText->text());
		}
		Clear();
		return;
	});
	connect(m_btnCancle, &QPushButton::clicked, [this]{
		m_lineEditText->clear();
		this->hide();
	});
}


void Keyboard::Clear()
{
	m_keyboardInterface = nullptr;
	m_lineEditText->clear();
	m_lineEditText->setEchoMode(QLineEdit::Normal);
}

