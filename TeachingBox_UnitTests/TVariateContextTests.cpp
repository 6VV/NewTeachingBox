#include "TVariateContextTests.h"
#include <memory>
#include "..\TeachingBox\TVariateContext.h"
#include "..\TeachingBox\TInteger.h"
#include "..\TeachingBox\TVariateScopeNode.h"


TEST_F(TVariateContextTests, AddVariate_Successed)
{
	TVariateContext::GetInstance()->AddVariate(std::shared_ptr<TVariate>(new TInteger(TSymbol{ "scope1", "name1" }, 1)));
	TVariateContext::GetInstance()->AddVariate(std::shared_ptr<TVariate>(new TInteger(TSymbol{ "scope1.child1", "name2" }, 2)));
	TVariateContext::GetInstance()->AddVariate(std::shared_ptr<TVariate>(new TInteger(TSymbol{ "scope2.child1", "name2" }, 2)));
	
}

