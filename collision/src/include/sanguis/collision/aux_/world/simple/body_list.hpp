#ifndef SANGUIS_COLLISION_AUX__WORLD_SIMPLE_BODY_LIST_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX__WORLD_SIMPLE_BODY_LIST_HPP_INCLUDED

#include <sanguis/collision/aux_/world/simple/body_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/intrusive/list.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace collision
{
namespace aux_
{
namespace world
{
namespace simple
{

typedef
boost::intrusive::list<
	sanguis::collision::aux_::world::simple::body,
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
