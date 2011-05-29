#include "clamp_pos.hpp"
#include <fcppt/math/dim/basic_impl.hpp>
#include <algorithm>

sanguis::client::draw2d::scene::world::batch_grid::dim const
sanguis::client::draw2d::scene::world::clamp_pos(
	batch_grid::dim const &_pos,
	batch_grid::dim const &_size
)
{
	return
		batch_grid::dim(
			std::min(
				_pos.w(),
				_size.w()
			),
			std::min(
				_pos.h(),
				_size.h()
			)
		);
}
