#include <sanguis/random_generator.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/pickup_spawner.hpp>
#include <sanguis/server/probability.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/entities/insert_parameters_center.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/pickups/health.hpp>
#include <sanguis/server/entities/pickups/monster.hpp>
#include <sanguis/server/entities/pickups/weapon.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/random/variate_impl.hpp>
#include <fcppt/random/distribution/uniform_real_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/strong_typedef_assignment.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/spirit/home/phoenix/bind/bind_member_variable.hpp>
#include <boost/spirit/home/phoenix/core/argument.hpp>
#include <boost/spirit/home/phoenix/operator/arithmetic.hpp>
#include <numeric>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::server::pickup_spawner::pickup_spawner(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	environment::object &_env
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
	spawns_(
		fcppt::assign::make_container<
			spawn_vector
		>(
			std::make_pair(
				server::probability(
					4.f
				),
				pickup_spawner::spawn_function(
					std::tr1::bind(
						&pickup_spawner::spawn_health,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			std::make_pair(
				server::probability(
					0.3f
				),
				pickup_spawner::spawn_function(
					std::tr1::bind(
						&pickup_spawner::spawn_monster,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			std::make_pair(
				server::probability(
					2.f
				),
				pickup_spawner::spawn_function(
					std::tr1::bind(
						&pickup_spawner::spawn_weapon,
						this,
						std::tr1::placeholders::_1,
						sanguis::weapon_type::pistol
					)
				)
			)
		)
		(
			std::make_pair(
				server::probability(
					0.8f
				),
				pickup_spawner::spawn_function(
					std::tr1::bind(
						&pickup_spawner::spawn_weapon,
						this,
						std::tr1::placeholders::_1,
						sanguis::weapon_type::shotgun
					)
				)
			)
		)
		(
			std::make_pair(
				server::probability(
					1.f
				),
				pickup_spawner::spawn_function(
					std::tr1::bind(
						&pickup_spawner::spawn_weapon,
						this,
						std::tr1::placeholders::_1,
						sanguis::weapon_type::rocket_launcher
					)
				)
			)
		)
		(
			std::make_pair(
				server::probability(
					4.f
				),
				pickup_spawner::spawn_function(
					std::tr1::bind(
						&pickup_spawner::spawn_weapon,
						this,
						std::tr1::placeholders::_1,
						sanguis::weapon_type::grenade
					)
				)
			)
		)
		(
			std::make_pair(
				server::probability(
					0.3f
				),
				pickup_spawner::spawn_function(
					std::tr1::bind(
						&pickup_spawner::spawn_weapon,
						this,
						std::tr1::placeholders::_1,
						sanguis::weapon_type::sentry
					)
				)
			)
		)
	),
	spawn_prob_(
		_random_generator,
		real_distribution(
			real_distribution::min(
				0.f
			),
			real_distribution::sup(
				1.f
			)
		)
	),
	spawn_value_(
		_random_generator,
		real_distribution(
			real_distribution::min(
				0.f
			),
			real_distribution::sup(
				std::accumulate(
					spawns_.begin(),
					spawns_.end(),
					server::probability(
						0.f
					),
					boost::phoenix::bind(
						&spawn_pair::first,
						boost::phoenix::arg_names::_2
					)
					+
					boost::phoenix::arg_names::_1
				).get()
			)
		)
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

	server::probability const value(
		spawn_value_()
	);

	server::probability cur(
		0.f
	);

	for(
		spawn_vector::const_iterator it(
			spawns_.begin()
		);
		it != spawns_.end();
		++it
	)
	{
		cur += it->first;

		if(
			cur < value
		)
		{
			it->second(
				_center
			);

			return;
		}
	}
}

void
sanguis::server::pickup_spawner::spawn_health(
	server::center const &_center
)
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
			_center
		)
	);
}

void
sanguis::server::pickup_spawner::spawn_monster(
	server::center const &_center
)
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
					random_generator_
				),
				fcppt::ref(
					env_.load_context()
				),
				team::players,
				friend_type::spider
			)
		),
		entities::insert_parameters_center(
			_center
		)
	);
}

void
sanguis::server::pickup_spawner::spawn_weapon(
	server::center const &_center,
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
			_center
		)
	);
}
