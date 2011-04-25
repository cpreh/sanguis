#include "own_player.hpp"

sanguis::client::draw2d::entities::own_player::own_player(
	model::parameters const &_param,
	draw2d::transform_callback const &_transform
)
:
	player(
		_param
	),
	transform_(_transform)
{
}

sanguis::client::draw2d::entities::own_player::~own_player()
{
}

void
sanguis::client::draw2d::entities::own_player::update(
	sanguis::time_delta const &_time
)
{
	player::update(
		_time
	);

	transform_(
		this->center()
	);
}
