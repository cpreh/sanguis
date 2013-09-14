#ifndef SANGUIS_COLLISION_AUX__WORLD_PROJECTILE_TO_SGE_USER_DATA_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX__WORLD_PROJECTILE_TO_SGE_USER_DATA_HPP_INCLUDED

#include <sanguis/collision/world/body_base_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/any.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace collision
{
namespace aux_
{
namespace world
{
namespace projectile
{

boost::any const
to_sge_user_data(
	sanguis::collision::world::body_base &
);

}
}
}
}
}

#endif
