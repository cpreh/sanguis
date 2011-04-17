#include "choleric.hpp"
#include "../environment/object.hpp"
#include "../entities/projectiles/simple_bullet.hpp"
#include "../entities/projectiles/rocket.hpp"
#include "../entities/insert_parameters.hpp"
#include <sge/time/second_f.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/random/make_inclusive_range.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>

sanguis::server::perks::choleric::choleric()
:
	perk(
		perk_type::choleric
	),
	clock_(),
	shoot_timer_(
		sge::time::second_f(
			5.f
		),
		sge::time::activation_state::active,
		clock_.callback(),
		sge::time::expiration_state::not_expired
	),
	rand_(
		fcppt::random::make_inclusive_range(
			static_cast<space_unit>(0),
			fcppt::math::twopi<space_unit>()
		)
	)
{
}

sanguis::server::perks::choleric::~choleric()
{
}

void
sanguis::server::perks::choleric::update(
	entities::base &_entity,
	sanguis::time_type const _time,
	environment::object &_env
)
{
	clock_.update(
		_time
	);

	if(
		!shoot_timer_.update_b()
	)
		return;

	server::level const rocket_level(
		10
	);

	bool const spawn_bullets(
		this->level() < rocket_level
	);

	unsigned const count(
		spawn_bullets
		?
			3 + this->level().get() * 2
		:
			this->level().get()
	);

	for(
		unsigned index = 0;
		index < count;
		++index
	)
	{
		server::direction const direction(
			rand_()
		);

		_env.insert(
			spawn_bullets
			?
				entities::unique_ptr(
					fcppt::make_unique_ptr<
						entities::projectiles::simple_bullet
					>(
						fcppt::ref(
							_env.load_context()
						),
						_entity.team(),
						damage::unit(2), // damage
						direction
					)
				)
			:
				entities::unique_ptr(
					fcppt::make_unique_ptr<
						entities::projectiles::rocket
					>(
						fcppt::ref(
							_env.load_context()
						),
						_entity.team(),
						damage::unit(5), // damage
						server::radius(
							80
						),
						direction
					)
				)
			,
			entities::insert_parameters(
				_entity.center(),
				server::angle(
					direction.get()
				)
			)
		);
	}
}

void
sanguis::server::perks::choleric::change(
	entities::base &,
	level_diff
)
{
}
