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
#include "../collision/bounding_circle.hpp"
#include "../../exception.hpp"
#include <sge/time/second_f.hpp>
#include <sge/time/resolution.hpp>
#include <sge/math/circle/basic_impl.hpp>
#include <sge/math/vector/basic_impl.hpp>
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
	time_type const tm,
	entities::with_weapon &owner
)
{
	if(!usable())
		return;

	process_event(
		events::poll(
			tm,
			owner
		)
	);
}

void
sanguis::server::weapons::weapon::attack(
	entities::with_weapon &from,
	pos_type const &to
)
{
	if(!usable())
		return;
	
	process_event(
		events::shoot(
			from,
			to
		)
	);
}

void
sanguis::server::weapons::weapon::stop()
{
	process_event(
		events::stop()
	);
}

void
sanguis::server::weapons::weapon::repickup()
{
	reset_magazine();

	process_event(
		events::reset()
	);

	if(magazine_count_ != unlimited_magazine_count)
		++magazine_count_;
}

sanguis::server::weapons::magazine_size const
sanguis::server::weapons::weapon::magazine_size() const
{
	return magazine_size_;
}

bool
sanguis::server::weapons::weapon::in_range(
	entities::base const &from,
	pos_type const &to
) const
{
	return
		collision::distance(
			from,
			to
		) - collision::bounding_circle(
			from
		)
		.radius() < range();
}

void
sanguis::server::weapons::weapon::attack_speed(
	space_unit const speed)
{
	ias_ = speed;
}

void
sanguis::server::weapons::weapon::reload_speed(
	space_unit const speed)
{
	irs_ = speed;
}

sanguis::server::weapons::weapon::~weapon()
{}

sanguis::server::weapons::weapon::weapon(
	weapon_type::type const type_,
	weapons::range const range_,
	weapons::magazine_size const magazine_size_,
	weapons::magazine_count const magazine_count_,
	weapons::base_cooldown const nbase_cooldown_,
	weapons::cast_point const ncast_point_,
	weapons::reload_time const nreload_time_
)
:
	type_(type_),
	range_(range_),
	magazine_used_(0),
	magazine_count_(magazine_count_),
	magazine_size_(magazine_size_),
	cast_point_(
		sge::time::second_f(
			ncast_point_
		)
	),
	backswing_time_(
		sge::time::second_f(
			nbase_cooldown_ - ncast_point_
		)
	),
	reload_time_(
		sge::time::second_f(
			nreload_time_
		)
	),
	ias_(static_cast<space_unit>(0)),
	irs_(static_cast<space_unit>(0))
{
	if(ncast_point_ > nbase_cooldown_)
		SGE_LOG_WARNING(
			log(),
			fcppt::log::_
				<< FCPPT_TEXT("A weapon's cast point interval is bigger than its cooldown!")
	);

	if(magazine_size() == 0)
		throw exception(
			FCPPT_TEXT("magazine size of 0 is invalid!")
		);

	initiate();
}

sanguis::time_type
sanguis::server::weapons::weapon::ias() const
{
	return ias_;
}

sanguis::time_type
sanguis::server::weapons::weapon::irs() const
{
	return irs_;
}

bool
sanguis::server::weapons::weapon::usable() const
{
	return magazine_count_ > 0;
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
	SGE_ASSERT(magazine_used_ <= magazine_size());
}

bool
sanguis::server::weapons::weapon::magazine_empty() const
{
	return magazine_used_ == magazine_size();
}

void
sanguis::server::weapons::weapon::magazine_exhausted()
{
	if(magazine_count_ != unlimited_magazine_count)
		--magazine_count_;
}

sge::time::resolution const
sanguis::server::weapons::weapon::cast_point() const
{
	return cast_point_;
}

sge::time::resolution const
sanguis::server::weapons::weapon::backswing_time() const
{
	return backswing_time_;
}

sge::time::resolution const
sanguis::server::weapons::weapon::reload_time() const
{
	return reload_time_;
}

void
sanguis::server::weapons::weapon::init_attack(
	entities::with_weapon &e
)
{
	e.start_attacking();

	on_init_attack(e);
}

void
sanguis::server::weapons::weapon::on_init_attack(
	entities::with_weapon &
)
{}

void
sanguis::server::weapons::weapon::on_castpoint(
	entities::with_weapon &
)
{}

fcppt::log::object &
sanguis::server::weapons::weapon::log()
{
	static fcppt::log::object log_(
		fcppt::log::parameters::inherited(
			weapons::log(),
			FCPPT_TEXT("weapon")
		)
	);
	return log_;
}
