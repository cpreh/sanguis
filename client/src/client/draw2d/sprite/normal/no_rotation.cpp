#include <sanguis/client/draw2d/sprite/float_unit.hpp>
#include <sanguis/client/draw2d/sprite/normal/no_rotation.hpp>
#include <fcppt/literal.hpp>


sanguis::client::draw2d::sprite::float_unit
sanguis::client::draw2d::sprite::normal::no_rotation()
{
	return
		fcppt::literal<
			sanguis::client::draw2d::sprite::float_unit
		>(
			0
		);
}
