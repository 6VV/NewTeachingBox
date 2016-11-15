#ifndef _TEACHING_BOX_TSTRING_H_
#define _TEACHING_BOX_TSTRING_H_

#include "TVariate.h"

class TString:public TVariate
{
	Q_OBJECT

public:
	TString(const QString& scope, const QString& name, const QString& value="");
	TString(const TString& variate);
	TString(QDataStream& dataStream);

	virtual TVariate* Clone() const override;

	const QString& GetValue() const;
	void SetValue(const QString& value);


protected:
	virtual void WriteValueToStream(QDataStream& dataStream) const override;
	virtual void UpdateFromValue(const TVariate& variate) override;

private:
	void  Init();

private:
	QString m_value;
};

#endif