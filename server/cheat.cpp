#include "cheat.hpp"
#include "entities/player.hpp"
#include "weapons/factory.hpp"
#include "weapons/weapon.hpp"
#include "../exception.hpp"
#include <fcppt/foreach_enumerator_start.hpp>
#include <fcppt/text.hpp>

void
sanguis::server::cheat(
	entities::player &p,
	cheat_type::type const type
)
{
	switch(type) {
	case cheat_type::impulse101:
		FCPPT_FOREACH_ENUMERATOR_START(
			index,
			weapon_type,
			weapon_type::pistol
		)
			p.add_weapon(
				weapons::create(
					static_cast<
						weapon_type::type
					>(
						index
					)
				)
			);
		break;
	case cheat_type::kill:
		p.die();
		break;
	default:
		throw exception(
			FCPPT_TEXT("Invalid cheat type!")
		);
	}
}
