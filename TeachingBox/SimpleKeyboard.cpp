#include "stdafx.h"
#include "SimpleKeyboard.h"
#include "KeyBoardButton.h"
#include "IKeyboard.h"



SimpleKeyboard::SimpleKeyboard(QWidget* parent/*=nullptr*/)
	:QWidget(parent)
	, m_targetObject(parent)
{
	Init();
}

void SimpleKeyboard::Init()
{
	InitLayout();
	InitSignalSlot();
	ChangeToLower();
}

void SimpleKeyboard::InitLayout()
{
	/*总布局*/
	QVBoxLayout* layoutWhole = new QVBoxLayout(this);
	QHBoxLayout* layoutLine1 = new QHBoxLayout;
	QHBoxLayout* layoutLine2 = new QHBoxLayout;
	QHBoxLayout* layoutLine3 = new QHBoxLayout;
	QHBoxLayout* layoutLine4 = new QHBoxLayout;
	QHBoxLayout* layoutLine5 = new QHBoxLayout;
	QHBoxLayout* layoutLine6 = new QHBoxLayout;

	layoutWhole->setMargin(0);
	layoutWhole->setSpacing(0);
	layoutLine1->setSpacing(0);
	layoutLine2->setSpacing(0);
	layoutLine3->setSpacing(0);
	layoutLine4->setSpacing(0);
	layoutLine5->setSpacing(0);
	layoutLine6->setSpacing(0);

	layoutWhole->addLayout(layoutLine1);
	layoutWhole->addLayout(layoutLine2);
	layoutWhole->addLayout(layoutLine3);
	layoutWhole->addLayout(layoutLine4);
	layoutWhole->addLayout(layoutLine5);
	layoutWhole->addLayout(layoutLine6);

	//////////////////////////////////////////////////////////////////////////
	/*初始化控件*/
	//////////////////////////////////////////////////////////////////////////
	/*初始化数字按键*/
	auto btnNum0 = new KeyboardButton(this);
	auto btnNum1 = new KeyboardButton(this);
	auto btnNum2 = new KeyboardButton(this);
	auto btnNum3 = new KeyboardButton(this);
	auto btnNum4 = new KeyboardButton(this);
	auto btnNum5 = new KeyboardButton(this);
	auto btnNum6 = new KeyboardButton(this);
	auto btnNum7 = new KeyboardButton(this);
	auto btnNum8 = new KeyboardButton(this);
	auto btnNum9 = new KeyboardButton(this);

	m_keyMap[btnNum0] = { Qt::Key_0, "0", ")" };
	m_keyMap[btnNum1] = { Qt::Key_1, "1", "!" };
	m_keyMap[btnNum2] = { Qt::Key_2, "2", "@" };
	m_keyMap[btnNum3] = { Qt::Key_3, "3", "#" };
	m_keyMap[btnNum4] = { Qt::Key_4, "4", "$" };
	m_keyMap[btnNum5] = { Qt::Key_5, "5", "%" };
	m_keyMap[btnNum6] = { Qt::Key_6, "6", "^" };
	m_keyMap[btnNum7] = { Qt::Key_7, "7", "&" };
	m_keyMap[btnNum8] = { Qt::Key_8, "8", "*" };
	m_keyMap[btnNum9] = { Qt::Key_9, "9", "(" };


	/*初始化字母按键*/
	auto btnA = new KeyboardButton(this);
	auto btnB = new KeyboardButton(this);
	auto btnC = new KeyboardButton(this);
	auto btnD = new KeyboardButton(this);
	auto btnE = new KeyboardButton(this);
	auto btnF = new KeyboardButton(this);
	auto btnG = new KeyboardButton(this);
	auto btnH = new KeyboardButton(this);
	auto btnI = new KeyboardButton(this);
	auto btnJ = new KeyboardButton(this);
	auto btnK = new KeyboardButton(this);
	auto btnL = new KeyboardButton(this);
	auto btnM = new KeyboardButton(this);
	auto btnN = new KeyboardButton(this);
	auto btnO = new KeyboardButton(this);
	auto btnP = new KeyboardButton(this);
	auto btnQ = new KeyboardButton(this);
	auto btnR = new KeyboardButton(this);
	auto btnS = new KeyboardButton(this);
	auto btnT = new KeyboardButton(this);
	auto btnU = new KeyboardButton(this);
	auto btnV = new KeyboardButton(this);
	auto btnW = new KeyboardButton(this);
	auto btnX = new KeyboardButton(this);
	auto btnY = new KeyboardButton(this);
	auto btnZ = new KeyboardButton(this);

	m_keyMap[btnA] = { Qt::Key_A, "a", "A" };
	m_keyMap[btnB] = { Qt::Key_B, "b", "B" };
	m_keyMap[btnC] = { Qt::Key_C, "c", "C" };
	m_keyMap[btnD] = { Qt::Key_D, "d", "D" };
	m_keyMap[btnE] = { Qt::Key_E, "e", "E" };
	m_keyMap[btnF] = { Qt::Key_F, "f", "F" };
	m_keyMap[btnG] = { Qt::Key_G, "g", "G" };
	m_keyMap[btnH] = { Qt::Key_H, "h", "H" };
	m_keyMap[btnI] = { Qt::Key_I, "i", "I" };
	m_keyMap[btnJ] = { Qt::Key_J, "j", "J" };
	m_keyMap[btnK] = { Qt::Key_K, "k", "K" };
	m_keyMap[btnL] = { Qt::Key_L, "l", "L" };
	m_keyMap[btnM] = { Qt::Key_M, "m", "M" };
	m_keyMap[btnN] = { Qt::Key_N, "n", "N" };
	m_keyMap[btnO] = { Qt::Key_O, "o", "O" };
	m_keyMap[btnP] = { Qt::Key_P, "p", "P" };
	m_keyMap[btnQ] = { Qt::Key_Q, "q", "Q" };
	m_keyMap[btnR] = { Qt::Key_R, "r", "R" };
	m_keyMap[btnS] = { Qt::Key_S, "s", "S" };
	m_keyMap[btnT] = { Qt::Key_T, "t", "T" };
	m_keyMap[btnU] = { Qt::Key_U, "u", "U" };
	m_keyMap[btnV] = { Qt::Key_V, "v", "V" };
	m_keyMap[btnW] = { Qt::Key_W, "w", "W" };
	m_keyMap[btnX] = { Qt::Key_X, "x", "X" };
	m_keyMap[btnY] = { Qt::Key_Y, "y", "Y" };
	m_keyMap[btnZ] = { Qt::Key_Z, "z", "Z" };

	/*初始化符号按键*/
	auto btnLeftBracket = new KeyboardButton(this);
	auto btnRightBracket = new KeyboardButton(this);
	auto btnQuotation = new KeyboardButton(this);
	auto btnQuoteLeft = new KeyboardButton(this);
	auto btnSemicolon = new KeyboardButton(this);
	auto btnMinus = new KeyboardButton(this);
	auto btnPlus = new KeyboardButton(this);
	auto btnComma = new KeyboardButton(this);
	auto btnPeriod = new KeyboardButton(this);
	auto btnSlash = new KeyboardButton(this);
	auto btnBackslash = new KeyboardButton(this);

	m_keyMap[btnLeftBracket] = { Qt::Key_BracketLeft, "[", "{" };
	m_keyMap[btnRightBracket] = { Qt::Key_BraceRight, "]", "}" };
	m_keyMap[btnQuotation] = { Qt::Key_Question, "\'", "\"" };
	m_keyMap[btnQuoteLeft] = { Qt::Key_QuoteLeft, "`", "~" };
	m_keyMap[btnSemicolon] = { Qt::Key_Semicolon, ";", ":" };
	m_keyMap[btnMinus] = { Qt::Key_Minus, "-", "_" };
	m_keyMap[btnPlus] = { Qt::Key_Plus, "=", "+" };
	m_keyMap[btnComma] = { Qt::Key_Comma, ",", "<" };
	m_keyMap[btnPeriod] = { Qt::Key_Period, ".", ">" };	
	m_keyMap[btnSlash] = { Qt::Key_Slash, "/", "?" };
	m_keyMap[btnBackslash] = { Qt::Key_Backslash, "\\", "|" };

	/*初始化功能按键*/
	auto btnTab = new KeyboardButton(this);
	auto btnCapsLock = new KeyboardButton(QString("Caps Lock"));
	auto btnEnter = new KeyboardButton(this);
	auto btnShift = new KeyboardButton("Shift");
	auto btnBackspace = new KeyboardButton(QString("<-"));
	auto btnSpace = new KeyboardButton(this);
	auto btnUp = new KeyboardButton(this);
	auto btnLeft = new KeyboardButton(this);
	auto btnDown = new KeyboardButton(this);
	auto btnRight = new KeyboardButton(this);

	m_keyMap[btnUp] = { Qt::Key_Up, "Up", "Up" };
	m_keyMap[btnLeft] = { Qt::Key_Left, "Lf", "Lf" };
	m_keyMap[btnDown] = { Qt::Key_Down, "Dw", "Dw" };
	m_keyMap[btnRight] = { Qt::Key_Right, "Rt", "Rt" };
	m_keyMap[btnEnter] = { Qt::Key_Enter, "Enter", "Enter" };
	m_keyMap[btnBackspace] = { Qt::Key_Backspace, "<-", "<-" };
	m_keyMap[btnSpace] = { Qt::Key_Space, " ", " " };
	m_keyMap[btnTab] = { Qt::Key_Tab, "Tab", "Tab" };

	connect(btnShift, &QToolButton::pressed, [this, btnShift]{
		m_isShiftPressed = true;
		UpdateKeyboard(m_isShiftPressed == m_isCapPressed);
	});
	connect(btnShift, &QToolButton::released, [this, btnShift]{
		m_isShiftPressed = false;
		UpdateKeyboard(m_isShiftPressed == m_isCapPressed);
	});
	connect(btnCapsLock, &QToolButton::clicked, [this, btnCapsLock]{
		m_isCapPressed = !m_isCapPressed;
		UpdateKeyboard(m_isShiftPressed == m_isCapPressed);
	});

	//////////////////////////////////////////////////////////////////////////
	/*布局*/
	//////////////////////////////////////////////////////////////////////////
	/*第一行布局*/
	layoutLine1->addWidget(btnQuoteLeft);
	layoutLine1->addWidget(btnNum1);
	layoutLine1->addWidget(btnNum2);
	layoutLine1->addWidget(btnNum3);
	layoutLine1->addWidget(btnNum4);
	layoutLine1->addWidget(btnNum5);
	layoutLine1->addWidget(btnNum6);
	layoutLine1->addWidget(btnNum7);
	layoutLine1->addWidget(btnNum8);
	layoutLine1->addWidget(btnNum9);
	layoutLine1->addWidget(btnNum0);
	layoutLine1->addWidget(btnMinus);
	layoutLine1->addWidget(btnPlus);
	layoutLine1->addWidget(btnBackspace);

	/*第二行布局*/
	layoutLine2->addWidget(btnTab);
	layoutLine2->addWidget(btnQ);
	layoutLine2->addWidget(btnW);
	layoutLine2->addWidget(btnE);
	layoutLine2->addWidget(btnR);
	layoutLine2->addWidget(btnT);
	layoutLine2->addWidget(btnY);
	layoutLine2->addWidget(btnU);
	layoutLine2->addWidget(btnI);
	layoutLine2->addWidget(btnO);
	layoutLine2->addWidget(btnP);
	layoutLine2->addWidget(btnLeftBracket);
	layoutLine2->addWidget(btnRightBracket);
	layoutLine2->addWidget(btnQuotation);

	/*第三行布局*/
	layoutLine3->addWidget(btnCapsLock);
	layoutLine3->addWidget(btnA);
	layoutLine3->addWidget(btnS);
	layoutLine3->addWidget(btnD);
	layoutLine3->addWidget(btnF);
	layoutLine3->addWidget(btnG);
	layoutLine3->addWidget(btnH);
	layoutLine3->addWidget(btnJ);
	layoutLine3->addWidget(btnK);
	layoutLine3->addWidget(btnL);
	layoutLine3->addWidget(btnSemicolon);
	layoutLine3->addWidget(btnEnter);

	layoutLine3->setStretch(0, 3);
	for (int i = 1; i < layoutLine3->count() - 1;++i)
	{
		layoutLine3->setStretch(i, 2);
	}
	layoutLine3->setStretch(layoutLine3->count() - 1, 3);

	/*第四行*/
	layoutLine4->addWidget(btnShift);
	layoutLine4->addWidget(btnZ);
	layoutLine4->addWidget(btnX);
	layoutLine4->addWidget(btnC);
	layoutLine4->addWidget(btnV);
	layoutLine4->addWidget(btnB);
	layoutLine4->addWidget(btnN);
	layoutLine4->addWidget(btnM);
	layoutLine4->addWidget(btnComma);
	layoutLine4->addWidget(btnPeriod);
	layoutLine4->addStretch();
	layoutLine4->addWidget(btnUp);
	layoutLine4->addStretch();

	layoutLine4->setStretch(0, 2);
	for (int i = 1; i < layoutLine4->count();++i)
	{
		layoutLine4->setStretch(i,1);
	}

	/*第五行布局*/
	layoutLine5->addWidget(btnSlash);
	layoutLine5->addWidget(btnBackslash);
	layoutLine5->addWidget(btnSpace);
	layoutLine5->addWidget(btnLeft);
	layoutLine5->addWidget(btnDown);
	layoutLine5->addWidget(btnRight);

	layoutLine5->setStretch(0, 1);
	layoutLine5->setStretch(1, 1);
	layoutLine5->setStretch(2, 9);
	layoutLine5->setStretch(3, 1);
	layoutLine5->setStretch(4, 1);
	layoutLine5->setStretch(5, 1);

	for (auto iter : m_keyMap)
	{
		iter.first->setText(iter.second.lowerText);
	}
}

void SimpleKeyboard::InitSignalSlot()
{
	for (auto iter : m_keyMap)
	{
		connect(iter.first, &KeyboardButton::clicked, [this, iter]{
			auto text = iter.second.lowerText;
			if (m_isCapPressed != m_isShiftPressed)
			{
				text = iter.second.upperText;
			}
			if (m_isShiftPressed)
			{
				QApplication::postEvent(m_targetObject, new QKeyEvent(QKeyEvent::KeyPress, iter.second.keyType,
					Qt::NoModifier | Qt::ShiftModifier, text));
			}
			else
			{
				QApplication::postEvent(m_targetObject, new QKeyEvent(QKeyEvent::KeyPress, iter.second.keyType,
					Qt::NoModifier, text));
			}
		});
	}
}

void SimpleKeyboard::ChangeToLower()
{
	for (auto iter : m_keyMap)
	{
		iter.first->setText(iter.second.lowerText);
	}
}

void SimpleKeyboard::ChangeToUpper()
{
	for (auto iter : m_keyMap)
	{
		iter.first->setText(iter.second.upperText);
		if (iter.second.upperText=="&")
		{
			iter.first->setText("&&");
		}
	}
}

void SimpleKeyboard::UpdateKeyboard(bool isLower)
{
	if (isLower)
	{
		ChangeToLower();
	}
	else{
		ChangeToUpper();
	}
}
