#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/friend_type.hpp>
#include <sanguis/primary_weapon_type.hpp>
#include <sanguis/random_generator.hpp>
#include <sanguis/secondary_weapon_type.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/entities/insert_parameters_center.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/pickups/health.hpp>
#include <sanguis/server/entities/pickups/monster.hpp>
#include <sanguis/server/entities/pickups/weapon.hpp>
#include <sanguis/server/environment/insert_no_result.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/create.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/world/pickup_spawner.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/strong_typedef_assignment.hpp>
#include <fcppt/random/variate_impl.hpp>
#include <fcppt/random/distribution/basic_impl.hpp>
#include <fcppt/random/distribution/parameters/uniform_real_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <numeric>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::world::pickup_spawner::pickup_spawner(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::server::environment::object &_env
)
:
	diff_clock_(
		_diff_clock
	),
	random_generator_(
		_random_generator
	),
	env_(
		_env
	),
	spawns_{
		std::make_pair(
			sanguis::server::pickup_probability(
				4.f
			),
			sanguis::server::world::pickup_spawner::spawn_function(
				std::bind(
					&sanguis::server::world::pickup_spawner::spawn_health,
					this,
					std::placeholders::_1,
					std::placeholders::_2
				)
			)
		),
		std::make_pair(
			sanguis::server::pickup_probability(
				0.3f
			),
			sanguis::server::world::pickup_spawner::spawn_function(
				std::bind(
					&sanguis::server::world::pickup_spawner::spawn_monster,
					this,
					std::placeholders::_1,
					std::placeholders::_2
				)
			)
		),
		std::make_pair(
			sanguis::server::pickup_probability(
				2.f
			),
			sanguis::server::world::pickup_spawner::spawn_function(
				std::bind(
					&sanguis::server::world::pickup_spawner::spawn_weapon,
					this,
					std::placeholders::_1,
					std::placeholders::_2,
					sanguis::weapon_type(
						sanguis::primary_weapon_type::pistol
					)
				)
			)
		),
		std::make_pair(
			sanguis::server::pickup_probability(
				0.8f
			),
			sanguis::server::world::pickup_spawner::spawn_function(
				std::bind(
					&sanguis::server::world::pickup_spawner::spawn_weapon,
					this,
					std::placeholders::_1,
					std::placeholders::_2,
					sanguis::weapon_type(
						sanguis::primary_weapon_type::shotgun
					)
				)
			)
		),
		std::make_pair(
			sanguis::server::pickup_probability(
				1.f
			),
			sanguis::server::world::pickup_spawner::spawn_function(
				std::bind(
					&sanguis::server::world::pickup_spawner::spawn_weapon,
					this,
					std::placeholders::_1,
					std::placeholders::_2,
					sanguis::weapon_type(
						sanguis::primary_weapon_type::rocket_launcher
					)
				)
			)
		),
		std::make_pair(
			sanguis::server::pickup_probability(
				4.f
			),
			sanguis::server::world::pickup_spawner::spawn_function(
				std::bind(
					&sanguis::server::world::pickup_spawner::spawn_weapon,
					this,
					std::placeholders::_1,
					std::placeholders::_2,
					sanguis::weapon_type(
						sanguis::secondary_weapon_type::grenade
					)
				)
			)
		),
		std::make_pair(
			sanguis::server::pickup_probability(
				0.3f
			),
			sanguis::server::world::pickup_spawner::spawn_function(
				std::bind(
					&sanguis::server::world::pickup_spawner::spawn_weapon,
					this,
					std::placeholders::_1,
					std::placeholders::_2,
					sanguis::weapon_type(
						sanguis::secondary_weapon_type::sentry
					)
				)
			)
		)
	},
	spawn_prob_(
		_random_generator,
		real_distribution(
			real_distribution::param_type::min(
				0.f
			),
			real_distribution::param_type::sup(
				1.f
			)
		)
	),
	spawn_value_(
		_random_generator,
		real_distribution(
			real_distribution::param_type::min(
				0.f
			),
			real_distribution::param_type::sup(
				std::accumulate(
					spawns_.begin(),
					spawns_.end(),
					sanguis::server::pickup_probability(
						0.f
					),
					[](
						sanguis::server::pickup_probability const _cur,
						sanguis::server::world::pickup_spawner::spawn_pair const &item
					)
					{
						return
							item.first
							+
							_cur;
					}
				).get()
			)
		)
	)
{
}

sanguis::server::world::pickup_spawner::~pickup_spawner()
{
}

void
sanguis::server::world::pickup_spawner::spawn(
	sanguis::server::pickup_probability const _prob,
	sanguis::server::center const _center,
	sanguis::server::entities::enemies::difficulty const _difficulty
)
{
	if(
		spawn_prob_()
		> _prob.get()
	)
		return;

	sanguis::server::pickup_probability const value(
		spawn_value_()
	);

	sanguis::server::pickup_probability cur(
		0.f
	);

	for(
		auto const &cur_spawn : spawns_
	)
	{
		cur += cur_spawn.first;

		if(
			value < cur
		)
		{
			cur_spawn.second(
				_center,
				_difficulty
			);

			return;
		}
	}
}

void
sanguis::server::world::pickup_spawner::spawn_health(
	sanguis::server::center const _center,
	sanguis::server::entities::enemies::difficulty const _difficulty
)
{
	this->spawn_entity(
		fcppt::make_unique_ptr<
			sanguis::server::entities::pickups::health
		>(
			diff_clock_,
			env_.load_context(),
			sanguis::server::team::players,
			sanguis::server::health(
				10.f
			)
		),
		_center
	);
}

void
sanguis::server::world::pickup_spawner::spawn_monster(
	sanguis::server::center const _center,
	sanguis::server::entities::enemies::difficulty const _difficulty
)
{
	this->spawn_entity(
		fcppt::make_unique_ptr<
			sanguis::server::entities::pickups::monster
		>(
			diff_clock_,
			env_.load_context(),
			sanguis::server::team::players,
			sanguis::friend_type::spider,
			_difficulty
		),
		_center
	);
}

void
sanguis::server::world::pickup_spawner::spawn_weapon(
	sanguis::server::center const _center,
	sanguis::server::entities::enemies::difficulty const _difficulty,
	sanguis::weapon_type const _wtype
)
{
	this->spawn_entity(
		fcppt::make_unique_ptr<
			sanguis::server::entities::pickups::weapon
		>(
			env_.load_context(),
			sanguis::server::team::players,
			sanguis::server::weapons::create(
				diff_clock_,
				random_generator_,
				_wtype,
				_difficulty
			)
		),
		_center
	);
}

void
sanguis::server::world::pickup_spawner::spawn_entity(
	sanguis::server::entities::unique_ptr &&_entity,
	sanguis::server::center const _center
)
{
	sanguis::server::environment::insert_no_result(
		env_,
		std::move(
			_entity
		),
		sanguis::server::entities::insert_parameters_center(
			_center
		)
	);
}
