#include "simple.hpp"
#include "search_new_target.hpp"
#include "../auras/aggro.hpp"
#include "../auras/unique_ptr.hpp"
#include "../entities/movable.hpp"
#include "../entities/with_ai.hpp"
#include "../entities/with_body.hpp"
#include "../entities/with_health.hpp"
#include "../entities/property/current_to_max.hpp"
#include "../collision/collides.hpp"
#include "../collision/distance.hpp"
#include "../vector.hpp"
#include <sge/time/second.hpp>
#include <fcppt/math/vector/signed_angle_cast.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/comparison.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/try_dynamic_cast.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional.hpp>

sanguis::server::ai::simple::simple(
	entities::with_ai &_me,
	entities::auto_weak_link _owner
)
:
	diff_clock_(),
	pos_timer_(
		sge::time::second(
			0 // TODO	
		),
		sge::time::activation_state::active,
		diff_clock_.callback(),
		sge::time::expiration_state::expired
	),
	me_(_me),
	target_(),
	owner_(_owner),
	potential_targets_()
{
	me_.add_aura(
		auras::unique_ptr(
			fcppt::make_unique_ptr<
				auras::aggro
			>(
				server::radius(
					1000.f // TODO
				),
				me_.team(),
				std::tr1::bind(
					&simple::target_enters,
					this,
					std::tr1::placeholders::_1
				),
				std::tr1::bind(
					&simple::target_leaves,
					this,
					std::tr1::placeholders::_1
				)
			)
		)
	);
}

sanguis::server::ai::simple::~simple()
{
}

// TODO: move this!

#include <sge/time/second_f.hpp>
#include <fcppt/random/uniform.hpp>
#include <fcppt/random/make_inclusive_range.hpp>
#include <fcppt/math/twopi.hpp>
#include <cmath>

namespace
{

sanguis::server::vector const
make_vector_from_angle(
	sanguis::server::space_unit const _angle
)
{
	return
		sanguis::server::vector(
			std::cos(
				_angle
			),
			std::sin(
				_angle
			)
		);
}

}

void
sanguis::server::ai::simple::update(
	time_type const _time
)
{
	diff_clock_.update(
		_time
	);

	if(
		!target_ && !potential_targets_.empty()
	)
		target_
			= search_new_target(
				me_,
				potential_targets_
			);

	if(
		!target_
	)
	{
		me_.aggressive(
			false
		);

		FCPPT_TRY_DYNAMIC_CAST(
			entities::movable *,
			movable_,
			&me_
		)
			movable_->movement_speed().current(
				0
			);

		return;
	}

	me_.target(
		target_->center().get()
	);

	if(
		!pos_timer_.update_b()
	)
		return;

	me_.aggressive(
		true
	);

	typedef fcppt::random::uniform<
		space_unit
	> rng_type;

	// FIXME!
	static rng_type rng(
		fcppt::random::make_inclusive_range(
			static_cast<
				space_unit
			>(
				0
			),
			fcppt::math::twopi<
				space_unit
			>()
		)
	);

	space_unit const distance(
		collision::distance(
			*target_,
			me_
		)
	);

	pos_timer_.interval(
		sge::time::second_f(
			distance * (1.f + rng()) / 1000.f // TODO!
		)
	);

	server::vector const fuzzy_target(
		target_->center().get()
		+
		make_vector_from_angle(
			rng()
		)
		* distance / 50.f
	);

	typedef fcppt::optional<
		server::space_unit
	> optional_angle;
	
	optional_angle const angle(
		fuzzy_target == me_.center().get()
		?
			optional_angle()
		:
			fcppt::math::vector::signed_angle_cast<
				space_unit
			>(
				me_.center().get(),
				fuzzy_target
			)
	);

	if(
		angle
	)
		me_.angle(
			server::angle(
				*angle
			)
		);

	FCPPT_TRY_DYNAMIC_CAST(
		entities::movable *,
		movable,
		&me_
	)
	{
		entities::property::changeable &speed(
			movable->movement_speed()
		);

		if(
			angle
		)
			movable->direction(
				server::direction(
					*angle
				)
			);
	
		// don't walk into the enemy
		// TODO: this should be done with the collision system
		if(
			collision::collides(
				*target_,
				me_
			)
		)
			speed.current(
				0
			);
		else
			entities::property::current_to_max(
				speed
			);
	}
}

void
sanguis::server::ai::simple::target_enters(
	entities::with_body &_new_target
)
{
	entities::with_health *const with_health(
		dynamic_cast<
			entities::with_health *
		>(
			&_new_target
		)
	);

	if(
		!with_health
	)
		return;

	potential_targets_.insert(
		_new_target.id(),
		with_health
	);

	if(
		target_
	)
		return;
	
	// if we already have a target
	// and the new target is farther away
	// do nothing
	if(
		target_
		&& collision::distance(
			*target_,
			me_
		)
		> collision::distance(
			_new_target,
			me_
		)
	)
		return;
			
	target_ = _new_target.link();
}

void
sanguis::server::ai::simple::target_leaves(
	entities::with_body &_old_target
)
{
	potential_targets_.erase(
		_old_target.id()
	);
}
