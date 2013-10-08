#include <sanguis/cheat_type.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/friend_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/secondary_weapon_type.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/cheat.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/entities/insert_parameters_center.hpp>
#include <sanguis/server/entities/player.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/pickups/monster.hpp>
#include <sanguis/server/entities/pickups/weapon.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/environment/optional_object_ref.hpp>
#include <sanguis/server/weapons/create.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assert/unreachable.hpp>


void
sanguis::server::cheat(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::server::entities::player &_player,
	sanguis::cheat_type const _type
)
{
	sanguis::server::environment::optional_object_ref const environment(
		_player.environment()
	);

	if(
		!environment
	)
		return;

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
		environment->insert(
			fcppt::make_unique_ptr<
				sanguis::server::entities::pickups::monster
			>(
				_diff_clock,
				environment->load_context(),
				sanguis::server::team::players,
				sanguis::friend_type::spider,
				sanguis::server::entities::enemies::difficulty(
					100.f
				)
			),
			sanguis::server::entities::insert_parameters_center(
				_player.center()
			)
		);
		return;
	case sanguis::cheat_type::sentry_pickup:
	case sanguis::cheat_type::grenade_pickup:
		environment->insert(
			fcppt::make_unique_ptr<
				sanguis::server::entities::pickups::weapon
			>(
				_diff_clock,
				environment->load_context(),
				sanguis::server::team::players,
				sanguis::server::weapons::create(
					_diff_clock,
					_random_generator,
					sanguis::weapon_type(
						// TODO: Refactor this!
						_type
						==
						sanguis::cheat_type::sentry_pickup
						?
							sanguis::secondary_weapon_type::sentry
						:
							sanguis::secondary_weapon_type::grenade
					),
					sanguis::server::entities::enemies::difficulty(
						100.f
					)
				)
			),
			sanguis::server::entities::insert_parameters_center(
				_player.center()
			)
		);

		return;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
