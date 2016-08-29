#ifndef _TEACHING_BOX_EXCEPTION_H_
#define _TEACHING_BOX_EXCEPTION_H_

#include "QString"

class Exception
{
public:
	Exception(const QString& info);
	
	QString GetInfo();

private:
	QString m_info;
};

#endif