#include "TRefSysTests.h"
#include <QTreeWidget>
#include <QSqlDatabase>
#include "..\TeachingBox\TRefSys.h"
#include "QDataStream"
#include "QByteArray"

void TRefSysTests::SetUp()
{
	m_refSys = new TRefSys("scope", "name",
		TRefSys::ValueType{ 
		TRefSys::BaseSysType{ "baseName"}, 
		TRefSys::OffsetType{ { 1, 2, 3, 4, 5, 6 } }});
}

void TRefSysTests::TearDown()
{
	delete m_refSys;
}

void TRefSysTests::TestEqual(TRefSys* sys1, TRefSys* sys2)
{
	EXPECT_STREQ(sys2->GetName().toStdString().c_str(), sys1->GetName().toStdString().c_str());
	EXPECT_STREQ(sys2->GetScope().toStdString().c_str(), sys1->GetScope().toStdString().c_str());
	EXPECT_EQ(sys2->GetType(), sys1->GetType());

	auto sourceValue = sys2->GetValue();
	auto cloneValue = sys1->GetValue();

	EXPECT_TRUE(sourceValue.offset == cloneValue.offset);
	EXPECT_TRUE(sourceValue.baseSys == cloneValue.baseSys);
}

TEST_F(TRefSysTests, Equal_When_Clone)
{
	auto clone = static_cast<TRefSys*>(m_refSys->Clone());
	
	TestEqual(m_refSys, clone);
}

TEST_F(TRefSysTests, Equal_When_Read_Write_DataStream)
{
	QByteArray array;
	QDataStream dataStream(&array, QIODevice::ReadWrite);
	m_refSys->WriteDataToStream(dataStream);

	dataStream.device()->seek(0);
	TRefSys sys(dataStream);

	TestEqual(m_refSys, &sys);
}