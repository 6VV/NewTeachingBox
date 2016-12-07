#include "TVariateContextTests.h"
#include <memory>
#include "..\TeachingBox\TVariateContext.h"
#include "..\TeachingBox\TInteger.h"
#include "..\TeachingBox\TVariateScopeNode.h"



void TVariateContextTests::SetUp()
{
	TVariateContext::GetInstance()->AddVariate(std::shared_ptr<TVariate>(new TInteger(TSymbol{ "scope1", "name1" }, 1)));
	TVariateContext::GetInstance()->AddVariate(std::shared_ptr<TVariate>(new TInteger(TSymbol{ "scope1.child1", "name2" }, 2)));
	TVariateContext::GetInstance()->AddVariate(std::shared_ptr<TVariate>(new TInteger(TSymbol{ "scope2.child1", "name2" }, 3)));
}

void TVariateContextTests::TearDown()
{

}

TEST_F(TVariateContextTests, FindVariateScollUp_SuccessedFind)
{
	auto child1=TVariateContext::GetInstance()->GetVariateScollUp("scope1", "name1");
	ASSERT_TRUE(child1 != nullptr);
	ASSERT_TRUE(typeid(*child1) == typeid(TInteger));
	EXPECT_EQ(1, std::static_pointer_cast<TInteger>(child1)->GetValue());

	child1 = TVariateContext::GetInstance()->GetVariateScollUp("scope1.child1", "name1");
	ASSERT_TRUE(child1 != nullptr);
	ASSERT_TRUE(typeid(*child1) == typeid(TInteger));
	EXPECT_EQ(1, std::static_pointer_cast<TInteger>(child1)->GetValue());

	child1 = TVariateContext::GetInstance()->GetVariateScollUp("scope2.child1", "name1");
	ASSERT_TRUE(child1 == nullptr);

	auto child2 = TVariateContext::GetInstance()->GetVariateScollUp("scope1.child1", "name2");
	ASSERT_TRUE(child2 != nullptr);
	ASSERT_TRUE(typeid(*child2) == typeid(TInteger));
	EXPECT_EQ(2, std::static_pointer_cast<TInteger>(child2)->GetValue());

	auto child3 = TVariateContext::GetInstance()->GetVariateScollUp("scope2.child1", "name2");
	ASSERT_TRUE(child3 != nullptr);
	ASSERT_TRUE(typeid(*child3) == typeid(TInteger));
	EXPECT_EQ(3, std::static_pointer_cast<TInteger>(child3)->GetValue());
}

TEST_F(TVariateContextTests, GetAllVairatesFromScope_Successed)
{
	TVariateContext::GetInstance()->AddVariate(std::shared_ptr<TVariate>(new TInteger(TSymbol{ "scope2.child1", "name3" }, 3)));
	auto vec = TVariateContext::GetInstance()->GetAllVariateFromScope("scope1");
	EXPECT_EQ(1, vec.size());

	vec = TVariateContext::GetInstance()->GetAllVariateFromScope("scope2.child1");
	EXPECT_EQ(2, vec.size());
}