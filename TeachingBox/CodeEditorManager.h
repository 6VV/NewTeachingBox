﻿#ifndef _TEACHING_BOX_CODE_EDITOR_MANAGER_H_
#define _TEACHING_BOX_CODE_EDITOR_MANAGER_H_

#include "QObject"

class SciCodeEditor;

class CodeEditorManager:public QObject
{
	Q_OBJECT

public:
	static CodeEditorManager* GetInstance();
	
	void ClearWrongLine() const;
	QString CurrentLineText() const;
	void Cut() const;
	void Copy() const;

	void Delete() const;

	void Format() const;

	QWidget* GetWidget() const;

	void HighlightPCLine(const QString& program, int lineNumber) const;
	void HighlightCurrentPCLine() const;	/*高亮显示PC行*/
	void HighlightWrongLine(const QString& program, const int lineNumber) const;	/*高亮显示错误行*/

	void Paste() const;

	void Redo() const;

	void SelectAll() const;
	void Search(const QString& text) const;

	QString Text() const;

	void UpdateCurrentLine(const QString& text) const;
	void Undo() const;

	void InsertTextBeforeLine(const QString& text) const;	/*插入文本*/

private:
	CodeEditorManager();
	CodeEditorManager(const CodeEditorManager&) = delete;
	CodeEditorManager& operator=(const CodeEditorManager&) = delete;
	~CodeEditorManager()=default;

	void HighlightPCLine(int lineNumber) const;
	void UpdateTextFromProgram(const QString &program) const;

private:
	SciCodeEditor* m_codeEditor;
};

#endif