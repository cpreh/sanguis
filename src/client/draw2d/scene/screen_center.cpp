#include <sanguis/client/draw2d/vector2.hpp>
#include <sanguis/client/draw2d/scene/screen_center.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/static.hpp>
#include <fcppt/math/dim/structure_cast.hpp>


sanguis::client::draw2d::vector2 const
sanguis::client::draw2d::scene::screen_center(
	sanguis::client::draw2d::sprite::center const _player_center,
	sge::renderer::screen_size const _screen_size
)
{
	sanguis::client::draw2d::sprite::point const translation_center(
		-_player_center.get()
		+
		fcppt::math::dim::structure_cast<
			fcppt::math::dim::static_<
				sanguis::client::draw2d::sprite::unit,
				2
			>
		>(
			_screen_size
			/
			fcppt::literal<
				sge::renderer::screen_unit
			>(
				2u
			)
		)
	);

	return
		fcppt::math::vector::structure_cast<
			sanguis::client::draw2d::vector2
		>(
			translation_center
		);
}
