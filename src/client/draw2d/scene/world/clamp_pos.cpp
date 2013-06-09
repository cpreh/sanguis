#include <sanguis/client/draw2d/scene/world/clamp_pos.hpp>
#include <sanguis/client/draw2d/scene/world/signed_pos.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/size.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/math/clamp.hpp>


sanguis::creator::pos const
sanguis::client::draw2d::scene::world::clamp_pos(
	sanguis::client::draw2d::scene::world::signed_pos const &_pos,
	sanguis::creator::size const &_size
)
{
	FCPPT_ASSERT_PRE(
		_size.content()
		!=
		0u
	);

	sanguis::creator::pos ret{
		fcppt::no_init()
	};

	for(
		sanguis::creator::size::dim_wrapper::value_type index(
			0u
		);
		index < sanguis::creator::size::dim_wrapper::value;
		++index
	)
		ret[
			index
		] =
			static_cast<
				sanguis::creator::pos::value_type
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
				)
			);

	return ret;
}
