#include "stdafx.h"
#include "ProjectContext.h"


ProjectContext::ProjectContext()
	:SCOPE_ORI(QStringList{ STR_SCOPE_SYSTEM, STR_SCOPE_SYNERGIC, STR_SCOPE_GLOBAL })
{
	m_currentScopes.append(SCOPE_ORI);
}

QStringList ProjectContext::GetScopes()
{
	return m_currentScopes;
}

void ProjectContext::SetLoadedProject(const QString& project, const QStringList& programs)
{
	m_project = project;
	m_programs = programs;

	m_currentScopes = SCOPE_ORI;
	m_currentScopes.append(m_project);
	m_currentScopes.append(m_programs);
}
