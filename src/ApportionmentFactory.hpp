#ifndef APPORTIONMENT_FACTORY_HPP
#define APPORTIONMENT_FACTORY_HPP

#include "Apportionment.hpp"
#include "methods.hpp"

#include <memory>

class ApportionmentFactory {
public:
	enum AppMethod {
		Adams,
		Dean,
		HuntingtonHill,
        Webster,
        Jefferson
	};

	static std::unique_ptr<Apportionment> 
        createApportionment(AppMethod appmethod);
};   

#endif