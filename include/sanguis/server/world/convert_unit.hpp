#ifndef SANGUIS_SERVER_WORLD_CONVERT_UNIT_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_CONVERT_UNIT_HPP_INCLUDED

#include <sanguis/pixels_per_meter.hpp>
#include <sanguis/creator/size_type.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <sge/projectile/scalar.hpp>
#include <fcppt/cast/int_to_float.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

inline
sge::projectile::scalar
convert_unit(
	sanguis::creator::size_type const &_value
)
{
	return
		fcppt::cast::int_to_float<
			sge::projectile::scalar
		>(
			_value
			*
			sanguis::creator::tile_size::value
		)
		/
		fcppt::cast::int_to_float<
			sge::projectile::scalar
		>(
			sanguis::pixels_per_meter()
		)
		;
}

}
}
}

#endif
