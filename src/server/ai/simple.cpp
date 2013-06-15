#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/random_generator.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/vector.hpp>
#include <sanguis/server/ai/simple.hpp>
#include <sanguis/server/ai/search_new_target.hpp>
#include <sanguis/server/auras/aggro.hpp>
#include <sanguis/server/collision/distance.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/property/changeable_fwd.hpp>
#include <sanguis/server/entities/property/current_to_max.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/try_dynamic_cast.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/comparison.hpp>
#include <fcppt/math/vector/hypersphere_to_cartesian.hpp>
#include <fcppt/math/vector/length_square.hpp>
#include <fcppt/math/vector/signed_angle_between_cast.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/random/variate_impl.hpp>
#include <fcppt/random/distribution/basic_impl.hpp>
#include <fcppt/random/distribution/parameters/uniform_real_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/chrono/duration.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::server::ai::simple::simple(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::server::entities::with_ai &_me,
	sanguis::server::entities::auto_weak_link _owner
)
:
	pos_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			boost::chrono::milliseconds(
				500
			)
		)
		.expired(
			true
		)
	),
	me_(
		_me
	),
	target_(),
	owner_(
		_owner
	),
	potential_targets_(),
	fuzzy_target_rng_(
		_random_generator,
		distribution(
			distribution::param_type::min(
				0.f
			),
			distribution::param_type::sup(
				fcppt::math::twopi<
					sanguis::server::space_unit
				>()
			)
		)
	)
{
	me_.add_aura(
		fcppt::make_unique_ptr<
			sanguis::server::auras::aggro
		>(
			sanguis::server::radius(
				20.f // TODO
			),
			me_.team(),
			std::bind(
				&sanguis::server::ai::simple::simple::target_enters,
				this,
				std::placeholders::_1
			),
			std::bind(
				&sanguis::server::ai::simple::target_leaves,
				this,
				std::placeholders::_1
			)
		)
	);
}

sanguis::server::ai::simple::~simple()
{
}

void
sanguis::server::ai::simple::update()
{
	if(
		!target_ && !potential_targets_.empty()
	)
		target_ =
			sanguis::server::ai::search_new_target(
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
			sanguis::server::entities::with_velocity *,
			movable,
			&me_
		)
			movable->movement_speed().current(
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

	sanguis::server::space_unit const distance(
		sanguis::server::collision::distance(
			*target_,
			me_
		)
	);

	sanguis::server::vector const fuzzy_target(
		target_->center().get()
		+
		fcppt::math::vector::hypersphere_to_cartesian(
			fcppt::math::vector::static_<
				sanguis::server::space_unit,
				1
			>(
				fuzzy_target_rng_()
			)
		)
		* distance / 50.f
	);

	typedef fcppt::optional<
		sanguis::server::space_unit
	> optional_angle;

	optional_angle const angle(
		fcppt::math::vector::length_square(
			fuzzy_target
			-
			me_.center().get()
		)
		< 1.f
		?
			optional_angle()
		:
			optional_angle(
				fcppt::math::vector::signed_angle_between_cast<
					sanguis::server::space_unit
				>(
					me_.center().get(),
					fuzzy_target
				)
			)
	);

	if(
		angle
	)
	{
		FCPPT_TRY_DYNAMIC_CAST(
			sanguis::server::entities::with_body *,
			with_body,
			&me_
		)
			with_body->angle(
				sanguis::server::angle(
					*angle
				)
			);
	}

	FCPPT_TRY_DYNAMIC_CAST(
		sanguis::server::entities::with_velocity *,
		movable,
		&me_
	)
	{
		sanguis::server::entities::property::changeable &speed(
			movable->movement_speed()
		);

		if(
			angle
		)
		{
			movable->direction(
				sanguis::server::direction(
					*angle
				)
			);

			sanguis::server::entities::property::current_to_max(
				speed
			);
		}
		else
			movable->movement_speed().current(
				0
			);
	}
}

void
sanguis::server::ai::simple::target_enters(
	sanguis::server::entities::with_body &_new_target
)
{
	sanguis::server::entities::with_health *const with_health(
		dynamic_cast<
			sanguis::server::entities::with_health *
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

	// if we already have a target and the new target is farther away do
	// nothing
	if(
		target_
		&& sanguis::server::collision::distance(
			*target_,
			me_
		)
		> sanguis::server::collision::distance(
			_new_target,
			me_
		)
	)
		return;

	target_ = _new_target.link();
}

void
sanguis::server::ai::simple::target_leaves(
	sanguis::server::entities::with_body &_old_target
)
{
	potential_targets_.erase(
		_old_target.id()
	);
}
