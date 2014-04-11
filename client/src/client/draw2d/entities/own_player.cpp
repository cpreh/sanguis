#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/client/health_pair.hpp>
#include <sanguis/client/optional_health_pair.hpp>
#include <sanguis/client/player_health_callback.hpp>
#include <sanguis/client/draw2d/collide_callback.hpp>
#include <sanguis/client/draw2d/collide_parameters.hpp>
#include <sanguis/client/draw2d/dim2.hpp>
#include <sanguis/client/draw2d/optional_player_center.hpp>
#include <sanguis/client/draw2d/optional_speed.hpp>
#include <sanguis/client/draw2d/player_center.hpp>
#include <sanguis/client/draw2d/player_center_callback.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/entities/name.hpp>
#include <sanguis/client/draw2d/entities/own_player.hpp>
#include <sanguis/client/draw2d/entities/player.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/load/auras/context_fwd.hpp>
#include <fcppt/math/dim/structure_cast.hpp>


sanguis::client::draw2d::entities::own_player::own_player(
	sanguis::client::load::auras::context &_auras_load_context,
	sanguis::client::draw2d::entities::model::load_parameters const &_parameters,
	sanguis::client::draw2d::player_center_callback const &_player_center_callback,
	sanguis::client::draw2d::collide_callback const &_collide,
	sanguis::client::player_health_callback const &_player_health_callback,
	sanguis::aura_type_vector const &_auras,
	sanguis::buff_type_vector const &_buffs,
	sanguis::client::health_pair const _health_pair
)
:
	sanguis::client::draw2d::entities::player(
		_auras_load_context,
		_parameters,
		_auras,
		_buffs,
		_health_pair,
		sanguis::client::draw2d::entities::name(
			sanguis::client::draw2d::entities::name::value_type()
		)
	),
	player_center_callback_(
		_player_center_callback
	),
	collide_(
		_collide
	),
	player_health_callback_(
		_player_health_callback
	),
	desired_speed_(
		sanguis::client::draw2d::speed::value_type::null()
	)
{
}

sanguis::client::draw2d::entities::own_player::~own_player()
{
	player_center_callback_(
		sanguis::client::draw2d::optional_player_center()
	);
}

void
sanguis::client::draw2d::entities::own_player::health(
	sanguis::client::health const _health
)
{
	sanguis::client::draw2d::entities::model::object::health(
		_health
	);

	this->update_health();
}

void
sanguis::client::draw2d::entities::own_player::max_health(
	sanguis::client::max_health const _max_health
)
{
	sanguis::client::draw2d::entities::model::object::max_health(
		_max_health
	);

	this->update_health();
}

void
sanguis::client::draw2d::entities::own_player::speed(
	sanguis::client::draw2d::speed const &_speed
)
{
	desired_speed_ =
		_speed;

	sanguis::client::draw2d::entities::player::speed(
		_speed
	);
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

	player_center_callback_(
		sanguis::client::draw2d::optional_player_center(
			sanguis::client::draw2d::player_center(
				this->center()
			)
		)
	);

	sanguis::client::draw2d::entities::player::speed(
		desired_speed_
	);
}

void
sanguis::client::draw2d::entities::own_player::on_die()
{
	sanguis::client::draw2d::entities::model::object::on_die();

	player_health_callback_(
		sanguis::client::optional_health_pair()
	);
}

void
sanguis::client::draw2d::entities::own_player::update_health()
{
	player_health_callback_(
		this->health_pair()
	);
}