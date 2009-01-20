#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_MAP_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_MAP_HPP_INCLUDED

#include "property_type.hpp"
#include <map>

namespace sanguis
{
namespace server
{
namespace entities
{

class property;

typedef std::map<
	property_type::type,
	property
> property_map;

}
}
}

#endif
