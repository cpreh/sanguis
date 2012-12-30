#include <sanguis/cheat_type.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/cheat.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/entities/player.hpp>
#include <sanguis/server/weapons/create.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/foreach_enumerator_start.hpp>
#include <fcppt/assert/unreachable.hpp>


void
sanguis::server::cheat(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::server::entities::player &_player,
	sanguis::cheat_type const _type
)
{
	switch(
		_type
	)
	{
	case sanguis::cheat_type::exp:
		_player.add_exp(
			sanguis::server::exp(
				100000.f
			)
		);
		return;
	case sanguis::cheat_type::impulse101:
		for(
			unsigned i = 0;
			i < 50;
			++i
		)
			FCPPT_FOREACH_ENUMERATOR_START(
				index,
				sanguis::weapon_type,
				sanguis::weapon_type::pistol
			)
				_player.add_weapon(
					sanguis::server::weapons::create(
						_diff_clock,
						_random_generator,
						index
					)
				);
		return;
	case sanguis::cheat_type::kill:
		_player.kill();
		return;
	case sanguis::cheat_type::size:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
