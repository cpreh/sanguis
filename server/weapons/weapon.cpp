#include "weapon.hpp"
#include "delayed_attack.hpp"
#include "log.hpp"
#include "events/poll.hpp"
#include "events/shoot.hpp"
#include "states/ready.hpp"
#include "../entities/entity_with_weapon.hpp"
#include "../collision/distance.hpp"
#include "../collision/bounding_circle.hpp"
#include "../../exception.hpp"
#include <sge/time/second_f.hpp>
#include <sge/time/resolution.hpp>
#include <sge/math/circle_impl.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/text.hpp>
#include <sge/log/headers.hpp>
#include <limits>
#include <ostream>

sanguis::server::space_unit
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
	entities::entity_with_weapon &owner)
{
	process_event(
		events::poll(
			tm,
			owner
		)
	);
}

void
sanguis::server::weapons::weapon::attack(
	entities::entity_with_weapon &from,
	pos_type const &to)
{
	process_event(
		events::shoot(
			from,
			to
		)
	);
}

sanguis::server::weapons::magazine_type
sanguis::server::weapons::weapon::magazine_size() const
{
	return magazine_size_;
}

bool
sanguis::server::weapons::weapon::in_range(
	entities::entity const &from,
	pos_type const &to) const
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
	server::environment const &env_,
	weapon_type::type const type_,
	space_unit const range_,
	magazine_type const magazine_size_,
	time_type const nbase_cooldown,
	time_type const ncast_point,
	time_type const nreload_time)
:
	env_(env_),
	type_(type_),
	range_(range_),
	magazine_used(0),
	magazine_size_(magazine_size_),
	base_cooldown_(
		sge::time::second_f(
			nbase_cooldown
		)
	),
	cast_point_(
		sge::time::second_f(
			ncast_point
		)
	),
	reload_time_(
		sge::time::second_f(
			nreload_time
		)
	),
	ias_(static_cast<space_unit>(0)),
	irs_(static_cast<space_unit>(0))
{
	if(cast_point_.get() > base_cooldown_.get())
		SGE_LOG_WARNING(
			log(),
			sge::log::_1
				<< SGE_TEXT("A weapon's cast point interval is bigger than its cooldown!")
	);

	if(magazine_size() == 0)
		throw exception(
			SGE_TEXT("magazine size of 0 is invalid!")
		);

	initiate();
}

sanguis::server::weapons::magazine_type const
sanguis::server::weapons::weapon::unlimited_magazine(
	std::numeric_limits<magazine_type>::max()
);

sanguis::server::entities::entity &
sanguis::server::weapons::weapon::insert(
	entities::auto_ptr e)
{
	return env_.insert(e);
}

void sanguis::server::weapons::weapon::send(
	messages::auto_ptr m)
{
	env_.send(m);
}

sanguis::server::environment const &
sanguis::server::weapons::weapon::environment() const
{
	return env_;
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

void
sanguis::server::weapons::weapon::reset_magazine()
{
	magazine_used = 0;
}

void
sanguis::server::weapons::weapon::use_magazine_item()
{
	++magazine_used;
	SGE_ASSERT(magazine_used <= magazine_size());
}

bool
sanguis::server::weapons::weapon::magazine_empty() const
{
	return magazine_used == magazine_size();
}

sge::time::resolution const
sanguis::server::weapons::weapon::base_cooldown() const
{
	return base_cooldown_;
}

sge::time::resolution const
sanguis::server::weapons::weapon::cast_point() const
{
	return cast_point_;
}

sge::time::resolution const
sanguis::server::weapons::weapon::reload_time() const
{
	return reload_time_;
}

void
sanguis::server::weapons::weapon::init_attack(
	entities::entity_with_weapon &e)
{
	e.start_attacking();
	on_init_attack(e);
}

void
sanguis::server::weapons::weapon::on_init_attack(
	entities::entity_with_weapon &)
{}

void sanguis::server::weapons::weapon::on_castpoint(
	entities::entity_with_weapon &)
{}

sge::log::logger &
sanguis::server::weapons::weapon::log()
{
	static sge::log::logger log_(
		weapons::log(),
		SGE_TEXT("weapon: "),
		true
	);
	return log_;
}
