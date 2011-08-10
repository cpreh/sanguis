#include "weapon.hpp"
#include "log.hpp"
#include "unlimited_magazine_count.hpp"
#include "events/poll.hpp"
#include "events/reset.hpp"
#include "events/shoot.hpp"
#include "events/stop.hpp"
#include "states/ready.hpp"
#include "../entities/with_weapon.hpp"
#include "../collision/distance.hpp"
#include "../../exception.hpp"
#include <fcppt/chrono/duration_arithmetic.hpp>
#include <fcppt/chrono/duration_comparison.hpp>
#include <fcppt/math/sphere/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/text.hpp>
#include <ostream>

sanguis::server::weapons::range const
sanguis::server::weapons::weapon::range() const
{
	return range_;
}

sanguis::weapon_type::type
sanguis::server::weapons::weapon::type() const
{
	return type_;
}

void
sanguis::server::weapons::weapon::update(
	entities::with_weapon &_owner
)
{
	if(
		!this->usable()
	)
		return;

	this->process_event(
		events::poll(
			_owner
		)
	);
}

void
sanguis::server::weapons::weapon::attack(
	entities::with_weapon &_from,
	server::vector const &_to
)
{
	if(
		!this->usable()
	)
		return;

	this->process_event(
		events::shoot(
			_from,
			_to
		)
	);
}

void
sanguis::server::weapons::weapon::stop()
{
	this->process_event(
		events::stop()
	);
}

void
sanguis::server::weapons::weapon::repickup()
{
	this->reset_magazine();

	this->process_event(
		events::reset()
	);

	if(
		magazine_count_ != unlimited_magazine_count.get()
	)
		++magazine_count_;
}

sanguis::server::weapons::magazine_size const
sanguis::server::weapons::weapon::magazine_size() const
{
	return magazine_size_;
}

bool
sanguis::server::weapons::weapon::in_range(
	entities::base const &_from,
	server::vector const &_to
) const
{
	return
		collision::distance(
			_from,
			_to
		)
		< this->range().get();
}

void
sanguis::server::weapons::weapon::attack_speed(
	sanguis::time_unit const _ias
)
{
	ias_ = _ias;
}

void
sanguis::server::weapons::weapon::reload_speed(
	sanguis::time_unit const _irs
)
{
	irs_ = _irs;
}

sanguis::server::weapons::weapon::~weapon()
{
	this->terminate(); // FIXME!
}

sanguis::server::weapons::weapon::weapon(
	sanguis::diff_clock const &_diff_clock,
	weapon_type::type const _type,
	weapons::range const _range,
	weapons::magazine_size const _magazine_size,
	weapons::magazine_count const _magazine_count,
	weapons::base_cooldown const _base_cooldown,
	weapons::cast_point const _cast_point,
	weapons::reload_time const _reload_time
)
:
	diff_clock_(_diff_clock),
	type_(_type),
	range_(_range),
	magazine_used_(0),
	magazine_count_(_magazine_count.get()),
	magazine_size_(_magazine_size),
	cast_point_(
		_cast_point
	),
	backswing_time_(
		_base_cooldown.get() - _cast_point.get()
	),
	reload_time_(
		_reload_time.get()
	),
	ias_(
		0.f
	),
	irs_(
		0.f
	)
{
	if(
		_cast_point.get() > _base_cooldown.get()
	)
		FCPPT_LOG_WARNING(
			weapon::log(),
			fcppt::log::_
				<< FCPPT_TEXT("A weapon's cast point interval is bigger than its cooldown!")
	);

	if(
		this->magazine_size().get() == 0
	)
		throw sanguis::exception(
			FCPPT_TEXT("magazine size of 0 is invalid!")
		);

	// TODO: use a scoped state machine!
	this->initiate();
}

bool
sanguis::server::weapons::weapon::usable() const
{
	return magazine_count_ > 0;
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

	FCPPT_ASSERT(
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
		weapons::cast_point(
			cast_point_.get() * ias_
		);
}

sanguis::server::weapons::backswing_time const
sanguis::server::weapons::weapon::backswing_time() const
{
	return
		weapons::backswing_time(
			backswing_time_.get() * ias_
		);
}

sanguis::server::weapons::reload_time const
sanguis::server::weapons::weapon::reload_time() const
{
	return
		weapons::reload_time(
			reload_time_.get() * irs_
		);
}

void
sanguis::server::weapons::weapon::init_attack(
	entities::with_weapon &_entity
)
{
	_entity.start_attacking();

	this->on_init_attack(
		_entity
	);
}

void
sanguis::server::weapons::weapon::on_init_attack(
	entities::with_weapon &
)
{
}

void
sanguis::server::weapons::weapon::on_castpoint(
	entities::with_weapon &
)
{
}

fcppt::log::object &
sanguis::server::weapons::weapon::log()
{
	static fcppt::log::object my_logger(
		fcppt::log::parameters::inherited(
			weapons::log(),
			FCPPT_TEXT("weapon")
		)
	);

	return my_logger;
}
