#include <sanguis/random_generator.hpp>
#include <sanguis/server/ai/simple.hpp>
#include <sanguis/server/ai/search_new_target.hpp>
#include <sanguis/server/auras/aggro.hpp>
#include <sanguis/server/auras/unique_ptr.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/property/changeable_fwd.hpp>
#include <sanguis/server/entities/property/current_to_max.hpp>
#include <sanguis/server/collision/distance.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/vector.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/math/vector/comparison.hpp>
#include <fcppt/math/vector/hypersphere_to_cartesian.hpp>
#include <fcppt/math/vector/signed_angle_between_cast.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/random/variate_impl.hpp>
#include <fcppt/random/distribution/uniform_real_impl.hpp>
#include <fcppt/try_dynamic_cast.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/chrono/duration.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::server::ai::simple::simple(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	entities::with_ai &_me,
	entities::auto_weak_link _owner
)
:
	pos_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			boost::chrono::seconds(
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
	potential_targets_(),
	timer_rng_(
		_random_generator,
		distribution(
			distribution::min(
				0.f
			),
			distribution::sup(
				2.f
			)
		)
	),
	fuzzy_target_rng_(
		_random_generator,
		distribution(
			distribution::min(
				0.f
			),
			distribution::sup(
				fcppt::math::twopi<
					server::space_unit
				>()
			)
		)
	)
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
				std::bind(
					&simple::target_enters,
					this,
					std::placeholders::_1
				),
				std::bind(
					&simple::target_leaves,
					this,
					std::placeholders::_1
				)
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

	server::space_unit const distance(
		collision::distance(
			*target_,
			me_
		)
	);

	pos_timer_.interval(
		boost::chrono::duration<
			server::space_unit
		>(
			distance
			*
			(
				1.f
				+
				timer_rng_()
			)
			/ 1000.f // TODO!
		)
	);

	server::vector const fuzzy_target(
		target_->center().get()
		+
		fcppt::math::vector::hypersphere_to_cartesian(
			fcppt::math::vector::static_<
				server::space_unit,
				1
			>::type(
				fuzzy_target_rng_()
			)
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
			optional_angle(
				fcppt::math::vector::signed_angle_between_cast<
					space_unit
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
