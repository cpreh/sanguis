#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_MAP_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_MAP_HPP_INCLUDED

#include "property.hpp"
#include <boost/ptr_container/ptr_map.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

typedef boost::ptr_map<
	property::type::enum_type,
	property
> property_map;

}
}
}

#endif
