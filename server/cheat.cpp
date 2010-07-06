#include "cheat.hpp"
#include "entities/player.hpp"
#include "weapons/create.hpp"
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
	switch(type)
	{
	case cheat_type::exp:
		p.add_exp(
			static_cast<exp_type>(100000)
		);
		return;
	case cheat_type::impulse101:
		for(
			unsigned i = 0;
			i < 50;
			++i
		)
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
		return;
	case cheat_type::kill:
		p.die();
		return;
	case cheat_type::size:
		break;
	}

	throw exception(
		FCPPT_TEXT("Invalid cheat type!")
	);
}
