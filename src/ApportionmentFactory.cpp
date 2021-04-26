#include "ApportionmentFactory.hpp"
#include "Apportionment.hpp"
#include "methods.hpp"

#include <memory>

std::unique_ptr<Apportionment> 
    ApportionmentFactory::createApportionment(AppMethod appMethod) {
    
    switch (appMethod) {
		case Adams:             return std::make_unique<AdamsMethod>();
		case Dean:              return std::make_unique<DeanMethod>();
		case HuntingtonHill:    return std::make_unique<HuntingtonHillMethod>();
        case Webster:           return std::make_unique<WebsterMethod>();
        case Jefferson:         return std::make_unique<JeffersonMethod>();
		}
		throw "invalid apportionment method.";
}