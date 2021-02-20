#include "stdafx.h"
#include "TeachingBoxInitialization.h"
#include "TRefSys.h"
#include "ProjectContext.h"
#include "TToolSys.h"
#include "Language.h"
#include "User.h"
#include "UserDatabase.h"
#include "TVariateManager.h"



std::shared_ptr<User> TeachingBoxInitialization::Adminastrator()
{
	return std::make_shared<User>("Adminastrator", "123456", 16, Language::English());
}

std::shared_ptr<TToolSys> TeachingBoxInitialization::DefaultToolSys()
{
	return std::make_shared<TToolSys>(TSymbol(ProjectContext::ScopeSystem(), "DefaultTool"));
}

std::shared_ptr<TRefSys> TeachingBoxInitialization::WorldRefSys()
{
	return std::make_shared<TRefSys>(TSymbol(ProjectContext::ScopeSystem(), "World"));
}



TeachingBoxInitialization::TeachingBoxInitialization()
{
	/*检查用户信息*/
	auto adminastrator = Adminastrator();
	if (Database::UserDatabase::SelectUser(adminastrator->GetName()).GetName().size() == 0)
	{
		Database::UserDatabase::InsertUserInfo(*adminastrator);
	}

	/*检查默认工具坐标系*/
	auto defaultSys = DefaultToolSys();
	if (!TVariateManager::GetInstance()->GetVariate(defaultSys->GetScope(),defaultSys->GetName()))
	{
		TVariateManager::GetInstance()->AddVariate(defaultSys);
	}

	/*检查默认世界坐标系*/
	auto worldSys = WorldRefSys();
	if (!TVariateManager::GetInstance()->GetVariate(worldSys->GetScope(), worldSys->GetName()))
	{
		TVariateManager::GetInstance()->AddVariate(worldSys);
	}
}

