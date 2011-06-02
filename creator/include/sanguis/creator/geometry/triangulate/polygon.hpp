#ifndef SANGUIS_CREATOR_GEOMETRY_TRIANGULATE_POLYGON_HPP_INCLUDED
#define SANGUIS_CREATOR_GEOMETRY_TRIANGULATE_POLYGON_HPP_INCLUDED

#include <sanguis/creator/geometry/triangulate/transform_function.hpp>
#include <sanguis/creator/geometry/polygon.hpp>
#include <sge/projectile/triangulation/triangulate.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/transform.hpp>
#include <vector>

namespace sanguis
{
namespace creator
{
namespace geometry
{
namespace triangulate
{

template<
	typename ResultContainer
>
ResultContainer const
polygon(
	sanguis::creator::geometry::polygon const &_poly,
	typename triangulate::transform_function<
		ResultContainer
	>::type const &_transform
)
{
	typedef typename ResultContainer::value_type::value_type point_type;

	std::vector<
		point_type
	> converted;

	converted.reserve(
		_poly.size()
	);

	for(
		sanguis::creator::geometry::polygon::const_iterator poly_it(
			_poly.begin()
		);
		poly_it != _poly.end();
		++poly_it
	)
		converted.push_back(
			fcppt::math::vector::transform(
				fcppt::math::vector::structure_cast<
					point_type
				>(
					poly_it->pos()
				),
				_transform
			)
		);

	return
		sge::projectile::triangulation::triangulate<
			ResultContainer
		>(
			converted,
			_transform(
				1
			) // TODO!
		);
}

}
}
}
}

#endif
