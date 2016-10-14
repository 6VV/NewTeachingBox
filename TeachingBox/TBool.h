#ifndef _TEACHING_BOX_TBOOL_H_
#define _TEACHING_BOX_TBOOL_H_

#include "TVariate.h"
#include "QString"

class TBool:public TVariate
{
	Q_OBJECT

public:
	const static QString STR_VALUE_TRUE;
	const static QString STR_VALUE_FALSE;

public:
	TBool(const QString& scope, const QString& name, const bool value=false);
	TBool(const TBool& variate);
	TBool(QDataStream& dataStream);

	virtual TVariate* Clone() const override;

	const bool GetValue() const;
	void SetValue(const bool value);


protected:
	virtual void ReadValueStream(QDataStream& dataStream) const override;
	virtual void UpdateFromValue(const TVariate& variate) override;


private:
	void Init();

private:
	bool m_value;
};

#endif