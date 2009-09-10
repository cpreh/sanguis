#include "cheat.hpp"
#include "entities/player.hpp"
#include "weapons/factory.hpp"
#include "weapons/weapon.hpp"
#include "../exception.hpp"
#include <sge/foreach_enum.hpp>
#include <sge/text.hpp>

void
sanguis::server::cheat(
	entities::player &p,
	cheat_type::type const type,
	environment::object_pt const env
)
{
	switch(type) {
	case cheat_type::impulse101:
		SGE_FOREACH_ENUM_2(
			index
			weapon_type,
			weapon_type::pistol
		)
			p.add_weapon(
				weapons::create(
					static_cast<
						weapon_type::type
					>(
						index
					),
					env
				)
			);
		break;
	case cheat_type::kill:
		p.die();
		break;
	default:
		throw exception(
			SGE_TEXT("Invalid cheat type!")
		);
	}
}
