#include "stdafx.h"
#include "ProjectContext.h"


const QString ProjectContext::ScopeSystem()
{
	return "SYSTEM";
}

const QString ProjectContext::ScopeSynergic()
{
	return "SYNERGIC";
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
	:SCOPE_ORI(QStringList{ ScopeSystem(), ScopeSynergic(), ScopeGlobal() })
{
	m_currentScopes.append(SCOPE_ORI);
}

QStringList ProjectContext::GetScopes()
{
	return m_currentScopes;
}

QString ProjectContext::GetProjectLoaded()
{
	return m_project;
}

QString ProjectContext::GetCurrentProgram()
{
	return m_currentProgram;
}

QString ProjectContext::GetFileOpened()
{
	return m_fileOpened;
}

void ProjectContext::SetCurrentProgram(const QString& program)
{
	m_currentProgram = program;
}

void ProjectContext::SetLoadedProject(const QString& project, const QStringList& programs)
{
	m_project = project;
	m_programs = programs;

	m_currentScopes = SCOPE_ORI;
	m_currentScopes.append(m_project);
	m_currentScopes.append(m_programs);
}

void ProjectContext::SetFileOpened(const QString& file)
{
	m_fileOpened = file;
}


bool ProjectContext::IsCurrentFileLoad()
{
	if (m_programs.contains(m_fileOpened))
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
