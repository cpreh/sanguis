#ifndef SANGUIS_COLLISION_IMPL_WORLD_SIMPLE_BODY_LIST_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_WORLD_SIMPLE_BODY_LIST_HPP_INCLUDED

#include <sanguis/collision/impl/world/simple/body_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/intrusive/list.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace collision
{
namespace impl
{
namespace world
{
namespace simple
{

typedef
boost::intrusive::list<
	sanguis::collision::impl::world::simple::body,
	boost::intrusive::constant_time_size<
		false
	>
>
body_list;

}
}
}
}
}

#endif
