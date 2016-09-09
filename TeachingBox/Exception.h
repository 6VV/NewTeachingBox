#ifndef _TEACHING_BOX_EXCEPTION_H_
#define _TEACHING_BOX_EXCEPTION_H_

#include "QString"

class Exception
{
public:
	Exception();
	Exception(const QString& info);
	virtual ~Exception(){};
	
	virtual QString GetInfo();

private:
	QString m_info;
};

#endif