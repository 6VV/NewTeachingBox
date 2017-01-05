#include "stdafx.h"
#include "MacroWidgetGosub.h"
#include "QTreeWidget"
#include "CodeEditor.h"
#include "CodeEditorManager.h"



MacroWidgetGosub::MacroWidgetGosub(const QString& macroText, QWidget* parent /*= nullptr*/)
	:MacroWidgetParent(macroText,parent)
{
	QTreeWidgetItem* item = new QTreeWidgetItem(m_treeWidget, QStringList{ "Value" });

	m_programComboBox = GetProgramComboBox();
	m_treeWidget->setItemWidget(item, 1, m_programComboBox);
}

inline
QComboBox* MacroWidgetGosub::GetProgramComboBox()
{
	QComboBox* programComboBox=new QComboBox(m_treeWidget);

	auto programs = Context::projectContext.Programs();
	QStringList files;
	for (auto program : programs)
	{
		auto fileList = program.split(".");
		if (fileList.size() != 2)
		{
			continue;
		}
		files.append(fileList.at(1));
	}

	programComboBox->addItems(files);

	if (m_macroParameterList.size()>0)
	{
		programComboBox->setCurrentText(m_macroParameterList.at(0));
	}

	return programComboBox;
}

MacroWidgetGosub::~MacroWidgetGosub()
{

}

QString MacroWidgetGosub::MacroName()
{
	return "GOSUB";
}

void MacroWidgetGosub::SlotOnButtonConfirmClicked()
{
	CodeEditorManager::GetInstance()->UpdateCurrentLine(MacroName() + " " + m_programComboBox->currentText());
	delete this;
}
