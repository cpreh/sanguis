#include "own_player.hpp"

sanguis::client::draw2d::entities::own_player::own_player(
	model::parameters const &_param,
	transform_callback const &_transform
)
:
	player(
		_param
	),
	transform_(_transform)
{}

void
sanguis::client::draw2d::entities::own_player::update(
	time_type const _time
)
{
	player::update(
		_time
	);

	transform_(
		center()
	);
}
