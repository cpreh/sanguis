#include "aoe_projectile.hpp"
#include "../../../messages/add_aoe_projectile.hpp"
#include "../../../messages/create.hpp"
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>

sanguis::server::entities::projectiles::aoe_projectile::aoe_projectile(
	aoe_projectile_type::type const _type,
	team::type const _team,
	entities::movement_speed const _movement_speed,
	dim_type const &_dim,
	life_time const _life_time,
	indeterminate::type const _indeterminate,
	space_unit const _aoe,
	space_unit const _direction
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
{}

sanguis::server::space_unit
sanguis::server::entities::projectiles::aoe_projectile::aoe() const
{
	return aoe_;
}

sanguis::messages::auto_ptr
sanguis::server::entities::projectiles::aoe_projectile::add_message(
	player_id const
) const
{
	return messages::create(
		messages::add_aoe_projectile(
			id(),
			pos(),
			angle(),
			dim(),
			abs_speed(),
			aoe_,
			type_
		)
	);
}
