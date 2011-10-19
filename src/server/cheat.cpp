#include <sanguis/server/cheat.hpp>
#include <sanguis/server/entities/player.hpp>
#include <sanguis/server/weapons/create.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/foreach_enumerator_start.hpp>
#include <fcppt/assert/unreachable.hpp>

void
sanguis::server::cheat(
	sanguis::diff_clock const &_diff_clock,
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
						_diff_clock,
						index
					)
				);
		return;
	case cheat_type::kill:
		_player.kill();
		return;
	case cheat_type::size:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
