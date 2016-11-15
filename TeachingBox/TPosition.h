#ifndef _TEACHING_BOX_TPOSITION_H_
#define _TEACHING_BOX_TPOSITION_H_

#include "TVariate.h"
#include "QVector"
#include "DataStruct.h"

class TPosition:public TVariate
{
	Q_OBJECT

public:
	TPosition(const QString& scope, const QString& name, const tAxesAllPositions& value = tAxesAllPositions{});
	TPosition(const TPosition& variate);
	TPosition(QDataStream& dataStream);

	virtual TVariate* Clone() const override;

	const tAxesAllPositions GetValue() const;

	void SetValue(const tAxesAllPositions& value);


private:
	virtual void WriteValueToStream(QDataStream& dataStream) const override;

	virtual void UpdateFromValue(const TVariate& variate) override;

private:
	void Init();

private:
	tAxesAllPositions m_value;
};

#endif