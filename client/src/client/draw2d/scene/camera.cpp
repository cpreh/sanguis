#include <sanguis/client/slowed_duration.hpp>
#include <sanguis/client/control/attack_dest.hpp>
#include <sanguis/client/control/cursor_position.hpp>
#include <sanguis/client/control/optional_attack_dest.hpp>
#include <sanguis/client/draw2d/optional_player_center.hpp>
#include <sanguis/client/draw2d/optional_translation.hpp>
#include <sanguis/client/draw2d/player_center.hpp>
#include <sanguis/client/draw2d/translation.hpp>
#include <sanguis/client/draw2d/vector2.hpp>
#include <sanguis/client/draw2d/scene/background_dim.hpp>
#include <sanguis/client/draw2d/scene/camera.hpp>
#include <sanguis/client/draw2d/scene/translation.hpp>
#include <sanguis/client/draw2d/translate/vector_from_client.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <fcppt/optional_bind_construct.hpp>
#include <fcppt/cast/int_to_float_fun.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


sanguis::client::draw2d::scene::camera::camera(
	sge::renderer::device::core &_renderer
)
:
	translation_(),
	renderer_(
		_renderer
	)
{
}

sanguis::client::draw2d::scene::camera::~camera()
{
}

void
sanguis::client::draw2d::scene::camera::update(
	sanguis::client::slowed_duration, //const _duration
	sanguis::client::draw2d::optional_player_center const _opt_player_center
)
{
	translation_ =
		fcppt::optional_bind_construct(
			_opt_player_center,
			[
				this
			](
				sanguis::client::draw2d::player_center const _player_center
			)
			{
				return
					sanguis::client::draw2d::scene::translation(
						_player_center,
						sanguis::client::draw2d::scene::background_dim(
							renderer_
						)
					);
			}
		);
}

sanguis::client::draw2d::optional_translation const
sanguis::client::draw2d::scene::camera::translation() const
{
	return
		translation_;
}

sanguis::client::control::optional_attack_dest const
sanguis::client::draw2d::scene::camera::translate_attack_dest(
	sanguis::client::control::cursor_position const _cursor_position
)
{
	return
		fcppt::optional_bind_construct(
			translation_,
			[
				_cursor_position
			](
				sanguis::client::draw2d::translation const _translation
			)
			{
				return
					sanguis::client::control::attack_dest{
						sanguis::client::draw2d::translate::vector_from_client(
							fcppt::math::vector::structure_cast<
								sanguis::client::draw2d::vector2,
								fcppt::cast::int_to_float_fun
							>(
								-
								_translation.get()
								+
								_cursor_position
							)
						)
					};
			}
		);
}
