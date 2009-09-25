#include "ias.hpp"
#include "../entities/property.hpp"
#include "../entities/entity.hpp"

sanguis::server::perks::ias::ias()
:
	perk(
		perk_type::ias
	)
{}

void
sanguis::server::perks::ias::do_apply(
	entities::base &entity_,
	time_type,
	environment::object_ptr,
	environment::load_context_ptr
)
{
	dynamic_cast<
		with_weapon &
	>(
		entity_
	)
	.attack_speed().multiply_max(
		factor()
	);
}

bool
sanguis::server::perks::ias::can_raise_level() const
{
	return level() < 8;
}

sanguis::server::space_unit
sanguis::server::perks::ias::factor() const
{
	return
		static_cast<space_unit>(level())
		* static_cast<space_unit>(0.2);
}
