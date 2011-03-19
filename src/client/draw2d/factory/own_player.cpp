#include "own_player.hpp"
#include "../entities/own_player.hpp"

sanguis::client::draw2d::entities::auto_ptr
sanguis::client::draw2d::factory::own_player(
	entities::model::parameters const &_param,
	transform_callback const &_transform
)
{
	return
		entities::auto_ptr(
			new entities::own_player(
				_param,
				_transform
			)
		);
}
