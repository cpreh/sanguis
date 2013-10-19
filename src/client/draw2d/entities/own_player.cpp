#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/client/draw2d/collide_callback.hpp>
#include <sanguis/client/draw2d/collide_parameters.hpp>
#include <sanguis/client/draw2d/dim2.hpp>
#include <sanguis/client/draw2d/optional_speed.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/transform_callback.hpp>
#include <sanguis/client/draw2d/entities/own_player.hpp>
#include <sanguis/client/draw2d/entities/player.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters_fwd.hpp>
#include <sanguis/load/auras/context_fwd.hpp>
#include <fcppt/math/dim/structure_cast.hpp>


sanguis::client::draw2d::entities::own_player::own_player(
	sanguis::load::auras::context &_auras_load_context,
	sanguis::client::draw2d::entities::model::load_parameters const &_parameters,
	sanguis::client::draw2d::transform_callback const &_transform,
	sanguis::client::draw2d::collide_callback const &_collide,
	sanguis::aura_type_vector const &_auras,
	sanguis::buff_type_vector const &_buffs
)
:
	sanguis::client::draw2d::entities::player(
		_auras_load_context,
		_parameters,
		_auras,
		_buffs
	),
	transform_(
		_transform
	),
	collide_(
		_collide
	),
	desired_speed_(
		sanguis::client::draw2d::speed::value_type::null()
	)
{
}

sanguis::client::draw2d::entities::own_player::~own_player()
{
}

void
sanguis::client::draw2d::entities::own_player::update()
{
	sanguis::client::draw2d::optional_speed const new_speed(
		collide_(
			sanguis::client::draw2d::collide_parameters(
				this->movement_duration(),
				this->float_center(),
				this->speed(),
				fcppt::math::dim::structure_cast<
					sanguis::client::draw2d::dim2
				>(
					this->bounding_dim()
				)
			)
		)
	);

	if(
		new_speed
	)
		sanguis::client::draw2d::entities::player::speed(
			*new_speed
		);

	sanguis::client::draw2d::entities::player::update();

	transform_(
		this->center()
	);

	sanguis::client::draw2d::entities::player::speed(
		desired_speed_
	);
}

void
sanguis::client::draw2d::entities::own_player::speed(
	sanguis::client::draw2d::speed const &_speed
)
{
	desired_speed_ = _speed;

	sanguis::client::draw2d::entities::player::speed(
		_speed
	);
}
