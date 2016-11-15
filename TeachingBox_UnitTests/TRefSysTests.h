#ifndef _T_REF_SYS_TESTS_H_
#define _T_REF_SYS_TESTS_H_

#include <gtest\gtest.h>

class TRefSys;

class TRefSysTests:public testing::Test
{
public:
	virtual void SetUp() override;
	virtual void TearDown() override;

protected:
	void TestEqual(TRefSys* sys1, TRefSys* sys2);

protected:
	TRefSys* m_refSys = nullptr;
};

#endif