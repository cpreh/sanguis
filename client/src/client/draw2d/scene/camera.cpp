#include <sanguis/client/slowed_duration.hpp>
#include <sanguis/client/control/attack_dest.hpp>
#include <sanguis/client/control/cursor_position.hpp>
#include <sanguis/client/control/optional_attack_dest.hpp>
#include <sanguis/client/draw2d/funit.hpp>
#include <sanguis/client/draw2d/optional_player_center.hpp>
#include <sanguis/client/draw2d/optional_translation.hpp>
#include <sanguis/client/draw2d/optional_vector2.hpp>
#include <sanguis/client/draw2d/player_center.hpp>
#include <sanguis/client/draw2d/translation.hpp>
#include <sanguis/client/draw2d/vector2.hpp>
#include <sanguis/client/draw2d/scene/background_dim.hpp>
#include <sanguis/client/draw2d/scene/camera.hpp>
#include <sanguis/client/draw2d/scene/translation.hpp>
#include <sanguis/client/draw2d/translate/vector_from_client.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/cast/float_to_int_fun.hpp>
#include <fcppt/cast/int_to_float_fun.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe.hpp>


sanguis::client::draw2d::scene::camera::camera(
	sge::renderer::device::core_ref const _renderer
)
:
	renderer_(
		_renderer
	),
	desired_translation_(),
	translation_()
{
}

sanguis::client::draw2d::scene::camera::~camera()
= default;

void
sanguis::client::draw2d::scene::camera::update(
	sanguis::client::slowed_duration const _duration,
	sanguis::client::draw2d::optional_player_center const &_opt_player_center
)
{
	desired_translation_ =
		fcppt::optional::map(
			_opt_player_center,
			[
				this
			](
				sanguis::client::draw2d::player_center const &_player_center
			)
			{
				return
					sanguis::client::draw2d::scene::translation(
						_player_center,
						sanguis::client::draw2d::scene::background_dim(
							renderer_.get()
						)
					);
			}
		);

	translation_ =
		fcppt::optional::map(
			desired_translation_,
			[
				this,
				_duration
			](
				sanguis::client::draw2d::translation const &_desired_translation
			)
			{
				return
					fcppt::optional::maybe(
						translation_,
						[
							_desired_translation
						]{
							return
								fcppt::math::vector::structure_cast<
									sanguis::client::draw2d::vector2,
									fcppt::cast::int_to_float_fun
								>(
									_desired_translation.get()
								);
						},
						[
							_desired_translation,
							_duration
						](
							sanguis::client::draw2d::vector2 const &_translation
						)
						{
							return
								_translation
								+
								(
									fcppt::math::vector::structure_cast<
										sanguis::client::draw2d::vector2,
										fcppt::cast::int_to_float_fun
									>(
										_desired_translation.get()
									)
									-
									_translation
								)
								*
								fcppt::literal<
									sanguis::client::draw2d::funit
								>(
									10.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
								)
								*
								_duration.get().count();
						}
					);
			}
		);
}

void
sanguis::client::draw2d::scene::camera::reset_translation()
{
	desired_translation_ =
		sanguis::client::draw2d::optional_translation();

	translation_ =
		sanguis::client::draw2d::optional_vector2();
}

sanguis::client::draw2d::optional_translation
sanguis::client::draw2d::scene::camera::translation() const
{
	return
		fcppt::optional::map(
			translation_,
			[](
				sanguis::client::draw2d::vector2 const &_translation
			)
			{
				return
					sanguis::client::draw2d::translation{
						fcppt::math::vector::structure_cast<
							sanguis::client::draw2d::translation::value_type,
							fcppt::cast::float_to_int_fun
						>(
							_translation
						)
					};
			}
		);
}

sanguis::client::control::optional_attack_dest
sanguis::client::draw2d::scene::camera::translate_attack_dest(
	sanguis::client::control::cursor_position const &_cursor_position
) const
{
	return
		fcppt::optional::map(
			this->translation(),
			[
				_cursor_position
			](
				sanguis::client::draw2d::translation const &_translation
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
