#include "stdafx.h"
#include "TInterpreterException.h"
#include "Context.h"
#include "TInterpreterInfo.h"

TInterpreterException::TInterpreterException(const InterpreterExceptionCode id, const int lineNumber, const QString& text/*=""*/)
	: m_id(id), m_lineNumber(lineNumber), m_text(text)
{

}

QString TInterpreterException::Info()
{
	const int SIZE_ADDED = 2;

	QString text = Format(TInterpreterInfo::InformationText()+":", SIZE_ADDED) + TInterpreterInfo::GetInfo(m_id) + "\n"
		+ Format(TInterpreterInfo::ProgramText() + ":", SIZE_ADDED) + Context::interpreterContext.GetProgramLoading() + "\n"
		+ Format(TInterpreterInfo::LineNumberText() + ":", SIZE_ADDED) + QString::number(m_lineNumber);

	if (m_text.size() > 0)
	{
		text.append("\n" + Format("Text:", SIZE_ADDED) + m_text);
	}
	return text;
}

int TInterpreterException::LineNumber() const
{
	return m_lineNumber;
}

inline
QString TInterpreterException::Format(const QString& text, int size)
{
	QString result{ text };
	for (int i = 0; i < size;++i)
	{
		result.append(" ");
	}

	return result;
}

