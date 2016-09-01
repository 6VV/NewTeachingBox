#ifndef _TEACHING_BOX_WARNING_MANAGER_H_
#define _TEACHING_BOX_WARNING_MANAGER_H_

#include "SingleTon.h"

class QWidget;

class WarningManager
{
	friend SingleTon<WarningManager>;

public:
	enum WarningCode
	{
		NameIsEmpty,		/*名称为空*/
		NameIsTooLong,		/*名称过长*/
		PleaseSelectScope,	/*请选择作用域*/
		PleaseSelectVariable,	/*请选择变量*/
		AlreadyExitVariable,	/*已存在该变量*/
		AlreadyLoadOtherProject,	/*已加载其它项目*/
		ForbidDelete,		/*禁止删除*/
		NotFindVariable,	/*未找到变量*/
		WrongName,	/*错误的变量名*/
	};

public:
	static WarningManager* GetInstance();

	static void Warning(QWidget* widget, QString strText);

	static void Warning(QWidget* widget, WarningCode);

private:
	WarningManager();
	WarningManager(const WarningManager&);
	WarningManager& operator=(const WarningManager&);
	~WarningManager();
	
private:

};

#endif