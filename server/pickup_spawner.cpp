#include "pickup_spawner.hpp"
#include "entities/auto_ptr.hpp"
#include "entities/pickups/health.hpp"
#include "entities/pickups/monster.hpp"
#include "entities/pickups/weapon.hpp"
#include <sge/random/actor/element.hpp>
#include <sge/random/actor/container.hpp>
#include <sge/assign/make_container.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <tr1/functional>

sanguis::server::pickup_spawner::pickup_spawner(
	environment const &env)
:
	env(env),
	rng(
		sge::assign::make_container<
			sge::random::actor::container
		>(
			sge::random::actor::element(
				static_cast<sge::random::actor::float_type>(4),
				std::tr1::bind(
					&pickup_spawner::spawn_health,
					this
				)
			)
		)
		(
			sge::random::actor::element(
				static_cast<sge::random::actor::float_type>(0.3),
				std::tr1::bind(
					&pickup_spawner::spawn_monster,
					this
				)
			)
		)
		(
			sge::random::actor::element(
				static_cast<sge::random::actor::float_type>(2),
				std::tr1::bind(
					&pickup_spawner::spawn_weapon,
					this,
					sanguis::weapon_type::pistol
				)
			)
		)
		(
			sge::random::actor::element(
				static_cast<sge::random::actor::float_type>(0.8),
				std::tr1::bind(
					&pickup_spawner::spawn_weapon,
					this,
					sanguis::weapon_type::shotgun
				)
			)
		)
		(
			sge::random::actor::element(
				static_cast<sge::random::actor::float_type>(1),
				std::tr1::bind(
					&pickup_spawner::spawn_weapon,
					this,
					sanguis::weapon_type::rocket_launcher
				)
			)
		)
		(
			sge::random::actor::element(
				static_cast<sge::random::actor::float_type>(4),
				std::tr1::bind(
					&pickup_spawner::spawn_weapon,
					this,
					sanguis::weapon_type::grenade
				)
			)
		)
		(
			sge::random::actor::element(
				static_cast<sge::random::actor::float_type>(0.3),
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

void
sanguis::server::pickup_spawner::spawn(
	pos_type const &npos)
{
	// TODO: this is really ugly! :(
	pos = npos;
	rng();
}

void
sanguis::server::pickup_spawner::spawn_health()
{
	env.insert()(
		entities::auto_ptr(
			new entities::pickups::health(
				env,
				pos,
				team::players,
				10 // FIXME: which health value to use?
			)
		)
	);
}

void
sanguis::server::pickup_spawner::spawn_monster()
{
	env.insert()(
		entities::auto_ptr(
			new entities::pickups::monster(
				env,
				pos,
				team::players,
				friend_type::spider
			)
		)
	);
}

void
sanguis::server::pickup_spawner::spawn_weapon(
	weapon_type::type const wtype)
{
	env.insert()(
		entities::auto_ptr(
			new entities::pickups::weapon(
				env,
				pos,
				team::players,
				wtype
			)
		)
	);
}
