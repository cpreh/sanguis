#include "ias.hpp"
#include "../entities/property/value.hpp"
#include "../entities/property/linear_add.hpp"
#include "../entities/with_weapon.hpp"

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
	environment::object_ptr
)
{
	entities::property::linear_add(
		dynamic_cast<
			entities::with_weapon &
		>(
			entity_
		)
		.attack_speed(),
		entities::property::value(
			level(),
			5
		)
	);
}

bool
sanguis::server::perks::ias::can_raise_level() const
{
	return level() < 8;
}
