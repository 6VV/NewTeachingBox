#ifndef _TEACHING_BOX_T_SCOPE_H_
#define _TEACHING_BOX_T_SCOPE_H_

#include <QList>
#include <QHash>

class TSymbol;
class TVariate;

class TScope
{
public:
	typedef QHash<QString, TSymbol*> TYPE_MAP_SYMBOL;
	typedef QList<TScope*> TYPE_LIST_SCOPE;

	//static const QString STR_SCOPE_SYSTEM;		/*系统作用域*/
	//static const QString STR_SCOPE_SYNERGIC;	/*协作作用域*/
	//static const QString STR_SCOPE_GLOBAL;		/*全局作用域*/
	//static const QString STR_SCOPE_PROJECT;		/*项目作用域*/
	////static const QString STR_SCOPE_LOCAL;		/*局部作用域*/

	//static const QStringList SCOPE_ORI;	/*初始作用域*/

	struct ScopeSymbol 
	{
		TScope* scope=nullptr;
		TSymbol* symbol = nullptr;
	};
public:
	TScope(const QString& name);
	TScope();
	~TScope();

public:
	void AddVariate(const TVariate* variate);
	void ClearSelf();			/*清除自身作用域*/
	void DeleteVariate(const QString& scope, const QString& name);

	TSymbol* FindSymbolScrollUp(const QString& strName);	/*在自身及上层作用域内查找符号*/
	TScope* FindScopeScrollDown(const QString& scope);	/*在本作用域及以下的所有作用域查找*/

	void PushScope(TScope* scope);		/*添加子作用域*/

	QString ScopeName() const;
	TScope* ParentScope() const;

	void UpdateVariate(const QString& scope,const QString& name,const TVariate* variate);

private:
	void ClearChildren();	/*清除子作用域数据*/

	void DefineSymbol(TSymbol* sym);		/*定义作用域内符号*/
	bool DefineSymbol(const QString& desScope, TSymbol* symbol);
	void DeleteSymbol(const QString& strName);	/*从本作用域中删除符号*/

	TSymbol* FindSymbolInSelf(const QString& strName);	/*在自身作用域内查找符号*/
	ScopeSymbol FindSymbolScopeScrollUp(const QString& strSymbolName);	/*查找符号所在作用域*/

	QString& GetScopeName();	/*获取当前作用域的名称*/
	TScope* GetEnclosingScope();	/*获取上层作用域*/

	void RenameSymbol(const QString& oldName, const QString& newName, TSymbol* symbol);	/*变量重命名*/

	void SetScopeName(const QString& strScopeName);	/*设置当前作用域名*/

protected:
	TYPE_MAP_SYMBOL m_mapSymbol;	/*本层作用域内符号*/
	TYPE_LIST_SCOPE m_listScope;	/*子作用域*/
	TScope* m_enclosingScope = nullptr;		/*上层作用域*/
	QString m_scopeName;		/*作用域名*/
};

#endif