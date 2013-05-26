#ifndef SANGUIS_SERVER_WORLD_CONVERT_UNIT_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_CONVERT_UNIT_HPP_INCLUDED

#include <sanguis/pixels_per_meter.hpp>
#include <sanguis/creator/size_type.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <sge/projectile/scalar.hpp>


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
		static_cast<
			sge::projectile::scalar
		>(
			_value
			*
			sanguis::creator::tile_size::value
		)
		/
		static_cast<
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
