#include "own_player.hpp"
#include "../entities/own_player.hpp"

sanguis::client::draw2d::entities::auto_ptr
sanguis::client::draw2d::factory::own_player(
	entities::model::parameters const &param_,
	transform_callback const &transform_
)
{
	return entities::auto_ptr(
		new entities::own_player(
			param_,
			transform_
		)
	);
}
