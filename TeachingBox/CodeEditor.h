#ifndef _TEACHING_BOX_CODE_EDITOR_H_
#define _TEACHING_BOX_CODE_EDITOR_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    CCodeEditor.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/09/05
//  Description:	代码编辑器，可显示代码行数并高亮显示部分行
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/09/05
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include <QPlainTextEdit>
#include <QColor>
#include "SingleTon.h"

class CodeEditor;

namespace
{
	/*************************************************
	//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
	//  File name: 	    CodeEditor.h
	//  Author:			刘巍
	//  Version: 		1.0
	//  Date: 			2016/09/05
	//  Description:	用于显示行数的区域
	//  Others:
	//  Function List:
	//  History:
	//    <author>      刘巍
	//    <time>        2016/09/05
	//    <version>     1.0
	//    <desc>        build this moudle
	*************************************************/
	class LineNumberArea : public QWidget
	{
	public:
		LineNumberArea(CodeEditor *editor);

		/*重定义父类函数*/
	private:
		QSize sizeHint() const Q_DECL_OVERRIDE;	/*控件默认大小*/
		void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;	/*绘制控件*/

	private:
		CodeEditor *codeEditor;
	};

	struct LightLine
	{
		LightLine(int l,const QColor& c)
			:lineNumber(l)
			, color(c)
		{}
		int lineNumber;
		QColor color;
	};

	struct LineHighlighter
	{
		static const QColor COLOR_PC;		/*蓝色，显示当前执行行*/
		static const QColor COLOR_WRONG;	/*红色，出错行*/
		static const QColor COLOR_EDIT;	/*黄色，当前编辑行*/

		LightLine pcLine={ -1, COLOR_PC };
		LightLine wrongLine={ -1, COLOR_WRONG };
		LightLine editLine={ -1, COLOR_EDIT };

		//int pcLineNumber=-1;
		//int wrongLineNumber=-1;
		//int editLineNumber=-1;
	}; 
}

class CodeEditor : public QPlainTextEdit
{
	friend SingleTon<CodeEditor>;
	friend LineNumberArea;

	Q_OBJECT


public:
	//static CodeEditor* GetInstance();

	CodeEditor(QWidget *parent = 0);
	CodeEditor(const CodeEditor&)=delete;
	CodeEditor& operator=(const CodeEditor&)=delete;
	~CodeEditor()=default;

public:
	void ClearWrongLine() ;
	QString CurrentLineText() ;

	void HighlightPCLine(int lineNumber);
	void HighlightWrongLine(const int lineNumber);	/*高亮显示错误行*/
	void HighlightCurrentPCLine() ;	/*高亮显示PC行*/

	void UpdateCurrentLine(const QString& text) ;
	void InsertTextBeforeLine(const QString& text) ;	/*插入文本*/

	/*重定义父类函数*/
protected:
	void resizeEvent(QResizeEvent *event) override;

	/*自定义槽函数*/
protected slots:
	void SlotUpdateCodeAreaWidth(int newBlockCount);	/*更新右侧区域宽度*/
	void SlotHighlightCurrentLine();	/*高亮显示某行*/
	void SlotUpdateLineNumberArea(const QRect &, int);	/*更新左侧区域*/

private:
	void AddSelection(QList<QTextEdit::ExtraSelection>& selections, const LightLine lightLine);

	int GetLineNumberAreaWidth();		/*返回左侧区域宽度*/
	QTextEdit::ExtraSelection GetSelection(int lineNumber, const QColor& color);

	void HighLightEditLine(const int lineNumber);	/*高亮显示编辑行*/
	void HighlightAllLines();	/*高亮显示行*/

	void PaintLineNumberArea(QPaintEvent *event);	/*绘制左侧行号区域*/

private:
	int m_textChangeTime = 0;
	QWidget *m_lineNumberArea;
	LineHighlighter m_lineHighlighter;

};

#endif