#include "irs.hpp"
#include "../entities/property/object.hpp"
#include "../entities/property/value.hpp"
#include "../entities/property/linear_add.hpp"
#include "../entities/with_weapon.hpp"

sanguis::server::perks::irs::irs()
:
	perk(
		perk_type::irs
	)
{}

void
sanguis::server::perks::irs::do_apply(
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
		.reload_speed(),
		entities::property::value(
			level(),
			2
		)
	);
}

bool
sanguis::server::perks::irs::can_raise_level() const
{
	return level() < 4;
}
