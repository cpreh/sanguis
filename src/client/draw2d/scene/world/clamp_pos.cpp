#include <sanguis/client/draw2d/scene/world/batch_grid.hpp>
#include <sanguis/client/draw2d/scene/world/clamp_pos.hpp>
#include <sanguis/client/draw2d/scene/world/signed_pos.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/container/grid/size_type.hpp>
#include <fcppt/math/clamp.hpp>


sanguis::client::draw2d::scene::world::batch_grid::dim const
sanguis::client::draw2d::scene::world::clamp_pos(
	sanguis::client::draw2d::scene::world::signed_pos const &_pos,
	sanguis::client::draw2d::scene::world::batch_grid::dim const &_size
)
{
	FCPPT_ASSERT_PRE(
		_size.content()
		!=
		0u
	);

	sanguis::client::draw2d::scene::world::batch_grid::dim ret{
		fcppt::no_init()
	};

	for(
		fcppt::container::grid::size_type index(
			0u
		);
		index < sanguis::client::draw2d::scene::world::batch_grid::dim::dim_wrapper::value;
		++index
	)
		ret[
			index
		] =
			static_cast<
				sanguis::client::draw2d::scene::world::batch_grid::dim::value_type
			>(
				fcppt::math::clamp(
					_pos[
						index
					],
					static_cast<
						sanguis::client::draw2d::scene::world::signed_pos::value_type
					>(
						0
					),
					static_cast<
						sanguis::client::draw2d::scene::world::signed_pos::value_type
					>(
						_size[
							index
						]
					)
					- 1
				)
			);

	return ret;
}
