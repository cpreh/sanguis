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
#include <sanguis/server/entities/pickups/weapon.hpp>
#include <sanguis/server/environment/insert_no_result.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/random/distributor_impl.hpp>
#include <sanguis/server/weapons/create.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/world/pickup_spawner.hpp>
#include <fcppt/make_literal_strong_typedef.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/strong_typedef_assignment.hpp>
#include <fcppt/random/distribution/basic_impl.hpp>
#include <fcppt/random/distribution/parameters/uniform_real_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <functional>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::world::pickup_spawner::pickup_spawner(
	sanguis::random_generator &_random_generator,
	sanguis::server::environment::object &_env
)
:
	random_generator_(
		_random_generator
	),
	env_(
		_env
	),
	distributor_(
		sanguis::server::world::pickup_spawner::distributor::vector{
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
					1.f
				),
				this->make_spawn_weapon(
					sanguis::weapon_type(
						sanguis::primary_weapon_type::pistol
					)
				)
			),
			std::make_pair(
				sanguis::server::pickup_probability(
					0.8f
				),
				this->make_spawn_weapon(
					sanguis::weapon_type(
						sanguis::primary_weapon_type::shotgun
					)
				)
			),
			std::make_pair(
				sanguis::server::pickup_probability(
					1.f
				),
				this->make_spawn_weapon(
					sanguis::weapon_type(
						sanguis::primary_weapon_type::rocket_launcher
					)
				)
			),
			std::make_pair(
				sanguis::server::pickup_probability(
					4.f
				),
				this->make_spawn_weapon(
					sanguis::weapon_type(
						sanguis::secondary_weapon_type::grenade
					)
				)
			),
			std::make_pair(
				sanguis::server::pickup_probability(
					0.5f
				),
				this->make_spawn_weapon(
					sanguis::weapon_type(
						sanguis::secondary_weapon_type::sentry
					)
				)
			),
			std::make_pair(
				sanguis::server::pickup_probability(
					0.5f
				),
				this->make_spawn_weapon(
					sanguis::weapon_type(
						sanguis::secondary_weapon_type::spider
					)
				)
			)
		}
	),
	spawn_prob_(
		real_distribution(
			real_distribution::param_type::min(
				0.f
			),
			real_distribution::param_type::sup(
				1.f
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
		spawn_prob_(
			random_generator_
		)
		>
		_prob.get()
	)
		return;

	distributor_.execute(
		random_generator_
	)(
		_center,
		_difficulty
	);
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
			env_.load_context(),
			sanguis::server::team::players,
			sanguis::server::health(
				10.f
				*
				std::sqrt(
					_difficulty.get()
				)
			)
		),
		_center
	);
}

void
sanguis::server::world::pickup_spawner::spawn_weapon(
	sanguis::server::center const _center,
	sanguis::server::entities::enemies::difficulty const _difficulty,
	sanguis::weapon_type const _weapon_type
)
{
	this->spawn_entity(
		fcppt::make_unique_ptr<
			sanguis::server::entities::pickups::weapon
		>(
			env_.load_context(),
			sanguis::server::team::players,
			sanguis::server::weapons::create(
				random_generator_,
				_weapon_type,
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

sanguis::server::world::pickup_spawner::spawn_function
sanguis::server::world::pickup_spawner::make_spawn_weapon(
	sanguis::weapon_type const &_weapon_type
)
{
	return
		sanguis::server::world::pickup_spawner::spawn_function(
			std::bind(
				&sanguis::server::world::pickup_spawner::spawn_weapon,
				this,
				std::placeholders::_1,
				std::placeholders::_2,
				_weapon_type
			)
		);
}
