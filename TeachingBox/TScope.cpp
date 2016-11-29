#include "stdafx.h"
#include "TScope.h"
#include "TSymbol.h"
#include "TVariate.h"

//const QString TScope::STR_SCOPE_SYSTEM = "SYSTEM";		/*系统作用域*/
//const QString TScope::STR_SCOPE_SYNERGIC = "SYNERGIC";	/*协作作用域*/
//const QString TScope::STR_SCOPE_GLOBAL = "GLOBAL";		/*全局作用域*/
//const QString TScope::STR_SCOPE_PROJECT = "PROJECT";		/*项目作用域*/
////const QString TScope::STR_SCOPE_LOCAL = "LOCAL";		/*局部作用域*/
//
//const QStringList TScope::SCOPE_ORI = QStringList{ TScope::STR_SCOPE_SYSTEM, TScope::STR_SCOPE_SYNERGIC, TScope::STR_SCOPE_GLOBAL };

QString& TScope::GetScopeName()
{
	return m_scopeName;
}

void TScope::SetScopeName(const QString& strScopeName)
{
	m_scopeName = strScopeName;
}

TScope* TScope::GetEnclosingScope()
{
	return m_enclosingScope;
}

void TScope::PushScope(TScope* scope)
{
	this->m_listScope.push_back(scope);
	scope->m_enclosingScope = this;
	//scope->SetEnclosingScope(this);
}

QString TScope::ScopeName() const
{
	return m_scopeName;
}

TScope* TScope::ParentScope() const
{
	return m_enclosingScope;
}

void TScope::DefineSymbol(TSymbol* sym)
{
	this->m_mapSymbol[sym->GetName()] = sym;
}

bool TScope::DefineSymbol(const QString& desScope, TSymbol* symbol)
{
	TScope* scopeFound = FindScopeScrollDown(desScope);
	if (!scopeFound)
	{
		return false;
	}
	scopeFound->DefineSymbol(symbol);
	return true;
}

void TScope::DeleteSymbol(const QString& strName)
{
	auto iter = m_mapSymbol.find(strName);

	if (iter!=m_mapSymbol.end())
	{
		delete(iter.value());
		m_mapSymbol.erase(iter);
	}
}

TSymbol* TScope::FindSymbolScrollUp(const QString& name)
{
	auto iter = m_mapSymbol.find(name);

	/*若找到*/
	if (iter!=m_mapSymbol.end())
	{
		return iter.value();
	}
	else
	{
		/*若不存在上层作用域*/
		if (this->m_enclosingScope==NULL)
		{
			return NULL;
		}
		else
		{
			return m_enclosingScope->FindSymbolScrollUp(name);
		}
	}
}

TSymbol* TScope::FindSymbolInSelf(const QString& strName)
{
	auto iter = m_mapSymbol.find(strName);

	/*若找到*/
	if (iter != m_mapSymbol.end())
	{
		return iter.value();
	}
	else
	{
		return NULL;
	}
}

TScope* TScope::FindScopeScrollDown(const QString& strScope)
{
	if (m_scopeName==strScope)
	{
		return this;
	}
	
	/*若不存在子作用域*/
	if (m_listScope.size()==0)
	{
		return nullptr;
	}

	/*遍历子作用域*/
    for (auto var : m_listScope)
	{
		TScope* scope = var->FindScopeScrollDown(strScope);
		if (scope != nullptr)
		{
			return scope;
		}
	}

	/*未找到*/
	return nullptr;
}

TScope::ScopeSymbol TScope::FindSymbolScopeScrollUp(const QString& strSymbolName)
{
	ScopeSymbol scopySymbol;
	auto iter = m_mapSymbol.find(strSymbolName);

	/*若找到*/
	if (iter != m_mapSymbol.end())
	{
		scopySymbol.scope = this;
		scopySymbol.symbol = iter.value();

		return scopySymbol;
	}
	else
	{
		/*若不存在上层作用域*/
		if (this->m_enclosingScope == NULL)
		{
			return scopySymbol;
		}
		else
		{
			return m_enclosingScope->FindSymbolScopeScrollUp(strSymbolName);
		}
	}

}

//void CScope::SetEnclosingScope(CScope* enclosingScope)
//{
//	this->m_enclosingScope = enclosingScope;
//}


void TScope::RenameSymbol(const QString& oldName, const QString& newName, TSymbol* symbol)
{
	auto iter = m_mapSymbol.find(oldName);

	/*若找到*/
	if (iter != m_mapSymbol.end())
	{
		delete(iter.value());
		m_mapSymbol.erase(iter);
		m_mapSymbol[newName] = symbol;
	}
}

void TScope::ClearChildren()
{
    for (auto var : m_listScope)
	{
		delete(var);
	}
	m_listScope.clear();

}

void TScope::ClearSelf()
{
    for (auto var : m_mapSymbol)
	{
		delete(var);
	}
	m_mapSymbol.clear();
}

TScope::TScope(const QString& name)
{
	this->m_scopeName = name;
}

TScope::TScope()
{

}

TScope::~TScope()
{
	ClearChildren();
	ClearSelf();
}

void TScope::AddVariate(const TVariate* variate)
{
	TSymbol* symbol = new TSymbol(variate->GetScope(), variate->GetName(), variate->GetType());
	TScope* scopeFound = FindScopeScrollDown(variate->GetScope());

	if (scopeFound)
	{
		scopeFound->DefineSymbol(variate->GetScope(), symbol);
	}
}


void TScope::DeleteVariate(const QString& scope, const QString& name)
{
	if (TScope* scopeFound = FindScopeScrollDown(scope))
	{
		scopeFound->DeleteSymbol(name);
	}
}

void TScope::UpdateVariate(const QString& scope, const QString& name, const TVariate* variate)
{
	TSymbol* symbol = new TSymbol(variate->GetScope(), variate->GetName(), variate->GetType());
	TScope* scopeFound = FindScopeScrollDown(scope);
	if (scopeFound)
	{
		scopeFound->RenameSymbol(name, variate->GetName(), symbol);
	}
}
