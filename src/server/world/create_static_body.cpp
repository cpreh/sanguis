#include "create_static_body.hpp"
#include <sge/projectile/body/object.hpp>

sge::projectile::body::object_unique_ptr
sanguis::server::world::create_static_body(
	sanguis::creator::geometry::shape_container const &_shapes
)
{
#if 0
	for(
		sanguis::projectile::geometry::shape_container::const_iterator shape_it(
			_shapes.begin()
		);
		shape_it != _shapes.end();
		++shape_it
	)
	{
		if(
			shape_it->solidity()
			!=
			sanguis::creator::geometry::solidity::solid
		)
			continue;

		sanguis::creator::geometry::polygon const &poly(
			shape_it->polygon()
		);

		
	}
#endif
}
