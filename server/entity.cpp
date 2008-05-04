#include "entity.hpp"
#include "get_unique_id.hpp"
#include "../angle_vector.hpp"
#include <sge/math/vec_dim.hpp>
#include <sge/math/power.hpp>
#include <sge/math/compare.hpp>
#include <sge/iostream.hpp>
#include <boost/foreach.hpp>
#include <algorithm>
#include <ostream>
#include <typeinfo>
#include <cmath>

sanguis::server::entity::entity(
	const environment &env_,
	const armor_array &armor_,
	const messages::pos_type &pos_,
	const messages::space_unit angle_,
	const messages::space_unit direction_,
	const team::type team_,
	const property_map properties)
: id_(get_unique_id()),
	env_(env_),
  pos_(pos_),
  angle_(angle_),
  direction_(direction_),
  team_(team_),
	armor_(armor_),
  attacking_(false),
  aggressive_(false),
	properties(properties)
{}

const sanguis::armor_array &sanguis::server::entity::armor() const
{
	return armor_;
}

const sanguis::armor_array &sanguis::server::entity::armor_diff() const
{
	return armor_diff_;
}

sanguis::armor_array &sanguis::server::entity::armor_diff()
{
	return armor_diff_;
}

bool sanguis::server::entity::attacking() const
{
	return attacking_;
}

void sanguis::server::entity::attacking(const bool n)
{
	attacking_ = n;
}

bool sanguis::server::entity::aggressive() const
{
	return aggressive_;
}

void sanguis::server::entity::aggressive(const bool n)
{
	aggressive_ = n;
}

sanguis::entity_id sanguis::server::entity::id() const
{
	return id_;
}

sanguis::server::team::type sanguis::server::entity::team() const
{
	return team_;
}

sanguis::messages::pos_type sanguis::server::entity::center() const
{
	return pos() + dim()/messages::mu(2);
}

void sanguis::server::entity::pos(const messages::pos_type _pos) 
{ 
	pos_ = _pos;
}

sanguis::messages::pos_type sanguis::server::entity::pos() const
{
	return pos_;
}

sanguis::messages::pos_type sanguis::server::entity::abs_speed() const
{
	return angle_to_vector(direction_) * get_property(property::type::speed).abs_current();
}

sanguis::messages::space_unit sanguis::server::entity::radius() const
{
	return std::sqrt(
		sge::math::quad(center().x() - pos().x())
		+ sge::math::quad(center().y() - pos().y()));
}

sanguis::messages::space_unit sanguis::server::entity::angle() const
{
	return angle_;
}

void sanguis::server::entity::angle(const messages::space_unit _angle)
{
	angle_ = _angle;
}

sanguis::messages::space_unit sanguis::server::entity::direction() const
{
	return direction_;
}

void sanguis::server::entity::damage(
	const messages::space_unit d,
	damage_array const& damages)
{
	if(!sge::math::compare(
		std::accumulate(
			damages.begin(),
			damages.end(),
			messages::mu(0)),
		messages::mu(1))
	)
		sge::clog << SGE_TEXT("Damage values don't equal 1. Check this!\n");
	
	property &health = get_property(property::type::health);
	for(damage_array::size_type i = 0; i < damages.size(); ++i)
		health.current(health.current() - d * damages[i] * (1 - armor_[i]));

	if(dead())
		die();
	// TODO: send health here!
}

bool sanguis::server::entity::dead() const
{
	return get_property(property::type::health).current() <= messages::mu(0);
}

void sanguis::server::entity::die()
{
	get_property(property::type::health).current(messages::mu(0));
	get_environment().exp(exp());
}

void sanguis::server::entity::update(
	const time_type delta,
	entity_container &)
{
	pos_ += abs_speed() * delta;
}

void sanguis::server::entity::direction(const messages::space_unit _direction)
{
	direction_ = _direction;
}

void sanguis::server::entity::add_perk(
	perks::perk_auto_ptr p)
{
	// check, if we already have such a perk
	BOOST_FOREACH(perks::perk &i, perks_)
	{
		if(typeid(i) == typeid(p))
		{
			i.raise_level();
			return;
		}
	}
	perks_.push_back(p);
	perks_.back().activate(*this);
}

sanguis::server::entity::~entity()
{}

void sanguis::server::entity::send(
	messages::base *const message)
{
	get_environment().send(message);
}

const sanguis::server::environment &sanguis::server::entity::get_environment() const
{
	return env_;
}

sanguis::server::entity &sanguis::server::entity::insert(
	entity_ptr e)
{
	return get_environment().insert(e);
}

sanguis::messages::exp_type sanguis::server::entity::exp() const
{
	return static_cast<messages::exp_type>(0);
}

sanguis::server::entity::property::property(
	const value_type min_,
	const value_type max_,
	const value_type base_,
	const value_type current_)
	: min_(min_),
	  max_(max_),
		base_(base_),
		current_(current_)
{}

sanguis::server::entity::property::value_type sanguis::server::entity::property::min() const
{
	return min_;
}

sanguis::server::entity::property::value_type sanguis::server::entity::property::max() const
{
	return max_;
}

sanguis::server::entity::property::value_type sanguis::server::entity::property::base() const
{
	return base_;
}

sanguis::server::entity::property::value_type sanguis::server::entity::property::current() const
{
	return current_;
}

sanguis::server::entity::property::value_type sanguis::server::entity::property::abs_current() const
{
	return min() + (max() - min()) * current();
}

sanguis::server::entity::property::value_type sanguis::server::entity::property::abs_base() const
{
	return min() + (max() - min()) * base();
}

void sanguis::server::entity::property::min(const value_type _min)
{
	min_ = _min;
}

void sanguis::server::entity::property::max(const value_type _max)
{
	max_ = _max;
}

void sanguis::server::entity::property::current(const value_type _current)
{
	current_ = _current;
}

const sanguis::server::entity::property &sanguis::server::entity::get_property(const property::type::enum_type e) const
{
	return const_cast<entity &>(*this).get_property(e);
}

sanguis::server::entity::property &sanguis::server::entity::get_property(const property::type::enum_type e)
{
	property_map::iterator it = properties.find(e);

	if (it == properties.end())
		throw sge::exception(SGE_TEXT("couldn't find specified entity property"));
	
	return it->second;
}
