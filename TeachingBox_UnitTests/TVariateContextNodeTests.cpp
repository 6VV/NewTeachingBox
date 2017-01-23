#include "TVariateContextNodeTests.h"
#include "..\TeachingBox\TVariateScopeNode.h"
#include <memory>
#include "..\TeachingBox\TInteger.h"


TEST_F(TVariateContextNodeTests, AddChild_NoException)
{
	TVariateScopeNode node;
	ASSERT_NO_THROW(node.AddChild(std::shared_ptr<TVariateScopeNode>(new TVariateScopeNode())));
}

TEST_F(TVariateContextNodeTests, AddVariate_NoException)
{
	TVariateScopeNode node;
	ASSERT_NO_THROW(node.AddOrUpdateVariate(std::shared_ptr<TVariate>(new TInteger())));
}

TEST_F(TVariateContextNodeTests, FindScope_Successed)
{
	std::shared_ptr<TVariateScopeNode> node1(new TVariateScopeNode("node1"));
	auto child1 = std::shared_ptr<TVariateScopeNode>(new TVariateScopeNode("child1"));
	auto child2 = std::shared_ptr<TVariateScopeNode>(new TVariateScopeNode("child2"));
	auto child3 = std::shared_ptr<TVariateScopeNode>(new TVariateScopeNode("child3"));

	node1->AddChild(child1);
	node1->AddChild(child2);
	child1->AddChild(child3);

	EXPECT_TRUE(node1->FindChildScope("child1")!=nullptr);
	EXPECT_TRUE(node1->FindChildScope("child2") != nullptr);
	EXPECT_TRUE(node1->FindChildScope("child3") != nullptr);
	EXPECT_TRUE(node1->FindChildScope("child4") == nullptr);

}

TEST_F(TVariateContextNodeTests, FindVariate_Successed)
{
	std::shared_ptr<TVariateScopeNode> node1(new TVariateScopeNode("node"));

	node1->AddOrUpdateVariate(std::make_shared<TInteger>(TSymbol{ "scope1", "name1" }));
	node1->AddOrUpdateVariate(std::make_shared<TInteger>(TSymbol{ "scope1", "name2" }));
	node1->AddOrUpdateVariate(std::make_shared<TInteger>(TSymbol{ "scope1", "name3" }));

	EXPECT_TRUE(node1->FindVariate("name1") != nullptr);
	EXPECT_TRUE(node1->FindVariate("name2") != nullptr);
	EXPECT_TRUE(node1->FindVariate("name3") != nullptr);
	EXPECT_TRUE(node1->FindVariate("name4") == nullptr);
}

TEST_F(TVariateContextNodeTests, GetParentNode_Successed)
{
	std::shared_ptr<TVariateScopeNode> node(new TVariateScopeNode("node"));
	std::shared_ptr<TVariateScopeNode> child(new TVariateScopeNode("child"));

	node->AddChild(child);

	EXPECT_TRUE(node->GetParentNode() == nullptr);
	EXPECT_TRUE(child->GetParentNode() == node.get());

}


TEST_F(TVariateContextNodeTests, DeleteVariate_Successed)
{
	std::shared_ptr<TVariateScopeNode> node1(new TVariateScopeNode("node"));

	node1->AddOrUpdateVariate(std::make_shared<TInteger>(TSymbol{ "node", "name1" }));
	node1->AddOrUpdateVariate(std::make_shared<TInteger>(TSymbol{ "node", "name2" }));

	node1->DeleteVariate("name1");
	EXPECT_TRUE(node1->FindVariate("name1") == nullptr);
}

TEST_F(TVariateContextNodeTests, GetAllVariates_Successed)
{
	std::shared_ptr<TVariateScopeNode> node1(new TVariateScopeNode("node"));

	node1->AddOrUpdateVariate(std::make_shared<TInteger>(TSymbol{ "node", "name1" }));
	node1->AddOrUpdateVariate(std::make_shared<TInteger>(TSymbol{ "node", "name2" }));

	auto vec = node1->GetAllVariates();
	ASSERT_EQ(2, vec.size());
}