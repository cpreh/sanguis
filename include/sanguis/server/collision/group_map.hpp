#ifndef SANGUIS_SERVER_COLLISION_GROUP_MAP_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_GROUP_MAP_HPP_INCLUDED

#include <sanguis/server/collision/group.hpp>
#include <sge/projectile/group/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

typedef boost::ptr_map<
	collision::group::type,
	sge::projectile::group::object
> group_map;

}
}
}

#endif