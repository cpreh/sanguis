#include "weapon.hpp"
#include "delayed_attack.hpp"
#include "log.hpp"
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
#include <ostream>
#include <cassert>

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
	entities::entity_with_weapon &owner)
{
	assert(magazine_used <= magazine_size());

	diff.update(tm);
	ias_diff.update(tm * ias);

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

		on_castpoint(
			owner);
		
		state_ = state::backswing;
		// fall through
	case state::backswing:
		if(!cooldown_timer.expired())
			return;

		if(magazine_size() != unlimited_magazine)
			++magazine_used;

		if(magazine_used < magazine_size())
		{
			state_ = state::ready;
			return;
		}

		assert(magazine_size() != unlimited_magazine);

		reload_timer.activate();
		state_ = state::reload;
		// fall through
	case state::reload:
		if(reload_timer.update_b())
		{
			reload_timer.deactivate();
			magazine_used = 0;
			state_ = state::ready;
		}
		return;
	default:
		throw exception(
			SGE_TEXT("Invalid state in weapon!"));
	}
}

bool sanguis::server::weapons::weapon::attack(
	entities::entity_with_weapon &from,
	pos_type const &to)
{
	if(state_ != state::ready
	|| !cooldown_timer.update_b()
	|| !in_range(from, to))
		return false;
	
	cast_point_timer.activate();
	attack_dest.reset(
		to);
	
	on_init_attack(
		from);

	state_ = state::castpoint;
	return true;
}

bool sanguis::server::weapons::weapon::ready() const
{
	return state_ == state::ready;
}

bool sanguis::server::weapons::weapon::reloading() const
{
	return reload_timer.active();	
}

unsigned sanguis::server::weapons::weapon::magazine_size() const
{
	return magazine_size_;
}

bool sanguis::server::weapons::weapon::in_range(
	entities::entity const &from,
	pos_type const &to) const
{
	return collision::distance(from, to) - collision::bounding_circle(from).radius() < range();
}

void sanguis::server::weapons::weapon::attack_speed(
	space_unit const speed)
{
	ias = speed;
}

sanguis::server::weapons::weapon::~weapon()
{}

sanguis::server::weapons::weapon::weapon(
	server::environment const &env_,
	weapon_type::type const type_,
	space_unit const range_,
	unsigned const magazine_size_,
	time_type const base_cooldown_,
	time_type const cast_point_,
	time_type const reload_time_)
:
	diff(),
	ias_diff(),
	env_(env_),
	type_(type_),
	range_(range_),
	magazine_used(0),
	magazine_size_(magazine_size_),
	cooldown_timer(
		sge::time::second_f(
			base_cooldown_),
		sge::time::activation_state::active,
		ias_diff.callback()),
	cast_point_timer(
		sge::time::second_f(
			cast_point_),
		sge::time::activation_state::inactive,
		ias_diff.callback()),
	reload_timer(
		sge::time::second_f(
			reload_time_),
		sge::time::activation_state::inactive,
		diff.callback()),
	state_(state::ready),
	ias(static_cast<space_unit>(0)),
	attack_dest()
{
	if(cast_point_timer.interval() > cooldown_timer.interval())
		SGE_LOG_WARNING(
			log(),
			sge::log::_1
				<< SGE_TEXT("A weapon's cast point interval is bigger than its cooldown!"));

	if(magazine_size() == 0)
		throw exception(
			SGE_TEXT("magazine size of 0 is invalid!"));
}

unsigned const
sanguis::server::weapons::weapon::unlimited_magazine(
	static_cast<unsigned>(-1));

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

sanguis::server::entities::entity &
sanguis::server::weapons::weapon::insert(
	entities::auto_ptr e)
{
	return env_.insert(e);
}

void sanguis::server::weapons::weapon::on_init_attack(
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
