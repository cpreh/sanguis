#include <sanguis/diff_clock.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/magazine_extra.hpp>
#include <sanguis/magazine_remaining.hpp>
#include <sanguis/magazine_size.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/update_diff_clock.hpp>
#include <sanguis/weapon_attribute_type.hpp>
#include <sanguis/weapon_description.hpp>
#include <sanguis/weapon_status.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/collision/distance_entity_pos.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/optional_reload_time.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/target.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/attributes/magazine_size.hpp>
#include <sanguis/server/weapons/attributes/make.hpp>
#include <sanguis/server/weapons/attributes/optional_accuracy.hpp>
#include <sanguis/server/weapons/attributes/optional_magazine_size.hpp>
#include <sanguis/server/weapons/events/poll.hpp>
#include <sanguis/server/weapons/events/reload.hpp>
#include <sanguis/server/weapons/events/shoot.hpp>
#include <sanguis/server/weapons/events/stop.hpp>
#include <sanguis/server/weapons/states/idle.hpp>
#include <fcppt/algorithm/join.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::server::weapons::weapon::weapon(
	sanguis::random_generator &_random_generator,
	sanguis::weapon_type const _type,
	sanguis::server::weapons::attributes::optional_accuracy const _accuracy,
	sanguis::server::weapons::range const _range,
	sanguis::server::weapons::attributes::optional_magazine_size const _magazine_size,
	sanguis::server::weapons::backswing_time const _backswing_time,
	sanguis::server::weapons::cast_point const _cast_point,
	sanguis::server::weapons::optional_reload_time const _reload_time
)
:
	diff_clock_(),
	random_generator_(
		_random_generator
	),
	type_(
		_type
	),
	accuracy_(
		_accuracy
	),
	range_(
		_range
	),
	magazine_used_(
		0u
	),
	magazine_size_(
		_magazine_size
	),
	cast_point_(
		_cast_point
	),
	backswing_time_(
		_backswing_time
	),
	reload_time_(
		_reload_time
	),
	owner_()
{
	FCPPT_ASSERT_PRE(
		this->magazine_size().value().get()
		!=
		0u
	);
}

FCPPT_PP_POP_WARNING

sanguis::server::weapons::weapon::~weapon()
{
}

void
sanguis::server::weapons::weapon::owner(
	sanguis::server::entities::optional_with_weapon_ref const &_owner
)
{
	if(
		_owner
	)
	{
		owner_ =
			_owner;

		this->initiate();
	}
	else
	{
		this->terminate();

		owner_ =
			sanguis::server::entities::optional_with_weapon_ref();
	}
}

void
sanguis::server::weapons::weapon::attack()
{
	this->process_event(
		sanguis::server::weapons::events::shoot()
	);
}

void
sanguis::server::weapons::weapon::reload()
{
	this->process_event(
		sanguis::server::weapons::events::reload()
	);
}

void
sanguis::server::weapons::weapon::stop()
{
	this->process_event(
		sanguis::server::weapons::events::stop()
	);
}

void
sanguis::server::weapons::weapon::update()
{
	this->process_event(
		sanguis::server::weapons::events::poll()
	);
}

void
sanguis::server::weapons::weapon::tick(
	sanguis::duration const &_duration
)
{
	sanguis::update_diff_clock(
		diff_clock_,
		_duration
	);
}

sanguis::weapon_type
sanguis::server::weapons::weapon::type() const
{
	return
		type_;
}

sanguis::server::weapons::attributes::magazine_size const
sanguis::server::weapons::weapon::magazine_size() const
{
	return
		magazine_size_
		?
			*magazine_size_
		:
			sanguis::server::weapons::attributes::magazine_size(
				sanguis::server::weapons::magazine_size(
					1u
				)
			)
		;
}

bool
sanguis::server::weapons::weapon::in_range(
	sanguis::server::weapons::target const _to
) const
{
	return
		sanguis::server::collision::distance_entity_pos(
			this->owner(),
			_to.get()
		)
		<
		range_.get();
}

bool
sanguis::server::weapons::weapon::owner_target_in_range() const
{
	return
		this->owner().target()
		&&
		this->in_range(
			*this->owner().target()
		);
}

sanguis::weapon_description
sanguis::server::weapons::weapon::description() const
{
	return
		sanguis::weapon_description(
			this->type(),
			sanguis::magazine_size(
				this->magazine_size().base().get()
			),
			sanguis::magazine_extra(
				this->magazine_size().extra()
				?
					this->magazine_size().extra()->get()
				:
					0u
			),
			this->magazine_remaining(),
			// TODO: Make composing this more sane!
			accuracy_
			?
				fcppt::algorithm::join(
					sanguis::weapon_attribute_vector{
						sanguis::server::weapons::attributes::make(
							sanguis::weapon_attribute_type::accuracy,
							*accuracy_
						)
					},
					this->attributes()
				)
			:
				this->attributes()
		);
}

sanguis::diff_clock const &
sanguis::server::weapons::weapon::diff_clock() const
{
	return
		diff_clock_;
}

sanguis::random_generator &
sanguis::server::weapons::weapon::random_generator() const
{
	return
		random_generator_;
}

sanguis::server::entities::with_weapon &
sanguis::server::weapons::weapon::owner() const
{
	FCPPT_ASSERT_PRE(
		owner_
	);

	return
		*owner_;
}

void
sanguis::server::weapons::weapon::weapon_status(
	sanguis::weapon_status const _status
)
{
	this->owner().weapon_status(
		_status,
		*this
	);
}

void
sanguis::server::weapons::weapon::reset_magazine()
{
	magazine_used_ =
		0u;

	this->update_magazine_remaining();
}

void
sanguis::server::weapons::weapon::use_magazine_item()
{
	++magazine_used_;

	this->update_magazine_remaining();

	FCPPT_ASSERT_ERROR(
		magazine_used_
		<=
		this->magazine_size().value().get()
	);
}

bool
sanguis::server::weapons::weapon::magazine_empty() const
{
	return
		magazine_used_
		==
		this->magazine_size().value().get();
}

sanguis::server::weapons::attributes::optional_accuracy const
sanguis::server::weapons::weapon::accuracy() const
{
	return
		accuracy_;
}

sanguis::server::weapons::cast_point const
sanguis::server::weapons::weapon::cast_point() const
{
	return
		cast_point_;
}

sanguis::server::weapons::backswing_time const
sanguis::server::weapons::weapon::backswing_time() const
{
	return
		backswing_time_;
}

sanguis::server::weapons::optional_reload_time const
sanguis::server::weapons::weapon::reload_time() const
{
	return
		reload_time_;
}

sanguis::magazine_remaining const
sanguis::server::weapons::weapon::magazine_remaining() const
{
	return
		sanguis::magazine_remaining(
			this->magazine_size().value().get()
			-
			magazine_used_
		);
}

void
sanguis::server::weapons::weapon::update_magazine_remaining()
{
	this->owner().magazine_remaining(
		this->magazine_remaining(),
		*this
	);
}
