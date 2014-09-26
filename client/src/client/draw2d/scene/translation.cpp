#include <sanguis/client/draw2d/player_center.hpp>
#include <sanguis/client/draw2d/translation.hpp>
#include <sanguis/client/draw2d/scene/translation.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/arithmetic.hpp>


sanguis::client::draw2d::translation const
sanguis::client::draw2d::scene::translation(
	sanguis::client::draw2d::player_center const _player_center,
	sge::renderer::screen_size const _screen_size
)
{
	return
		sanguis::client::draw2d::translation(
			-
			_player_center.get().get()
			+
			fcppt::math::dim::structure_cast<
				sanguis::client::draw2d::player_center::value_type::value_type
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
}
