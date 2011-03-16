#include "pickup_spawner.hpp"
#include "environment/object.hpp"
#include "entities/insert_parameters_pos.hpp"
#include "entities/insert_parameters.hpp"
#include "entities/unique_ptr.hpp"
#include "entities/pickups/health.hpp"
#include "entities/pickups/monster.hpp"
#include "entities/pickups/weapon.hpp"
#include <fcppt/random/actor/element.hpp>
#include <fcppt/random/actor/container.hpp>
#include <fcppt/random/make_inclusive_range.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_unique_ptr.hpp>

sanguis::server::pickup_spawner::pickup_spawner(
	environment::object_ptr const _env
)
:
	env_(_env),
	spawn_prob_(
		fcppt::random::make_inclusive_range(
			static_cast<probability_type>(0),
			static_cast<probability_type>(1)
		)
	),
	rng_(
		fcppt::assign::make_container<
			fcppt::random::actor::container
		>(
			fcppt::random::actor::element(
				static_cast<fcppt::random::actor::float_type>(4),
				std::tr1::bind(
					&pickup_spawner::spawn_health,
					this
				)
			)
		)
		(
			fcppt::random::actor::element(
				static_cast<fcppt::random::actor::float_type>(0.3),
				std::tr1::bind(
					&pickup_spawner::spawn_monster,
					this
				)
			)
		)
		(
			fcppt::random::actor::element(
				static_cast<fcppt::random::actor::float_type>(2),
				std::tr1::bind(
					&pickup_spawner::spawn_weapon,
					this,
					sanguis::weapon_type::pistol
				)
			)
		)
		(
			fcppt::random::actor::element(
				static_cast<fcppt::random::actor::float_type>(0.8),
				std::tr1::bind(
					&pickup_spawner::spawn_weapon,
					this,
					sanguis::weapon_type::shotgun
				)
			)
		)
		(
			fcppt::random::actor::element(
				static_cast<fcppt::random::actor::float_type>(1),
				std::tr1::bind(
					&pickup_spawner::spawn_weapon,
					this,
					sanguis::weapon_type::rocket_launcher
				)
			)
		)
		(
			fcppt::random::actor::element(
				static_cast<fcppt::random::actor::float_type>(4),
				std::tr1::bind(
					&pickup_spawner::spawn_weapon,
					this,
					sanguis::weapon_type::grenade
				)
			)
		)
		(
			fcppt::random::actor::element(
				static_cast<fcppt::random::actor::float_type>(0.3),
				std::tr1::bind(
					&pickup_spawner::spawn_weapon,
					this,
					sanguis::weapon_type::sentry
				)
			)
		)
	),
	pos_(
		pos_type::null()
	)
{
}

sanguis::server::pickup_spawner::~pickup_spawner()
{
}

void
sanguis::server::pickup_spawner::spawn(
	probability_type const _prob,
	pos_type const &_pos
)
{
	if(
		spawn_prob_()
		> _prob
	)
		return;
	
	// TODO: this is really ugly! :(
	pos_ = _pos;

	rng_();
}

void
sanguis::server::pickup_spawner::spawn_health()
{
	env_->insert(
		entities::unique_ptr(
			fcppt::make_unique_ptr<
				entities::pickups::health
			>(
				env_->load_context(),
				team::players,
				entities::health_type(10) // FIXME: which health value to use?
			)
		),
		entities::insert_parameters_pos(
			pos_
		)
	);
}

void
sanguis::server::pickup_spawner::spawn_monster()
{
	env_->insert(
		entities::unique_ptr(
			fcppt::make_unique_ptr<
				entities::pickups::monster
			>(
				env_->load_context(),
				team::players,
				friend_type::spider
			)
		),
		entities::insert_parameters_pos(
			pos_
		)
	);
}

void
sanguis::server::pickup_spawner::spawn_weapon(
	weapon_type::type const _wtype
)
{
	env_->insert(
		entities::unique_ptr(
			fcppt::make_unique_ptr<
				entities::pickups::weapon
			>(
				env_->load_context(),
				team::players,
				_wtype
			)
		),
		entities::insert_parameters_pos(
			pos_
		)
	);
}
