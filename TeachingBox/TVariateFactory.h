#ifndef _TVARIATE_FACTORY_H_
#define _TVARIATE_FACTORY_H_

#include <memory>

class TVariate;
class TSymbol;

class TVariateFactory
{
public:
	static std::shared_ptr<TVariate> GetVariate(QByteArray& dataBytes);
	static std::shared_ptr<TVariate> CreateVariate(const TSymbol& symbol);
};

#endif