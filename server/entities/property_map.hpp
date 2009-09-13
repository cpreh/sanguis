#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_MAP_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_MAP_HPP_INCLUDED

#include "property_fwd.hpp"
#include "property_type.hpp"
#include <sge/container/map_fwd.hpp>
#include <map>

namespace sanguis
{
namespace server
{
namespace entities
{
typedef sge::container::map<
	std::map<
		property_type::type,
		property
	>
> property_map;

}
}
}

#endif
