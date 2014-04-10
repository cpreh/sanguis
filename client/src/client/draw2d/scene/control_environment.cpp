#include <sanguis/client/control/cursor_position.hpp>
#include <sanguis/client/control/environment.hpp>
#include <sanguis/client/control/optional_attack_dest.hpp>
#include <sanguis/client/control/optional_cursor_position.hpp>
#include <sanguis/client/draw2d/optional_translation.hpp>
#include <sanguis/client/draw2d/vector2.hpp>
#include <sanguis/client/draw2d/scene/control_environment.hpp>
#include <sanguis/client/draw2d/scene/object.hpp>
#include <sanguis/client/draw2d/translate/vector_from_client.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


sanguis::client::draw2d::scene::control_environment::control_environment(
	sanguis::client::draw2d::scene::object &_object
)
:
	sanguis::client::control::environment(),
	object_(
		_object
	),
	position_()
{
}

sanguis::client::draw2d::scene::control_environment::~control_environment()
{
}

sanguis::client::control::optional_attack_dest const
sanguis::client::draw2d::scene::control_environment::translate_attack_dest(
	sanguis::client::control::cursor_position const &_cursor_position
) const
{
	sanguis::client::draw2d::optional_translation const translation(
		object_.translation()
	);

	return
		translation
		?
			sanguis::client::control::optional_attack_dest(
				sanguis::client::draw2d::translate::vector_from_client(
					fcppt::math::vector::structure_cast<
						sanguis::client::draw2d::vector2
					>(
						-
						translation->get()
						+
						_cursor_position
					)
				)
			)
		:
			sanguis::client::control::optional_attack_dest()
		;
}

sanguis::client::control::optional_cursor_position const
sanguis::client::draw2d::scene::control_environment::position() const
{
	return
		position_;
}

void
sanguis::client::draw2d::scene::control_environment::update_position(
	sanguis::client::control::optional_cursor_position const &_position
)
{
	position_ =
		_position;
}
