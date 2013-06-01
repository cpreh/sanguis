#include <sanguis/client/draw2d/scene/world/ceil_div_signed_pos.hpp>
#include <sanguis/client/draw2d/scene/world/signed_pos.hpp>
#include <sanguis/client/draw2d/scene/world/signed_unit.hpp>
#include <fcppt/math/ceil_div_signed.hpp>
#include <fcppt/math/map.hpp>


sanguis::client::draw2d::scene::world::signed_pos const
sanguis::client::draw2d::scene::world::ceil_div_signed_pos(
	sanguis::client::draw2d::scene::world::signed_pos const &_pos,
	sanguis::client::draw2d::scene::world::signed_unit const _factor
)
{
	return
		fcppt::math::map<
			sanguis::client::draw2d::scene::world::signed_pos
		>(
			_pos,
			[
				_factor
			](
				sanguis::client::draw2d::scene::world::signed_pos::value_type const _value
			)
			{
				return
					fcppt::math::ceil_div_signed(
						_value,
						_factor
					);
			}
		);

}
