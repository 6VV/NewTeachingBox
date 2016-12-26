#ifndef _TVARIATE_FACTORY_H_
#define _TVARIATE_FACTORY_H_

#include <memory>
#include <map>

class TVariate;
class TSymbol;

class TVariateFactory
{
public:
	//typedef std::shared_ptr<TVariate>(*FunGetVariate)(QDataStream& dataStream);
	typedef std::shared_ptr<TVariate>(*FunCreateVariate)(const TSymbol& symbol);


public:
	static std::shared_ptr<TVariate> GetVariate(QByteArray& dataBytes);
	static std::shared_ptr<TVariate> CreateVariate(const TSymbol& symbol);

	//static std::map<QString, FunGetVariate>& FunMapGetVariate();
	static std::map<QString, FunCreateVariate>& FunMapCreateVariate();

};

#endif