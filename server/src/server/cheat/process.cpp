#include <sanguis/cheat_type.hpp>
#include <sanguis/friend_type.hpp>
#include <sanguis/perk_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/send_available_perks.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/unicast_callback.hpp>
#include <sanguis/server/cheat/process.hpp>
#include <sanguis/server/cheat/weapon_type.hpp>
#include <sanguis/server/entities/insert_parameters_center.hpp>
#include <sanguis/server/entities/player.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/pickups/monster.hpp>
#include <sanguis/server/entities/pickups/weapon.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/environment/optional_object_ref.hpp>
#include <sanguis/server/weapons/create.hpp>
#include <sanguis/server/weapons/monster_spawner.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/make_enum_range.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assert/unreachable.hpp>


void
sanguis::server::cheat::process(
	sanguis::random_generator &_random_generator,
	sanguis::server::entities::player &_player,
	sanguis::cheat_type const _cheat_type,
	sanguis::server::unicast_callback const &_unicast_callback
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
		_cheat_type
	)
	{
	case sanguis::cheat_type::exp:
		_player.add_exp(
			sanguis::server::exp(
				100000.f
			)
		);
		return;
	case sanguis::cheat_type::heal:
		_player.health().current(
			_player.max_health().get()
		);
		return;
	case sanguis::cheat_type::kill:
		_player.kill();
		return;
	case sanguis::cheat_type::friendly_spider:
		environment->insert(
			fcppt::make_unique_ptr<
				sanguis::server::entities::pickups::monster
			>(
				_random_generator,
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
	case sanguis::cheat_type::monster_spawner:
		environment->insert(
			fcppt::make_unique_ptr<
				sanguis::server::entities::pickups::weapon
			>(
				environment->load_context(),
				sanguis::server::team::players,
				fcppt::make_unique_ptr<
					sanguis::server::weapons::monster_spawner
				>(
					_random_generator
				)
			),
			sanguis::server::entities::insert_parameters_center(
				_player.center()
			)
		);

		return;
	case sanguis::cheat_type::sentry:
	case sanguis::cheat_type::grenade:
	case sanguis::cheat_type::shotgun:
	case sanguis::cheat_type::rocket_launcher:
		environment->insert(
			fcppt::make_unique_ptr<
				sanguis::server::entities::pickups::weapon
			>(
				environment->load_context(),
				sanguis::server::team::players,
				sanguis::server::weapons::create(
					_random_generator,
					sanguis::server::cheat::weapon_type(
						_cheat_type
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
	case sanguis::cheat_type::perks:
		for(
			auto perk
			:
			fcppt::make_enum_range<
				sanguis::perk_type
			>()
		)
			while(
				_player.perk_choosable(
					perk
				)
			)
				_player.add_perk(
					perk
				);

		sanguis::server::send_available_perks(
			_player,
			_unicast_callback
		);

		return;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
