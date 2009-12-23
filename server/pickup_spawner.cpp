#include "pickup_spawner.hpp"
#include "environment/object.hpp"
#include "entities/insert_parameters_pos.hpp"
#include "entities/insert_parameters.hpp"
#include "entities/auto_ptr.hpp"
#include "entities/pickups/health.hpp"
#include "entities/pickups/monster.hpp"
#include "entities/pickups/weapon.hpp"
#include <fcppt/random/actor/element.hpp>
#include <fcppt/random/actor/container.hpp>
#include <fcppt/random/inclusive_range.hpp>
#include <sge/assign/make_container.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <tr1/functional>

sanguis::server::pickup_spawner::pickup_spawner(
	environment::object_ptr const env
)
:
	env(env),
	spawn_prob(
		fcppt::random::make_inclusive_range(
			static_cast<probability_type>(0),
			static_cast<probability_type>(1)
		)
	),
	rng(
		sge::assign::make_container<
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
	pos(
		pos_type::null()
	)
{}

sanguis::server::pickup_spawner::~pickup_spawner()
{}

void
sanguis::server::pickup_spawner::spawn(
	probability_type const prob,
	pos_type const &npos
)
{
	if(
		spawn_prob()
		> prob
	)
		return;
	
	// TODO: this is really ugly! :(
	pos = npos;
	rng();
}

void
sanguis::server::pickup_spawner::spawn_health()
{
	env->insert(
		entities::auto_ptr(
			new entities::pickups::health(
				env->load_context(),
				team::players,
				entities::health_type(10) // FIXME: which health value to use?
			)
		),
		entities::insert_parameters_pos(
			pos
		)
	);
}

void
sanguis::server::pickup_spawner::spawn_monster()
{
	env->insert(
		entities::auto_ptr(
			new entities::pickups::monster(
				env->load_context(),
				team::players,
				friend_type::spider
			)
		),
		entities::insert_parameters_pos(
			pos
		)
	);
}

void
sanguis::server::pickup_spawner::spawn_weapon(
	weapon_type::type const wtype
)
{
	env->insert(
		entities::auto_ptr(
			new entities::pickups::weapon(
				env->load_context(),
				team::players,
				wtype
			)
		),
		entities::insert_parameters_pos(
			pos
		)
	);
}
