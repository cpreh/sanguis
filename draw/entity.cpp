#include "entity.hpp"
#include "../log_headers.hpp"
#include <sge/time/second.hpp>
#include <sge/time/resolution.hpp>

void sanguis::draw::entity::update(
	time_type const time)
{
	diff_clock_.update(time);
}

sanguis::entity_id sanguis::draw::entity::id() const
{
	return id_;
}

void sanguis::draw::entity::decay()
{
	decay_timer.activate();
}

void sanguis::draw::entity::decay_time(
	time_type const diff)
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
	SGE_LOG_WARNING(
		log(),
		sge::log::_1 << SGE_TEXT("entity got a weapon message that can't have a weapon!"));
}

void sanguis::draw::entity::start_attacking()
{
	SGE_LOG_WARNING(
		log(),
		sge::log::_1 << SGE_TEXT("entity got a start attacking message!"));
}

void sanguis::draw::entity::stop_attacking()
{
	SGE_LOG_WARNING(
		log(),
		sge::log::_1 << SGE_TEXT("entity got a stop attacking message!"));
}

void sanguis::draw::entity::start_reloading()
{
	SGE_LOG_WARNING(
		log(),
		sge::log::_1 << SGE_TEXT("entity got a start reloading message!"));
}

void sanguis::draw::entity::stop_reloading()
{
	SGE_LOG_WARNING(
		log(),
		sge::log::_1 << SGE_TEXT("entity got a stop reloading message!"));
}

sanguis::draw::entity::~entity()
{}

sanguis::draw::entity::entity(
	entity_id const id_,
	system &sys)
:
	id_(id_),
	sys(sys),
	diff_clock_(),
	decay_timer(
		sge::time::resolution(0),
		false,
		diff_clock_.callback())
{}

sanguis::draw::system &
sanguis::draw::entity::get_system()
{
	return sys;
}
