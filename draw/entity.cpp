#include "entity.hpp"
#include <sge/time/second.hpp>
#include <sge/time/resolution.hpp>
#include <sge/iostream.hpp>
#include <ostream>
	
sanguis::entity_id sanguis::draw::entity::id() const
{
	return id_;
}

void sanguis::draw::entity::decay()
{
	decay_timer.activate();
}

void sanguis::draw::entity::decay_time(
	const time_type diff)
{
	decay_timer.interval(
		sge::time::second(diff));
}

bool sanguis::draw::entity::may_be_removed() const
{
	return decay_timer.expired();
}

void sanguis::draw::entity::health(sge::space_unit)
{}

void sanguis::draw::entity::max_health(sge::space_unit)
{}

void sanguis::draw::entity::weapon(weapon_type::type)
{
	sge::clog << SGE_TEXT("warning: entity got a weapon message that can't have a weapon!\n");
}

void sanguis::draw::entity::start_attacking()
{
	sge::clog << SGE_TEXT("warning: entity got a start attacking message!\n");
}

void sanguis::draw::entity::stop_attacking()
{
	sge::clog << SGE_TEXT("warning: entity got a stop attacking message!\n");
}

sanguis::draw::entity::~entity()
{}

sanguis::draw::entity::entity(
	entity_id const id_,
	system &sys)
: id_(id_),
  sys(sys),
  decay_timer(
  	sge::time::resolution(0),
	false)
{}

sanguis::draw::system &
sanguis::draw::entity::get_system()
{
	return sys;
}
