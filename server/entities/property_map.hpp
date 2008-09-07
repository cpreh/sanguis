#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_MAP_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_MAP_HPP_INCLUDED

#include "property.hpp"
#include <map>

namespace sanguis
{
namespace server
{
namespace entities
{

typedef std::map<
	property::type::enum_type,
	property
> property_map;

}
}
}

#endif
