#ifndef SANGUIS_SERVER_WORLD_CONVERT_POS_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_CONVERT_POS_HPP_INCLUDED

#include <sanguis/server/world/convert_unit.hpp>
#include <sanguis/creator/pos.hpp>
#include <sge/projectile/vector2.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

inline
sge::projectile::vector2 const
convert_pos(
	sanguis::creator::pos const &_pos
)
{
	return
		sge::projectile::vector2(
			sanguis::server::world::convert_unit(
				_pos.w()
			),
			sanguis::server::world::convert_unit(
				_pos.h()
			)
		);
}

}
}
}

#endif
