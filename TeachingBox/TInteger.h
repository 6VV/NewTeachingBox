#ifndef _TEACHING_BOX_TINTEGER_H_
#define _TEACHING_BOX_TINTEGER_H_

#include "TVariate.h"

class TInteger:public TVariate
{
	Q_OBJECT

public:
	TInteger(const QString& scope, const QString& name,const int value);
	TInteger(const TInteger& variate);
	TInteger(QDataStream& dataStream);

	virtual TVariate* Clone() const override;

	int GetValue();
	void SetValue(const int value);

protected:
	virtual void ReadValueStream(QDataStream& dataStream) const override;
	virtual void UpdateFromValue(const TVariate& variate) override;

private:
	void Init();

private:
	int m_value;
};

#endif