#ifndef _TEACHING_BOX_TDOUBLE_H_
#define _TEACHING_BOX_TDOUBLE_H_

#include "TVariate.h"

class TDouble:public TVariate
{
	Q_OBJECT

public:
	TDouble(const QString& scope, const QString& name, const double value=0);
	TDouble(const TDouble& variate);
	TDouble(QDataStream& dataStream);

	virtual TVariate* Clone() const override;

	double GetValue();
	void SetValue(const double value);

protected:
	virtual void ReadValueStream(QDataStream& dataStream) const override;
	virtual void UpdateFromValue(const TVariate& variate) override;


private:
	void Init();

private:
	double m_value;
};

#endif