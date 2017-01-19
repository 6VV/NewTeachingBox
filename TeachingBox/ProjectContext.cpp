#include "stdafx.h"
#include "ProjectContext.h"


const QString ProjectContext::ScopeSystem()
{
	return "SYSTEM";
}

const QString ProjectContext::ScopeCooperate()
{
	return "COOPERATE";
}

const QString ProjectContext::ScopeGlobal()
{
	return "GLOBAL";
}

//const QString ProjectContext::STR_SCOPE_SYSTEM = "SYSTEM";
//
//const QString ProjectContext::STR_SCOPE_SYNERGIC = "SYNERGIC";
//
//const QString ProjectContext::STR_SCOPE_GLOBAL = "GLOBAL";

ProjectContext::ProjectContext()
	:SCOPE_ORI(QStringList{ ScopeSystem(), ScopeCooperate(), ScopeGlobal() })
{
	m_currentScopes.append(SCOPE_ORI);
}

QStringList ProjectContext::AllCurrentScopes()
{
	m_currentScopes = SCOPE_ORI;
	if (m_project.size()!=0)
	{
		m_currentScopes.append(m_project);
	}
	
	if (m_programs.size()!=0)
	{
		m_currentScopes.append(m_programs);
	}

	return m_currentScopes;
}

QString ProjectContext::CurrentScope()
{
	if (!m_programOpened.isEmpty())
	{
		return m_programOpened;
	}

	if (!m_project.isEmpty())
	{
		return m_project;
	}

	return ScopeGlobal();
}

const QStringList& ProjectContext::Programs() const
{
	return m_programs;
}

QString ProjectContext::ProjectLoaded()
{
	return m_project;
}

QString ProjectContext::ProgramOpened() const
{
	return m_programOpened;
}


//void ProjectContext::ProgramLoading(const QString& program)
//{
//	m_programLoading = program;
//}
//
//QString ProjectContext::ProgramLoading() const
//{
//	return m_programLoading;
//}

void ProjectContext::SetLoadedProject(const QString& project, const QStringList& programs)
{
	m_project = project;
	m_programs = programs;
}

void ProjectContext::ProgramOpened(const QString& file)
{
	m_programOpened = file;
}


bool ProjectContext::IsCurrentFileLoad()
{
	if (m_programs.contains(m_programOpened))
	{
		return true;
	}
	return false;
}


void ProjectContext::UnloadProject()
{
	m_project = QString{};
	m_programs = QStringList{};

	m_currentScopes = SCOPE_ORI;
}
