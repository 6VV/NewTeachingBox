#ifndef _TVARIATE_FACTORY_H_
#define _TVARIATE_FACTORY_H_

class TVariate;

class TVariateFactory
{
public:
	static TVariate* CreateVariate(QByteArray& dataBytes);
};

#endif