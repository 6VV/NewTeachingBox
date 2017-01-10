#ifndef _TVARIATE_FACTORY_H_
#define _TVARIATE_FACTORY_H_

#include <memory>
#include <map>

class TVariate;
class TSymbol;

class TVariateFactory
{
public:
	typedef std::shared_ptr<TVariate>(*FunCreateVariate)(const TSymbol& symbol);

public:
	static std::shared_ptr<TVariate> GetVariate(QByteArray& dataBytes);
	static FunCreateVariate GetFun(const QString& type);
	static std::shared_ptr<TVariate> CreateVariate(const TSymbol& symbol);

	static void Register(const QString& type, FunCreateVariate fun);

private:
	static std::map<QString, FunCreateVariate>& FunMapCreateVariate();
};

#endif