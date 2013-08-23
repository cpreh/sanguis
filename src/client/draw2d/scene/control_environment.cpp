#include <sanguis/client/control/attack_dest.hpp>
#include <sanguis/client/control/cursor_position.hpp>
#include <sanguis/client/draw2d/vector2.hpp>
#include <sanguis/client/draw2d/scene/control_environment.hpp>
#include <sanguis/client/draw2d/scene/object.hpp>
#include <sanguis/client/draw2d/sprite/point.hpp>
#include <sanguis/client/draw2d/translate/vector_from_client.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


sanguis::client::draw2d::scene::control_environment::control_environment(
	sanguis::client::draw2d::scene::object &_object
)
:
	object_(
		_object
	)
{
}

sanguis::client::draw2d::scene::control_environment::~control_environment()
{
}

sanguis::client::control::attack_dest const
sanguis::client::draw2d::scene::control_environment::translate_attack_dest(
	sanguis::client::control::cursor_position const &_cursor_position
) const
{
	return
		sanguis::client::draw2d::translate::vector_from_client(
			fcppt::math::vector::structure_cast<
				sanguis::client::draw2d::vector2
			>(
				-
				fcppt::math::dim::structure_cast<
					sanguis::client::draw2d::sprite::point
				>(
					object_.screen_size()
					/
					fcppt::literal<
						sge::renderer::screen_unit
					>(
						2u
					)
				)
				+ object_.player_center().get()
				+ _cursor_position
			)
		);
}
