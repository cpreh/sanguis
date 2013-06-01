#include <sanguis/client/draw2d/center.hpp>
#include <sanguis/client/draw2d/collide_callback.hpp>
#include <sanguis/client/draw2d/dim2.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/speed_is_null.hpp>
#include <sanguis/client/draw2d/transform_callback.hpp>
#include <sanguis/client/draw2d/entities/own_player.hpp>
#include <sanguis/client/draw2d/entities/player.hpp>
#include <sanguis/client/draw2d/entities/model/parameters_fwd.hpp>


sanguis::client::draw2d::entities::own_player::own_player(
	sanguis::client::draw2d::entities::model::parameters const &_param,
	sanguis::client::draw2d::transform_callback const &_transform,
	sanguis::client::draw2d::collide_callback const &_collide
)
:
	sanguis::client::draw2d::entities::player(
		_param
	),
	transform_(
		_transform
	),
	collide_(
		_collide
	)
{
}

sanguis::client::draw2d::entities::own_player::~own_player()
{
}

void
sanguis::client::draw2d::entities::own_player::update()
{
	if(
		!sanguis::client::draw2d::speed_is_null(
			this->speed()
		)
		&&
		collide_(
			this->center(),
			this->bounding_dim()
		)
	)
		this->speed(
			sanguis::client::draw2d::speed(
				sanguis::client::draw2d::speed::value_type::null()
			)
		);

	sanguis::client::draw2d::entities::player::update();

	transform_(
		this->center()
	);
}
