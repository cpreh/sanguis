#include "entity.hpp"
#include "log.hpp"
#include <sge/log/headers.hpp>
#include <sge/text.hpp>
#include <sge/time/second_f.hpp>
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
		sge::time::second_f(diff));
}

bool sanguis::draw::entity::may_be_removed() const
{
	return decay_timer.expired();
}

void sanguis::draw::entity::health(funit)
{}

void sanguis::draw::entity::max_health(funit)
{}

void sanguis::draw::entity::weapon(weapon_type::type)
{
	SGE_LOG_WARNING(
		log(),
		sge::log::_1 << SGE_TEXT("got a weapon message that can't have a weapon!"));
}

void sanguis::draw::entity::start_attacking()
{
	SGE_LOG_WARNING(
		log(),
		sge::log::_1 << SGE_TEXT("got a start attacking message!"));
}

void sanguis::draw::entity::stop_attacking()
{
	SGE_LOG_WARNING(
		log(),
		sge::log::_1 << SGE_TEXT("got a stop attacking message!"));
}

void sanguis::draw::entity::start_reloading()
{
	SGE_LOG_WARNING(
		log(),
		sge::log::_1 << SGE_TEXT("got a start reloading message!"));
}

void sanguis::draw::entity::stop_reloading()
{
	SGE_LOG_WARNING(
		log(),
		sge::log::_1 << SGE_TEXT("got a stop reloading message!"));
}

sanguis::draw::entity::~entity()
{}

sanguis::draw::entity::entity(
	draw::environment const &env_,
	entity_id const id_,
	draw::system &sys)
:
	env_(env_),
	id_(id_),
	sys(sys),
	diff_clock_(),
	decay_timer(
		sge::time::resolution(0),
		false,
		diff_clock_.callback())
{}

sanguis::draw::environment const &
sanguis::draw::entity::environment() const
{
	return env_;
}

sanguis::draw::system &
sanguis::draw::entity::system()
{
	return sys;
}

sge::log::logger &
sanguis::draw::entity::log()
{
	static sge::log::logger log_(
		draw::log(),
		SGE_TEXT("entity: "));
	return log_;
}
