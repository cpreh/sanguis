#include "aoe_projectile.hpp"
#include "../../../messages/add_aoe_projectile.hpp"
#include "../../../messages/create.hpp"
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>

sanguis::server::entities::projectiles::aoe_projectile::aoe_projectile(
	aoe_projectile_type::type const _type,
	team::type const _team,
	entities::movement_speed const _movement_speed,
	server::dim const &_dim,
	life_time const _life_time,
	indeterminate::type const _indeterminate,
	server::radius const _aoe,
	server::direction const _direction
)
:
	projectile(
		projectile_type::aoe,
		_team,
		_movement_speed,
		_dim,
		_life_time,
		_direction,
		_indeterminate
	),
	type_(_type),
	aoe_(_aoe)
{
}

sanguis::server::entities::projectiles::aoe_projectile::~aoe_projectile()
{
}

sanguis::server::radius const
sanguis::server::entities::projectiles::aoe_projectile::aoe() const
{
	return aoe_;
}

sanguis::messages::auto_ptr
sanguis::server::entities::projectiles::aoe_projectile::add_message(
	player_id const
) const
{
	return
		messages::create(
			messages::add_aoe_projectile(
				this->id(),
				this->center().get(),
				this->angle().get(),
				this->abs_speed().get(),
				aoe_.get(),
				type_
			)
		);
}
