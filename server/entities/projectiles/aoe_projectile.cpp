#include "aoe_projectile.hpp"
#include "../../../messages/add_aoe_projectile.hpp"
#include "../../../messages/create.hpp"
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>

sanguis::server::entities::projectiles::aoe_projectile::aoe_projectile(
	aoe_projectile_type::type const type_,
	team::type const team_,
	entities::movement_speed const movement_speed_,
	dim_type const &dim_,
	life_time const life_time_,
	indeterminate::type const indeterminate_,
	space_unit const aoe_,
	space_unit const direction_
)
:
	projectile(
		projectile_type::aoe,
		team_,
		movement_speed_,
		dim_,
		life_time_,
		direction_,
		indeterminate_
	),
	type_(type_),
	aoe_(aoe_)
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
