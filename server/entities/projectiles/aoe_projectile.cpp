#include "aoe_projectile.hpp"
#include "../../../messages/add_aoe_projectile.hpp"
#include "../../../messages/create.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>

sanguis::server::entities::projectiles::aoe_projectile::aoe_projectile(
	aoe_projectile_type::type const type_,
	server::environment::load_context_ptr const load_context_,
	team::type const team_,
	property_map const &properties_,
	dim_type const &dim,
	life_time const life_time_,
	indeterminate::type const indeterminate_,
	space_unit const aoe_
)
:
	projectile(
		projectile_type::aoe,
		load_context_,
		team_,
		properties_,
		dim,
		life_time_,
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
			health(),
			max_health(),
			dim(),
			aoe_,
			type_
		)
	);
}
