#include "envelope.hpp"
#include <sanguis/creator/geometry/rect.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/box/extend_bounding_box.hpp>

sanguis::creator::geometry::rect const
sanguis::client::draw2d::scene::world::envelope(
	sanguis::creator::geometry::polygon const &_poly
)
{
	sanguis::creator::geometry::rect ret(
		sanguis::creator::geometry::rect::null()
	);

	for(
		sanguis::creator::geometry::polygon::const_iterator vertex_it(
			_poly.begin()
		);
		vertex_it != _poly.end();
		++vertex_it
	)
		ret =
			fcppt::math::box::extend_bounding_box(
				ret,
				vertex_it->pos()
			);

	return ret;
}
