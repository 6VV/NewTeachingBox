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
	ASSERT_NO_THROW(node.AddVariate(std::shared_ptr<TVariate>(new TInteger())));
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

	EXPECT_TRUE(node1->FindScope("child1")!=nullptr);
	EXPECT_TRUE(node1->FindScope("child2") != nullptr);
	EXPECT_TRUE(node1->FindScope("child3") != nullptr);
	EXPECT_TRUE(node1->FindScope("child4") == nullptr);

}