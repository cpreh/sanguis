#include "own_player.hpp"
#include "../entities/own_player.hpp"
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
				_param,
				_transform
			)
		);
}
