#include "cheat.hpp"
#include "entities/player.hpp"
#include "weapons/create.hpp"
#include "weapons/weapon.hpp"
#include "../exception.hpp"
#include <fcppt/foreach_enumerator_start.hpp>
#include <fcppt/text.hpp>

void
sanguis::server::cheat(
	entities::player &_player,
	cheat_type::type const _type
)
{
	switch(
		_type
	)
	{
	case cheat_type::exp:
		_player.add_exp(
			server::exp(
				100000
			)
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
				_player.add_weapon(
					weapons::create(
						index
					)
				);
		return;
	case cheat_type::kill:
		_player.die();
		return;
	case cheat_type::size:
		break;
	}

	throw sanguis::exception(
		FCPPT_TEXT("Invalid cheat type!")
	);
}
