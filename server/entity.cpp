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
	const messages::space_unit health_,
	const messages::space_unit max_health_,
	const team::type team_,
	const messages::space_unit speed_,
	const messages::space_unit max_speed_)
: id_(get_unique_id()),
	env_(env_),
  pos_(pos_),
  speed_(speed_),
  max_speed_(max_speed_),
  angle_(angle_),
  direction_(direction_),
  health_(health_),
  max_health_(max_health_),
  team_(team_),
	armor_(armor_),
  attacking_(false),
  aggressive_(false)
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
	return angle_to_vector(direction_) * speed_ * max_speed();
}

sanguis::messages::space_unit sanguis::server::entity::radius() const
{
	return std::sqrt(
		sge::math::quad(center().x() - pos().x())
		+ sge::math::quad(center().y() - pos().y()));
}

sanguis::messages::space_unit sanguis::server::entity::speed() const
{
	return speed_;
}

void sanguis::server::entity::speed(const messages::space_unit _speed)
{
	speed_ = _speed;
}

sanguis::messages::space_unit sanguis::server::entity::angle() const
{
	return angle_;
}

void sanguis::server::entity::angle(const messages::space_unit _angle)
{
	angle_ = _angle;
}

sanguis::messages::space_unit sanguis::server::entity::max_speed() const
{
	return max_speed_;
}

void sanguis::server::entity::max_speed(const messages::space_unit _max_speed)
{
	max_speed_ = _max_speed;
}

sanguis::messages::space_unit sanguis::server::entity::max_health() const
{
	return max_health_;
}

void sanguis::server::entity::max_health(const messages::space_unit _max_health)
{
	max_health_ = _max_health;
}

sanguis::messages::space_unit sanguis::server::entity::health() const
{
	return health_;
}

void sanguis::server::entity::health(const messages::space_unit _health)
{
	health_ = _health;
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
	for(damage_array::size_type i = 0; i < damages.size(); ++i)
		health_ -= d * damages[i] * (1 - armor_[i]);

	if(dead())
		die();
	// TODO: send health here!
}

bool sanguis::server::entity::dead() const
{
	return health() <= messages::mu(0);
}

void sanguis::server::entity::die()
{
	health(messages::mu(0));
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
