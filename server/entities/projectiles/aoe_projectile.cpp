#include "aoe_projectile.hpp"
#include "../../health_type.hpp"
#include "../../../messages/add_aoe_projectile.hpp"
#include "../../../messages/create.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>

sanguis::server::entities::projectiles::aoe_projectile::aoe_projectile(
	aoe_projectile_type::type const type_,
	team::type const team_,
	server::movement_speed const movement_speed_,
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
sanguis::server::entities::projectiles::aoe_projectile::add_message() const
{
	return messages::create(
		messages::add_aoe_projectile(
			id(),
			pos(),
			angle(),
			abs_speed(),
			health_type(0),
			health_type(0),
			dim(),
			aoe_,
			type_
		)
	);
}
