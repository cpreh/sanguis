#include "weapon.hpp"
#include "delayed_attack.hpp"
#include "../entities/entity.hpp"
#include "../../log_headers.hpp"
#include <sge/time/second.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
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

void sanguis::server::weapons::weapon::update(
	time_type const tm,
	entities::entity const &owner)
{
	diff.update(tm);

	switch(state_) {
	case state::ready:
		return;
	case state::castpoint:
		if(!cast_point_timer.update_b())
			return;

		do_attack(
			delayed_attack(
				owner.center(),
				owner.angle(),
				owner.team(),
				*attack_dest));

		cast_point_timer.deactivate();
		attack_dest.reset();

		state_ = state::backswing;
	//	return; // fall through
	case state::backswing:
		if(!cooldown_timer.expired())
			return;

		if(magazine_used == magazine_size)
		{
			reload_timer.activate();
			state_ = state::reload;
		}
		else
		{
			++magazine_used;
			state_ = state::ready;
		}
		return;
	case state::reload:
		if(reload_timer.update_b())
		{
			reload_timer.deactivate();
			magazine_used = 0;
			state_ = state::ready;
		}
		return;
	default:
		throw sge::exception(
			SGE_TEXT("Invalid state in weapon!"));
	}

}

bool sanguis::server::weapons::weapon::attack(
	entities::entity const &from,
	pos_type const& to)
{
	if(state_ != state::ready
	|| !cooldown_timer.update_b()
	|| !in_range(from, to))
		return false;
	
	cast_point_timer.activate();
	attack_dest.reset(
		to);
	
	state_ = state::castpoint;
	return true;
}

sanguis::server::weapons::weapon::~weapon()
{}

sanguis::server::weapons::weapon::weapon(
	environment const &env_,
	weapon_type::type const type_,
	space_unit const range_,
	unsigned const magazine_size,
	time_type const base_cooldown_,
	time_type const cast_point_,
	time_type const reload_time_)
:
	diff(),
	env_(env_),
	type_(type_),
	range_(range_),
	magazine_used(0),
	magazine_size(magazine_size),
	cooldown_timer(
		sge::time::second(base_cooldown_),
		true,
		diff.callback()),
	cast_point_timer(
		sge::time::second(cast_point_),
		false,
		diff.callback()),
	reload_timer(
		sge::time::second(reload_time_),
		false,
		diff.callback()),
	state_(state::ready)
{
	if(magazine_size == 0)
		SGE_LOG_WARNING(
			log(),
			sge::log::_1
				<< SGE_TEXT("magazine sizes of 0 are meaningless and will be threated as 1."));
}

unsigned const
sanguis::server::weapons::weapon::unlimited_magazine(
	static_cast<unsigned>(-1));

void sanguis::server::weapons::weapon::send(
	messages::auto_ptr m)
{
	env_.send(m);
}

sanguis::server::environment
sanguis::server::weapons::weapon::get_environment() const
{
	return env_;
}

sanguis::server::entities::entity &
sanguis::server::weapons::weapon::insert(
	entities::auto_ptr e)
{
	return env_.insert(e);
}

bool sanguis::server::weapons::weapon::in_range(
	entities::entity const& from,
	pos_type const& to) const
{
	return (from.center() - to).length() < range();
}
