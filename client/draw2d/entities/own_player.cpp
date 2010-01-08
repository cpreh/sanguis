#include "own_player.hpp"

sanguis::client::draw2d::entities::own_player::own_player(
	model::parameters const &param_,
	transform_callback const &transform_
)
:
	player(
		param_
	),
	transform_(transform_)
{}

void
sanguis::client::draw2d::entities::own_player::update(
	time_type const time_
)
{
	player::update(
		time_
	);

	transform_(
		center()
	);
}
