#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/log_parameters.hpp>
#include <sanguis/weapon_description.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/collision/distance_entity_pos.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/entities/with_weapon_fwd.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/log_location.hpp>
#include <sanguis/server/weapons/magazine_count.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/make_attribute.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/target.hpp>
#include <sanguis/server/weapons/unlimited_magazine_count.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/events/poll.hpp>
#include <sanguis/server/weapons/events/shoot.hpp>
#include <sanguis/server/weapons/events/stop.hpp>
#include <sanguis/server/weapons/states/ready.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/scoped_state_machine_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/join.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/log/parameters/object.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/chrono/chrono_io.hpp>
#include <fcppt/config/external_end.hpp>


namespace
{

fcppt::log::object logger(
	sanguis::log_parameters(
		sanguis::server::weapons::log_location()
		/
		FCPPT_TEXT("weapon")
	)
);

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::server::weapons::weapon::weapon(
	sanguis::diff_clock const &_diff_clock,
	sanguis::weapon_type const _type,
	sanguis::server::weapons::range const _range,
	sanguis::server::weapons::magazine_size const _magazine_size,
	sanguis::server::weapons::magazine_count const _magazine_count,
	sanguis::server::weapons::base_cooldown const _base_cooldown,
	sanguis::server::weapons::cast_point const _cast_point,
	sanguis::server::weapons::reload_time const _reload_time
)
:
	diff_clock_(
		_diff_clock
	),
	type_(
		_type
	),
	range_(
		_range
	),
	magazine_used_(
		0u
	),
	magazine_count_(
		_magazine_count.get()
	),
	magazine_size_(
		_magazine_size
	),
	cast_point_(
		_cast_point
	),
	backswing_time_(
		_base_cooldown.get()
		-
		_cast_point.get()
	),
	reload_time_(
		_reload_time.get()
	),
	scoped_machine_(
		*this
	)
{
	if(
		_cast_point.get() > _base_cooldown.get()
	)
		FCPPT_LOG_WARNING(
			::logger,
			fcppt::log::_
				<< FCPPT_TEXT("A weapon's cast point interval is bigger than its cooldown!")
	);

	FCPPT_ASSERT_PRE(
		this->magazine_size().get() != 0
	);
}

FCPPT_PP_POP_WARNING

sanguis::server::weapons::weapon::~weapon()
{
}

void
sanguis::server::weapons::weapon::attack(
	sanguis::server::entities::with_weapon &_from
)
{
	if(
		!this->usable()
	)
		return;

	this->process_event(
		sanguis::server::weapons::events::shoot(
			_from
		)
	);
}

void
sanguis::server::weapons::weapon::stop(
	sanguis::server::entities::with_weapon &_owner
)
{
	this->process_event(
		sanguis::server::weapons::events::stop(
			_owner
		)
	);
}

void
sanguis::server::weapons::weapon::update(
	sanguis::server::entities::with_weapon &_owner
)
{
	if(
		!this->usable()
	)
		return;

	this->process_event(
		sanguis::server::weapons::events::poll(
			_owner
		)
	);
}

sanguis::weapon_type
sanguis::server::weapons::weapon::type() const
{
	return type_;
}

sanguis::server::weapons::magazine_size const
sanguis::server::weapons::weapon::magazine_size() const
{
	return magazine_size_;
}

bool
sanguis::server::weapons::weapon::in_range(
	sanguis::server::entities::base const &_from,
	sanguis::server::weapons::target const _to
) const
{
	return
		sanguis::server::collision::distance_entity_pos(
			_from,
			_to.get()
		)
		<
		range_.get();
}

bool
sanguis::server::weapons::weapon::usable() const
{
	return magazine_count_ > 0;
}

sanguis::weapon_description
sanguis::server::weapons::weapon::description() const
{
	return
		sanguis::weapon_description(
			fcppt::algorithm::join(
				sanguis::string_vector{
					sanguis::server::weapons::make_attribute(
						FCPPT_TEXT("range"),
						fcppt::insert_to_fcppt_string(
							range_
						)
					),
					sanguis::server::weapons::make_attribute(
						FCPPT_TEXT("magazine size"),
						fcppt::insert_to_fcppt_string(
							magazine_size_
						)
					),
					sanguis::server::weapons::make_attribute(
						FCPPT_TEXT("cast point"),
						fcppt::insert_to_fcppt_string(
							cast_point_
						)
					),
					sanguis::server::weapons::make_attribute(
						FCPPT_TEXT("backswing time"),
						fcppt::insert_to_fcppt_string(
							backswing_time_
						)
					),
					sanguis::server::weapons::make_attribute(
						FCPPT_TEXT("reload time"),
						fcppt::insert_to_fcppt_string(
							reload_time_
						)
					)
				},
				this->attributes()
			),
			this->type()
		);
}

sanguis::diff_clock const &
sanguis::server::weapons::weapon::diff_clock() const
{
	return diff_clock_;
}

void
sanguis::server::weapons::weapon::reset_magazine()
{
	magazine_used_ = 0;
}

void
sanguis::server::weapons::weapon::use_magazine_item()
{
	++magazine_used_;

	FCPPT_ASSERT_ERROR(
		magazine_used_ <= magazine_size_.get()
	);
}

bool
sanguis::server::weapons::weapon::magazine_empty() const
{
	return
		magazine_used_ == magazine_size_.get();
}

void
sanguis::server::weapons::weapon::magazine_exhausted()
{
	if(
		magazine_count_ != unlimited_magazine_count.get()
	)
		--magazine_count_;
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

sanguis::server::weapons::reload_time const
sanguis::server::weapons::weapon::reload_time() const
{
	return
		reload_time_;
}
