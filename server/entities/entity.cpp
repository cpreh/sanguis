#include "entity.hpp"
#include "base_parameters.hpp"
#include "../get_unique_id.hpp"
#include "../message_converter.hpp"
#include "../../messages/add.hpp"
#include "../../angle_vector.hpp"
#include <sge/math/vec_dim.hpp>
#include <sge/math/power.hpp>
#include <boost/foreach.hpp>
#include <typeinfo>
#include <cmath>

sanguis::server::entities::entity::entity(
	base_parameters const &param)
:
	id_(get_unique_id()),
	env_(param.env()),
	armor_(param.armor()),
	center_(param.center()),
	angle_(param.angle()),
	direction_(param.direction()),
	team_(param.team()),
	properties(param.properties()),
	type_(param.type()),
	invulnerable_(param.invulnerable()),
	collision_dim(param.collision_dim()),
	attacking_(false),
	aggressive_(false)
{}

sanguis::entity_id
sanguis::server::entities::entity::id() const
{
	return id_;
}

sanguis::server::pos_type const
sanguis::server::entities::entity::pos() const
{
	return center() - dim() / messages::mu(2);
}

void sanguis::server::entities::entity::pos(
	pos_type const &p) 
{ 
	center(
		p + dim() / messages::mu(2));
}

sanguis::server::space_unit
sanguis::server::entities::entity::angle() const
{
	return angle_;
}

void sanguis::server::entities::entity::angle(
	space_unit const _angle)
{
	angle_ = _angle;
}

sanguis::server::space_unit
sanguis::server::entities::entity::direction() const
{
	return direction_;
}

void sanguis::server::entities::entity::direction(
	space_unit const _direction)
{
	direction_ = _direction;
}

sanguis::server::pos_type const
sanguis::server::entities::entity::center() const
{
	return center_;
}

void sanguis::server::entities::entity::center(
	pos_type const &_center)
{
	center_ = _center;
}

sanguis::server::pos_type const
sanguis::server::entities::entity::abs_speed() const
{
	return angle_to_vector(direction_) * speed();
}

sanguis::server::space_unit
sanguis::server::entities::entity::speed() const
{
	return get_property(property::type::movement_speed).current();
}

sanguis::server::space_unit
sanguis::server::entities::entity::radius() const
{
	return std::sqrt(
		sge::math::quad(center().x() - pos().x())
		+ sge::math::quad(center().y() - pos().y()));
}

sanguis::server::team::type
sanguis::server::entities::entity::team() const
{
	return team_;
}

void sanguis::server::entities::entity::damage(
	space_unit const d,
	damage_array const& damages)
{
	for(damage_array::size_type i = 0; i < damages.size(); ++i)
		health(health() - d * damages[i] * (1 - armor_[i]));

	if(dead())
		die();
	// TODO: send health here!
}

bool sanguis::server::entities::entity::dead() const
{
	return health() <= messages::mu(0);
}

void sanguis::server::entities::entity::die()
{
	health(messages::mu(0));
	on_die();
}

sanguis::armor_array const &
sanguis::server::entities::entity::armor() const
{
	return armor_;
}

sanguis::armor_array const &
sanguis::server::entities::entity::armor_diff() const
{
	return armor_diff_;
}

sanguis::armor_array &
sanguis::server::entities::entity::armor_diff()
{
	return armor_diff_;
}

bool sanguis::server::entities::entity::attacking() const
{
	return attacking_;
}

void sanguis::server::entities::entity::attacking(
	bool const n)
{
	attacking_ = n;
}

bool sanguis::server::entities::entity::aggressive() const
{
	return aggressive_;
}

void sanguis::server::entities::entity::aggressive(
	bool const n)
{
	aggressive_ = n;
}

sanguis::server::health_type
sanguis::server::entities::entity::health() const
{
	return get_property(property::type::health).current();
}

void sanguis::server::entities::entity::health(
	health_type const nhealth)
{
	get_property(property::type::health).current(nhealth);
}

sanguis::server::health_type
sanguis::server::entities::entity::max_health() const
{
	return get_property(property::type::health).max();
}

sanguis::server::entities::property const &
sanguis::server::entities::entity::get_property(
	property::type::enum_type const e) const
{
	return const_cast<entity &>(*this).get_property(e);
}

sanguis::server::entities::property &
sanguis::server::entities::entity::get_property(
	property::type::enum_type const e)
{
	property_map::iterator const it = properties.find(e);

	if (it == properties.end())
		throw sge::exception(
			SGE_TEXT("couldn't find specified entity property"));
	
	return it->second;
}

sanguis::server::exp_type
sanguis::server::entities::entity::exp() const
{
	return static_cast<exp_type>(0);
}

sanguis::server::dim_type const
sanguis::server::entities::entity::dim() const
{
	return collision_dim;
}

sanguis::entity_type::type
sanguis::server::entities::entity::type() const
{
	return type_;
}

bool sanguis::server::entities::entity::invulnerable() const
{
	return invulnerable_;
}

void sanguis::server::entities::entity::update(
	time_type const delta,
	container &)
{
	center_ += abs_speed() * delta;

	BOOST_FOREACH(property_map::value_type &p, properties)
		p.second.reset_max_to_base();

	BOOST_FOREACH(perks::perk &p, perks_)
		p.apply(*this);
}

void sanguis::server::entities::entity::add_perk(
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
}

sanguis::messages::auto_ptr
sanguis::server::entities::entity::add_message() const
{
	return message_convert<messages::add>(*this);
}

sanguis::server::entities::entity::~entity()
{}

void sanguis::server::entities::entity::send(
	messages::auto_ptr message)
{
	get_environment().send(
		messages::auto_ptr(
			message));
}

sanguis::server::environment const &
sanguis::server::entities::entity::get_environment() const
{
	return env_;
}

sanguis::server::entities::entity &
sanguis::server::entities::entity::insert(
	auto_ptr e)
{
	return get_environment().insert(e);
}

void sanguis::server::entities::entity::on_die()
{}
