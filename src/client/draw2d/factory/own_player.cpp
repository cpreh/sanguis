#include <sanguis/client/draw2d/factory/own_player.hpp>
#include <sanguis/client/draw2d/entities/own_player.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>

sanguis::client::draw2d::entities::unique_ptr
sanguis::client::draw2d::factory::own_player(
	entities::model::parameters const &_param,
	draw2d::transform_callback const &_transform
)
{
	return
		entities::unique_ptr(
			fcppt::make_unique_ptr<
				entities::own_player
			>(
				fcppt::cref(
					_param
				),
				_transform
			)
		);
}
