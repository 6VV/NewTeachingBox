#include "stdafx.h"
#include "Keyboard.h"
#include "QBoxLayout"
#include "QList"
#include "TeachingBoxContext.h"
#include "KeyBoardButton.h"
#include "KeyboardInterface.h"

const int Keyboard::CONFIRM_SCREEN_SETTING_LOGIN = 1;
const int Keyboard::CONFIRM_SCREEN_PROGRAM_EDIT_PROGRAM = 2;
const int Keyboard::CONFIRM_SCREEN_PROJECT_NEW_PROJECT = 3;
const int Keyboard::CONFIRM_SCREEN_PROJECT_NEW_PROGRAM = 4;
const int Keyboard::CONFIRM_MACRO_POSITION_EIDT = 5;
const int Keyboard::CONFIRM_MACRO_VELOCITY_EDIT = 6;
const int Keyboard::CONFIRM_MACRO_ZONE_EDIT = 7;
const int Keyboard::CONFIRM_MACRO_DOUBLE_EDIT = 8;
const int Keyboard::CONFIRM_MACRO_LABEL_EDIT = 9;
const int Keyboard::CONFIRM_NEW_PARAMETER = 10;
const int Keyboard::CONFIRM_MACRO_INT_EDIT = 11;
const int Keyboard::CONFIRM_MACRO_BOOL_EDIT = 12;
const int Keyboard::CONFIRM_MACRO_STRING_EDIT = 13;
const int Keyboard::CONFIRM_MACRO_NUMBER_EDIT = 14;


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



QLineEdit* Keyboard::GetLineEdit()
{
	return m_lineEditText;
}

QString Keyboard::GetCurrentText()
{
	return m_lineEditText->text();
}

/*************************************************
//  Function: 		SetConfirmCommand
//  Description: 	设置确认按钮按下后应进行的操作
//  Calls:		 	
//  Called By: 		各需要调用本键盘操作的函数
//  Parameter:      int
//  Return: 		void
//  Others: 		所有函数在调用键盘操作是均需要调用此函数
*************************************************/
void Keyboard::SetConfirmCommand(int command)
{
	m_confirmCommand = command;
}

/*************************************************
//  Function: 		SetCurrentWidget
//  Description: 	设置调用本键盘的窗口，用于在确认按钮按下后进行相关操作
//  Calls:		 	
//  Called By: 		所有无法直接获取其指针的窗口
//  Parameter:      QWidget*
//  Return: 		void
//  Others: 		本函数可根据需要调用
*************************************************/
void Keyboard::SetCurrentWidget(QWidget* currentWidget)
{
	m_currentWidget = currentWidget;
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
	InitLayout();
	InitSignalSlot();
	ChangeToLower();
	m_isLower = true;
	m_keyboardInterface = NULL;	/*函数指针为NULL*/
}

void Keyboard::InitLayout()
{
	this->setWindowFlags(Qt::Popup);
	
	/*设置位置及大小*/
	QRect rect = TeachingBoxContext::GetScreenRect();
	this->setGeometry(rect.left(), rect.top(), rect.width(), rect.height());

	//this->setWindowModality(Qt::ApplicationModal);	/*其它窗口无效化*/

	/*总布局*/
	//this->setMinimumWidth(SCREEN_CENTER_WIDTH);
	//this->setMinimumHeight(SCREEN_HEIGHT / 3);
	//this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

	QVBoxLayout* layoutWhole = new QVBoxLayout(this);
	QHBoxLayout* layoutText = new QHBoxLayout;
	QHBoxLayout* layoutLine1 = new QHBoxLayout;
	QHBoxLayout* layoutLine2 = new QHBoxLayout;
	QHBoxLayout* layoutLine3 = new QHBoxLayout;
	QHBoxLayout* layoutLine4 = new QHBoxLayout;
	QHBoxLayout* layoutLine5 = new QHBoxLayout;
	QHBoxLayout* layoutLine6 = new QHBoxLayout;

	layoutWhole->setMargin(0);
	layoutWhole->setSpacing(0);
	layoutText->setSpacing(0);
	layoutLine1->setSpacing(0);
	layoutLine2->setSpacing(0);
	layoutLine3->setSpacing(0);
	layoutLine4->setSpacing(0);
	layoutLine5->setSpacing(0);
	layoutLine6->setSpacing(0);

	layoutWhole->addLayout(layoutText);
	layoutWhole->addLayout(layoutLine1);
	layoutWhole->addLayout(layoutLine2);
	layoutWhole->addLayout(layoutLine3);
	layoutWhole->addLayout(layoutLine4);
	layoutWhole->addLayout(layoutLine5);
	layoutWhole->addLayout(layoutLine6);

//////////////////////////////////////////////////////////////////////////
	/*初始化控件*/
//////////////////////////////////////////////////////////////////////////
	/*初始化文本控件*/
	m_lineEditText = new QLineEdit;
	layoutText->addWidget(m_lineEditText);

	/*初始化数字按键*/
	m_btnNum0 = new KeyboardButton(QString("0"));
	m_btnNum1 = new KeyboardButton(QString("1"));
	m_btnNum2 = new KeyboardButton(QString("2"));
	m_btnNum3 = new KeyboardButton(QString("3"));
	m_btnNum4 = new KeyboardButton(QString("4"));
	m_btnNum5 = new KeyboardButton(QString("5"));
	m_btnNum6 = new KeyboardButton(QString("6"));
	m_btnNum7 = new KeyboardButton(QString("7"));
	m_btnNum8 = new KeyboardButton(QString("8"));
	m_btnNum9 = new KeyboardButton(QString("9"));

	m_btnNum0->setObjectName("btnNum");
	m_btnNum1->setObjectName("btnNum");
	m_btnNum2->setObjectName("btnNum");
	m_btnNum3->setObjectName("btnNum");
	m_btnNum4->setObjectName("btnNum");
	m_btnNum5->setObjectName("btnNum");
	m_btnNum6->setObjectName("btnNum");
	m_btnNum7->setObjectName("btnNum");
	m_btnNum8->setObjectName("btnNum");
	m_btnNum9->setObjectName("btnNum");

	/*初始化字母按键*/
	m_btnA = new KeyboardButton(QString("A"));
	m_btnB = new KeyboardButton(QString("B"));
	m_btnC = new KeyboardButton(QString("C"));
	m_btnD = new KeyboardButton(QString("D"));
	m_btnE = new KeyboardButton(QString("E"));
	m_btnF = new KeyboardButton(QString("F"));
	m_btnG = new KeyboardButton(QString("G"));
	m_btnH = new KeyboardButton(QString("H"));
	m_btnI = new KeyboardButton(QString("I"));
	m_btnJ = new KeyboardButton(QString("J"));
	m_btnK = new KeyboardButton(QString("K"));
	m_btnL = new KeyboardButton(QString("L"));
	m_btnM = new KeyboardButton(QString("M"));
	m_btnN = new KeyboardButton(QString("N"));
	m_btnO = new KeyboardButton(QString("O"));
	m_btnP = new KeyboardButton(QString("P"));
	m_btnQ = new KeyboardButton(QString("Q"));
	m_btnR = new KeyboardButton(QString("R"));
	m_btnS = new KeyboardButton(QString("S"));
	m_btnT = new KeyboardButton(QString("T"));
	m_btnU = new KeyboardButton(QString("U"));
	m_btnV = new KeyboardButton(QString("V"));
	m_btnW = new KeyboardButton(QString("W"));
	m_btnX = new KeyboardButton(QString("X"));
	m_btnY = new KeyboardButton(QString("Y"));
	m_btnZ = new KeyboardButton(QString("Z"));

	m_btnA->setObjectName("btnLetter");
	m_btnB->setObjectName("btnLetter");
	m_btnC->setObjectName("btnLetter");
	m_btnD->setObjectName("btnLetter");
	m_btnE->setObjectName("btnLetter");
	m_btnF->setObjectName("btnLetter");
	m_btnG->setObjectName("btnLetter");
	m_btnH->setObjectName("btnLetter");
	m_btnI->setObjectName("btnLetter");
	m_btnJ->setObjectName("btnLetter");
	m_btnK->setObjectName("btnLetter");
	m_btnL->setObjectName("btnLetter");
	m_btnM->setObjectName("btnLetter");
	m_btnN->setObjectName("btnLetter");
	m_btnO->setObjectName("btnLetter");
	m_btnP->setObjectName("btnLetter");
	m_btnQ->setObjectName("btnLetter");
	m_btnR->setObjectName("btnLetter");
	m_btnS->setObjectName("btnLetter");
	m_btnT->setObjectName("btnLetter");
	m_btnU->setObjectName("btnLetter");
	m_btnV->setObjectName("btnLetter");
	m_btnW->setObjectName("btnLetter");
	m_btnX->setObjectName("btnLetter");
	m_btnY->setObjectName("btnLetter");
	m_btnZ->setObjectName("btnLetter");

	/*初始化符号按键*/
	m_btnLeftBracket = new KeyboardButton(QString("["));
	m_btnRightBracket = new KeyboardButton(QString("]"));
	m_btnQuotation = new KeyboardButton(QString("\'"));
	m_btnTilde = new KeyboardButton(QString("~"));
	m_btnSemicolon = new KeyboardButton(QString(";"));
	m_btnMinus = new KeyboardButton(QString("-"));
	m_btnPlus = new KeyboardButton(QString("+"));
	m_btnComma = new KeyboardButton(QString(","));
	m_btnPeriod = new KeyboardButton(QString("."));
	m_btnSlash = new KeyboardButton(QString("/"));
	m_btnBackSlash = new KeyboardButton(QString("\\"));
	m_btnEqual = new KeyboardButton(QString("="));

	m_btnLeftBracket->setObjectName("btnSymbol");
	m_btnRightBracket->setObjectName("btnSymbol");
	m_btnQuotation->setObjectName("btnSymbol");
	m_btnTilde->setObjectName("btnSymbol");
	m_btnSemicolon->setObjectName("btnSymbol");
	m_btnMinus->setObjectName("btnSymbol");
	m_btnPlus->setObjectName("btnSymbol");
	m_btnComma->setObjectName("btnSymbol");
	m_btnPeriod->setObjectName("btnSymbol");
	m_btnSlash->setObjectName("btnSymbol");
	m_btnBackSlash->setObjectName("btnSymbol");
	m_btnEqual->setObjectName("btnSymbol");

	/*初始化功能按键*/
	m_btnTab = new KeyboardButton(QString("Tab"));
	m_btnCapsLock = new KeyboardButton(QString("Caps Lock"));
	m_btnEnter = new KeyboardButton(QString("Enter"));
	m_btnShift = new KeyboardButton(QString("Shift"));
	m_btnBackspace = new KeyboardButton(QString("<-"));
	m_btnCtrl = new KeyboardButton(QString("Ctrl"));
	m_btnAlt = new KeyboardButton(QString("Alt"));
	m_btnSpace = new KeyboardButton(QString(""));
	m_btnUp = new KeyboardButton(QString("up"));
	m_btnLf = new KeyboardButton(QString("Lf"));
	m_btnBt = new KeyboardButton(QString("Bt"));
	m_btnRg = new KeyboardButton(QString("Rg"));

	m_btnTab->setObjectName("btnOther");
	m_btnCapsLock->setObjectName("btnOther");
	m_btnEnter->setObjectName("btnOther");
	m_btnShift->setObjectName("btnOther");
	m_btnBackspace->setObjectName("btnOther");
	m_btnCtrl->setObjectName("btnOther");
	m_btnAlt->setObjectName("btnOther");
	m_btnSpace->setObjectName("btnOther");
	m_btnUp->setObjectName("btnOther");
	m_btnLf->setObjectName("btnOther");
	m_btnBt->setObjectName("btnOther");
	m_btnRg->setObjectName("btnOther");

	/*初始化确认、取消按键*/
	m_btnCancle = new KeyboardButton(QCoreApplication::translate(CLASS_NAME, "Cancle"));
	m_btnConfirm = new KeyboardButton(QCoreApplication::translate(CLASS_NAME, "Confirm"));

	m_btnCancle->setObjectName("btnSpecial");
	m_btnConfirm->setObjectName("btnSpecial");

//////////////////////////////////////////////////////////////////////////
	/*布局*/
//////////////////////////////////////////////////////////////////////////
	/*第一行布局*/
	layoutLine1->addWidget(m_btnTilde);
	layoutLine1->addWidget(m_btnNum1);
	layoutLine1->addWidget(m_btnNum2);
	layoutLine1->addWidget(m_btnNum3);
	layoutLine1->addWidget(m_btnNum4);
	layoutLine1->addWidget(m_btnNum5);
	layoutLine1->addWidget(m_btnNum6);
	layoutLine1->addWidget(m_btnNum7);
	layoutLine1->addWidget(m_btnNum8);
	layoutLine1->addWidget(m_btnNum9);
	layoutLine1->addWidget(m_btnNum0);
	layoutLine1->addWidget(m_btnMinus);
	layoutLine1->addWidget(m_btnPlus);
	layoutLine1->addWidget(m_btnBackspace);


	/*layoutLine1->setStretch(0, 1);
	layoutLine1->setStretch(1, 1);
	layoutLine1->setStretch(2, 1);
	layoutLine1->setStretch(3, 1);
	layoutLine1->setStretch(4, 1);
	layoutLine1->setStretch(5, 1);
	layoutLine1->setStretch(6, 1);
	layoutLine1->setStretch(7, 1);
	layoutLine1->setStretch(8, 1);
	layoutLine1->setStretch(9, 1);
	layoutLine1->setStretch(10, 1);
	layoutLine1->setStretch(11, 1);
	layoutLine1->setStretch(12, 1);
	layoutLine1->setStretch(13, 1);*/

	/*第二行布局*/
	layoutLine2->addWidget(m_btnTab);
	layoutLine2->addWidget(m_btnQ);
	layoutLine2->addWidget(m_btnW);
	layoutLine2->addWidget(m_btnE);
	layoutLine2->addWidget(m_btnR);
	layoutLine2->addWidget(m_btnT);
	layoutLine2->addWidget(m_btnY);
	layoutLine2->addWidget(m_btnU);
	layoutLine2->addWidget(m_btnI);
	layoutLine2->addWidget(m_btnO);
	layoutLine2->addWidget(m_btnP);
	layoutLine2->addWidget(m_btnLeftBracket);
	layoutLine2->addWidget(m_btnRightBracket);
	layoutLine2->addWidget(m_btnEqual);

	//layoutLine2->setStretch(0, 1);
	//layoutLine2->setStretch(1, 1);
	//layoutLine2->setStretch(2, 1);
	//layoutLine2->setStretch(3, 1);
	//layoutLine2->setStretch(4, 1);
	//layoutLine2->setStretch(5, 1);
	//layoutLine2->setStretch(6, 1);
	//layoutLine2->setStretch(7, 1);
	//layoutLine2->setStretch(8, 1);
	//layoutLine2->setStretch(9, 1);
	//layoutLine2->setStretch(10, 1);
	//layoutLine2->setStretch(11, 1);
	//layoutLine2->setStretch(12, 1);


	/*第三行布局*/
	layoutLine3->addWidget(m_btnCapsLock);
	layoutLine3->addWidget(m_btnA);
	layoutLine3->addWidget(m_btnS);
	layoutLine3->addWidget(m_btnD);
	layoutLine3->addWidget(m_btnF);
	layoutLine3->addWidget(m_btnG);
	layoutLine3->addWidget(m_btnH);
	layoutLine3->addWidget(m_btnJ);
	layoutLine3->addWidget(m_btnK);
	layoutLine3->addWidget(m_btnL);
	layoutLine3->addWidget(m_btnSemicolon);
	layoutLine3->addWidget(m_btnEnter);

	layoutLine3->setStretch(0, 3);
	layoutLine3->setStretch(1, 2);
	layoutLine3->setStretch(2, 2);
	layoutLine3->setStretch(3, 2);
	layoutLine3->setStretch(4, 2);
	layoutLine3->setStretch(5, 2);
	layoutLine3->setStretch(6, 2);
	layoutLine3->setStretch(7, 2);
	layoutLine3->setStretch(8, 2);
	layoutLine3->setStretch(9, 2);
	layoutLine3->setStretch(10, 2);
	layoutLine3->setStretch(11, 3);

	/*第四行*/
	layoutLine4->addWidget(m_btnShift);
	layoutLine4->addWidget(m_btnZ);
	layoutLine4->addWidget(m_btnX);
	layoutLine4->addWidget(m_btnC);
	layoutLine4->addWidget(m_btnV);
	layoutLine4->addWidget(m_btnB);
	layoutLine4->addWidget(m_btnN);
	layoutLine4->addWidget(m_btnM);
	layoutLine4->addWidget(m_btnComma);
	layoutLine4->addWidget(m_btnPeriod);
	layoutLine4->addWidget(m_btnSlash);
	layoutLine4->addWidget(m_btnBackSlash);
	layoutLine4->addWidget(m_btnUp);
	layoutLine4->addWidget(m_btnQuotation);

	/*第五行布局*/
	layoutLine5->addWidget(m_btnCtrl);
	layoutLine5->addWidget(m_btnAlt);
	layoutLine5->addWidget(m_btnSpace);
	layoutLine5->addWidget(m_btnLf);
	layoutLine5->addWidget(m_btnBt);
	layoutLine5->addWidget(m_btnRg);

	layoutLine5->setStretch(0, 1);
	layoutLine5->setStretch(1, 1);
	layoutLine5->setStretch(2, 9);
	layoutLine5->setStretch(3, 1);
	layoutLine5->setStretch(4, 1);
	layoutLine5->setStretch(5, 1);

	/*第六行布局*/
	layoutLine6->addWidget(m_btnCancle);
	layoutLine6->addWidget(m_btnConfirm);
}

void Keyboard::InitSignalSlot()
{
	QList<KeyboardButton*> btnList = this->findChildren<KeyboardButton*>();
    for (auto button : btnList)
	{
		connect(button, SIGNAL(clicked()), this, SLOT(SlotOnButtonClicked()));
	}
}

/*不同窗口内键盘确认按钮事件*/
void Keyboard::OnButtonConfirmClicked()
{
	/*若函数不为空*/
	if (m_keyboardInterface != NULL)
	{
		m_keyboardInterface->KeyboardEdit();
	}
	Clear();
	this->hide();
	return;

	//switch (m_confirmCommand)
	//{
	///*编辑*/
	//case CONFIRM_SCREEN_PROGRAM_EDIT_PROGRAM:
	//{
	//	CScreenPragram::GetInstance()->KeyboardEdit();
	//}break;
	//default:
	//	break;
	//}

	//this->hide();
}

void Keyboard::ChangeToLower()
{
	/*初始化数字按键*/
	m_btnNum0->setText(QString("0"));
	m_btnNum1->setText(QString("1"));
	m_btnNum2->setText(QString("2"));
	m_btnNum3->setText(QString("3"));
	m_btnNum4->setText(QString("4"));
	m_btnNum5->setText(QString("5"));
	m_btnNum6->setText(QString("6"));
	m_btnNum7->setText(QString("7"));
	m_btnNum8->setText(QString("8"));
	m_btnNum9->setText(QString("9"));

	/*初始化字母按键*/
	m_btnA->setText(QString("a"));
	m_btnB->setText(QString("b"));
	m_btnC->setText(QString("c"));
	m_btnD->setText(QString("d"));
	m_btnE->setText(QString("e"));
	m_btnF->setText(QString("f"));
	m_btnG->setText(QString("g"));
	m_btnH->setText(QString("h"));
	m_btnI->setText(QString("i"));
	m_btnJ->setText(QString("j"));
	m_btnK->setText(QString("k"));
	m_btnL->setText(QString("l"));
	m_btnM->setText(QString("m"));
	m_btnN->setText(QString("n"));
	m_btnO->setText(QString("o"));
	m_btnP->setText(QString("p"));
	m_btnQ->setText(QString("q"));
	m_btnR->setText(QString("r"));
	m_btnS->setText(QString("s"));
	m_btnT->setText(QString("t"));
	m_btnU->setText(QString("u"));
	m_btnV->setText(QString("v"));
	m_btnW->setText(QString("w"));
	m_btnX->setText(QString("x"));
	m_btnY->setText(QString("y"));
	m_btnZ->setText(QString("z"));

	/*初始化符号按键*/
	m_btnLeftBracket->setText(QString("["));
	m_btnRightBracket->setText(QString("]"));
	m_btnQuotation->setText(QString("\'"));
	m_btnTilde->setText(QString("`"));
	m_btnSemicolon->setText(QString(";"));
	m_btnMinus->setText(QString("-"));
	m_btnPlus->setText(QString("+"));
	m_btnComma->setText(QString(","));
	m_btnPeriod->setText(QString("."));
	m_btnSlash->setText(QString("/"));
	m_btnBackSlash->setText(QString("\\"));
	m_btnEqual->setText(QString("="));

	m_isLower = true;
}

void Keyboard::ChangeToUpper()
{
	/*初始化数字按键*/
	m_btnNum0->setText(QString(")"));
	m_btnNum1->setText(QString("!"));
	m_btnNum2->setText(QString("@"));
	m_btnNum3->setText(QString("#"));
	m_btnNum4->setText(QString("$"));
	m_btnNum5->setText(QString("%"));
	m_btnNum6->setText(QString("^"));
	m_btnNum7->setText(QString("&"));
	m_btnNum8->setText(QString("*"));
	m_btnNum9->setText(QString("("));

	/*初始化字母按键*/
	m_btnA->setText(QString("A"));
	m_btnB->setText(QString("B"));
	m_btnC->setText(QString("C"));
	m_btnD->setText(QString("D"));
	m_btnE->setText(QString("E"));
	m_btnF->setText(QString("F"));
	m_btnG->setText(QString("G"));
	m_btnH->setText(QString("H"));
	m_btnI->setText(QString("I"));
	m_btnJ->setText(QString("J"));
	m_btnK->setText(QString("K"));
	m_btnL->setText(QString("L"));
	m_btnM->setText(QString("M"));
	m_btnN->setText(QString("N"));
	m_btnO->setText(QString("O"));
	m_btnP->setText(QString("P"));
	m_btnQ->setText(QString("Q"));
	m_btnR->setText(QString("R"));
	m_btnS->setText(QString("S"));
	m_btnT->setText(QString("T"));
	m_btnU->setText(QString("U"));
	m_btnV->setText(QString("V"));
	m_btnW->setText(QString("W"));
	m_btnX->setText(QString("X"));
	m_btnY->setText(QString("Y"));
	m_btnZ->setText(QString("Z"));

	/*初始化符号按键*/
	m_btnLeftBracket->setText(QString("{"));
	m_btnRightBracket->setText(QString("}"));
	m_btnQuotation->setText(QString("\""));
	m_btnTilde->setText(QString("~"));
	m_btnSemicolon->setText(QString(";"));
	m_btnMinus->setText(QString("_"));
	m_btnPlus->setText(QString("+"));
	m_btnComma->setText(QString("<"));
	m_btnPeriod->setText(QString(">"));
	m_btnSlash->setText(QString("?"));
	m_btnBackSlash->setText(QString("|"));
	m_btnEqual->setText(QString("="));

	m_isLower = false;
}

void Keyboard::Clear()
{
	m_keyboardInterface = NULL;
	m_lineEditText->clear();
}

void Keyboard::showEvent(QShowEvent *event)
{
	QWidget::showEvent(event);
	this->move(TeachingBoxContext::GetScreenRect().left(),TeachingBoxContext::GetScreenRect().top());
}

void Keyboard::hideEvent(QHideEvent *event)
{
	QWidget::hideEvent(event);

	m_lineEditText->clear();
}

/*鼠标点击事件*/
void Keyboard::SlotOnButtonClicked()
{
	KeyboardButton* button = (KeyboardButton*)sender();	/*点击的按键*/
	QString objectName = button->objectName();	

	/*若为数字、字母或符号，则直接写入*/
	if (objectName == "btnNum"|| objectName=="btnLetter"||objectName=="btnSymbol")
	{
		m_lineEditText->insert(button->text());
	}
	else if (objectName == "btnSpecial")
	{
		if (button == m_btnConfirm)
		{
			OnButtonConfirmClicked();
		}
		else if (button==m_btnCancle)
		{
			m_lineEditText->clear();
			this->hide();
		}
	}
	else if(objectName == "btnOther")
	{
		/*若为tab键，则向后移动一定空格*/
		if (button == m_btnTab)
		{
			int spaceNum = 8-m_lineEditText->text().length() % 8;
			for (int i = 0; i < spaceNum;++i)
			{
				m_lineEditText->insert(" ");
			}
		}
		else if (button == m_btnCapsLock)
		{
			QMessageBox::about(this, button->text(), button->text());
		}
		else if (button==m_btnEnter)
		{
			QMessageBox::about(this, button->text(), button->text());
		}
		else if (button==m_btnShift)
		{
			/*若是小写字符*/
			if (m_isLower)
			{
				ChangeToUpper();
			}
			else
			{
				ChangeToLower();
			}
		}
		else if (button==m_btnBackspace)
		{
			m_lineEditText->backspace();
		}
		else if (button==m_btnCtrl)
		{
			QMessageBox::about(this, button->text(), button->text());
		}
		else if (button==m_btnAlt)
		{
			QMessageBox::about(this, button->text(), button->text());
		}
		else if (button==m_btnSpace)
		{
			m_lineEditText->insert(" ");
		}
		else if (button == m_btnUp)
		{
			QMessageBox::about(this, button->text(), button->text());
		}
		else if (button==m_btnLf)
		{
			QMessageBox::about(this, button->text(), button->text());
		}
		else if (button==m_btnBt)
		{
			QMessageBox::about(this, button->text(), button->text());
		}
		else if (button == m_btnRg)
		{
			QMessageBox::about(this, button->text(), button->text());
		}
	}
}
