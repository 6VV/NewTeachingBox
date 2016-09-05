#include "stdafx.h"
#include "ProjectContext.h"


//const QString ProjectContext::STR_SCOPE_SYSTEM = "SYSTEM";		/*系统作用域*/
//
//const QString ProjectContext::STR_SCOPE_SYNERGIC = "SYNERGIC";	/*协作作用域*/
//
//const QString ProjectContext::STR_SCOPE_GLOBAL = "GLOBAL";		/*全局作用域*/
//
//const QString ProjectContext::STR_SCOPE_PROJECT = "PROJECT";		/*项目作用域*/

//const QStringList ProjectContext::SCOPE_ORI{ STR_SCOPE_SYSTEM, STR_SCOPE_SYNERGIC, STR_SCOPE_GLOBAL };

ProjectContext::ProjectContext()
	:SCOPE_ORI(QStringList{ STR_SCOPE_SYSTEM, STR_SCOPE_SYNERGIC, STR_SCOPE_GLOBAL })
{
	m_currentScopes.append(SCOPE_ORI);
}

QStringList ProjectContext::GetScopes()
{
	return m_currentScopes;
}
