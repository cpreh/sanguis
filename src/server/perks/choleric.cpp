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

	unsigned const max(
		this->can_raise_level()
		?
			3 + this->level().get() * 2
		:
			10
	);

	for(
		unsigned i = 0;
		i < max;
		++i
	)
	{
		server::direction const direction(
			rand_()
		);

		_env.insert(
			this->can_raise_level()
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

sanguis::server::level const
sanguis::server::perks::choleric::max_level() const
{
	return
		server::level(
			10
		);
}

void
sanguis::server::perks::choleric::change(
	entities::base &,
	level_diff
)
{
}
