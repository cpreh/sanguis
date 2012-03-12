#include <sanguis/server/pickup_spawner.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/entities/insert_parameters_center.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/pickups/health.hpp>
#include <sanguis/server/entities/pickups/monster.hpp>
#include <sanguis/server/entities/pickups/weapon.hpp>
#include <fcppt/random/actor/element.hpp>
#include <fcppt/random/actor/container.hpp>
#include <fcppt/random/make_inclusive_range.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>

sanguis::server::pickup_spawner::pickup_spawner(
	sanguis::diff_clock const &_diff_clock,
	environment::object &_env
)
:
	diff_clock_(_diff_clock),
	env_(_env),
	spawn_prob_(
		fcppt::random::make_inclusive_range(
			static_cast<
				server::probability::value_type
			>(
				0
			),
			static_cast<
				server::probability::value_type
			>(
				1
			)
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
	center_(
		server::center::value_type::null()
	)
{
}

sanguis::server::pickup_spawner::~pickup_spawner()
{
}

void
sanguis::server::pickup_spawner::spawn(
	server::probability const _prob,
	server::center const &_center
)
{
	if(
		spawn_prob_()
		> _prob.get()
	)
		return;

	// TODO: this is really ugly! :(
	center_ = _center;

	rng_();
}

void
sanguis::server::pickup_spawner::spawn_health()
{
	env_.insert(
		entities::unique_ptr(
			fcppt::make_unique_ptr<
				entities::pickups::health
			>(
				fcppt::cref(
					diff_clock_
				),
				fcppt::ref(
					env_.load_context()
				),
				team::players,
				server::health(
					10.f
				) // FIXME: which health value to use?
			)
		),
		entities::insert_parameters_center(
			center_
		)
	);
}

void
sanguis::server::pickup_spawner::spawn_monster()
{
	env_.insert(
		entities::unique_ptr(
			fcppt::make_unique_ptr<
				entities::pickups::monster
			>(
				fcppt::cref(
					diff_clock_
				),
				fcppt::ref(
					env_.load_context()
				),
				team::players,
				friend_type::spider
			)
		),
		entities::insert_parameters_center(
			center_
		)
	);
}

void
sanguis::server::pickup_spawner::spawn_weapon(
	weapon_type::type const _wtype
)
{
	env_.insert(
		entities::unique_ptr(
			fcppt::make_unique_ptr<
				entities::pickups::weapon
			>(
				fcppt::cref(
					diff_clock_
				),
				fcppt::ref(
					env_.load_context()
				),
				team::players,
				_wtype
			)
		),
		entities::insert_parameters_center(
			center_
		)
	);
}
