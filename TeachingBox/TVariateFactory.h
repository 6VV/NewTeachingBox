#ifndef _TVARIATE_FACTORY_H_
#define _TVARIATE_FACTORY_H_

#include <memory>

class TVariate;

class TVariateFactory
{
public:
	static TVariate* CreateVariate(QByteArray& dataBytes);
	static std::shared_ptr<TVariate> GetVariate(QByteArray& dataBytes);
};

#endif