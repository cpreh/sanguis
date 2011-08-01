#include "simple.hpp"
#include "search_new_target.hpp"
#include "../auras/aggro.hpp"
#include "../auras/unique_ptr.hpp"
#include "../entities/with_ai.hpp"
#include "../entities/with_body.hpp"
#include "../entities/with_health.hpp"
#include "../entities/with_velocity.hpp"
#include "../entities/property/changeable_fwd.hpp"
#include "../entities/property/current_to_max.hpp"
#include "../collision/distance.hpp"
#include "../angle.hpp"
#include "../direction.hpp"
#include "../space_unit.hpp"
#include "../vector.hpp"
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/chrono/seconds.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/comparison.hpp>
#include <fcppt/math/vector/signed_angle_cast.hpp>
#include <fcppt/math/vector/unit_circle.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/try_dynamic_cast.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional.hpp>

sanguis::server::ai::simple::simple(
	sanguis::diff_clock const &_diff_clock,
	entities::with_ai &_me,
	entities::auto_weak_link _owner
)
:
	pos_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			fcppt::chrono::seconds(
				0 // TODO
			)
		)
		.expired(
			true
		)
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
					20.f // TODO
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

#include <fcppt/random/uniform.hpp>
#include <fcppt/random/make_inclusive_range.hpp>
#include <fcppt/math/twopi.hpp>

void
sanguis::server::ai::simple::update()
{
	if(
		!target_ && !potential_targets_.empty()
	)
		target_
			= ai::search_new_target(
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
			entities::with_velocity *,
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
		!sge::timer::reset_when_expired(
			pos_timer_
		)
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

	server::space_unit const distance(
		collision::distance(
			*target_,
			me_
		)
	);

	pos_timer_.interval(
		fcppt::chrono::duration<
			server::space_unit
		>(
			distance * (1.f + rng()) / 1000.f // TODO!
		)
	);

	server::vector const fuzzy_target(
		target_->center().get()
		+
		fcppt::math::vector::unit_circle(
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
	{
		FCPPT_TRY_DYNAMIC_CAST(
			entities::with_body *,
			with_body,
			&me_
		)
			with_body->angle(
				server::angle(
					*angle
				)
			);
	}

	FCPPT_TRY_DYNAMIC_CAST(
		entities::with_velocity *,
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
