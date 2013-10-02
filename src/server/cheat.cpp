#include <sanguis/cheat_type.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/friend_type.hpp>
#include <sanguis/server/cheat.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/entities/insert_parameters_center.hpp>
#include <sanguis/server/entities/player.hpp>
#include <sanguis/server/entities/pickups/monster.hpp>
#include <sanguis/server/environment/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assert/unreachable.hpp>


void
sanguis::server::cheat(
	sanguis::diff_clock const &_diff_clock,
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
	case sanguis::cheat_type::kill:
		_player.kill();
		return;
	case sanguis::cheat_type::monster_pickup:
		if(
			!_player.has_environment()
		)
			return;

		_player.environment().insert(
			fcppt::make_unique_ptr<
				sanguis::server::entities::pickups::monster
			>(
				_diff_clock,
				_player.environment().load_context(),
				sanguis::server::team::players,
				sanguis::friend_type::spider
			),
			sanguis::server::entities::insert_parameters_center(
				_player.center()
			)
		);

		return;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
