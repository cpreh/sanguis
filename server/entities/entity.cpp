#include "entity.hpp"
#include "sattelite.hpp"
#include "base_parameters.hpp"
#include "auto_weak_link.hpp"
#include "property.hpp"
#include "../perks/perk.hpp"
#include "../get_unique_id.hpp"
#include "../message_converter.hpp"
#include "../../messages/add.hpp"
#include "../../angle_vector.hpp"
#include "../../exception.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/dim/arithmetic.hpp>
#include <sge/math/power.hpp>
#include <sge/collision/system.hpp>
#include <sge/collision/object.hpp>
#include <sge/container/linear_set_impl.hpp>
#include <sge/text.hpp>
#include <boost/foreach.hpp>
#include <boost/bind.hpp>
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
	aggressive_(false),
	collision_(
		environment().collision->create_circle(
			sge::collision::sattelite_ptr(
				new sattelite(*this)),
			static_cast<sge::collision::unit>(
				radius()))),
	speed_change_(
		property(
			property_type::movement_speed).register_change_callback(
				boost::bind(&entity::speed_change,this,_1)))
{
	center(center_);
}

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
	collision_->speed(
		sge::math::structure_cast<sge::collision::unit>(
			abs_speed()));
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
	collision_->pos(sge::math::structure_cast<sge::collision::unit>(_center));
}

void sanguis::server::entities::entity::collision_update(
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
	return property(
		property_type::movement_speed).current();
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
	return property(property_type::health).current();
}

void sanguis::server::entities::entity::health(
	health_type const nhealth)
{
	property(property_type::health).current(nhealth);
}

sanguis::server::health_type
sanguis::server::entities::entity::max_health() const
{
	return property(property_type::health).max();
}

sanguis::server::entities::property const &
sanguis::server::entities::entity::property(
	property_type::type const e) const
{
	return const_cast<entity &>(*this).property(e);
}

sanguis::server::entities::property &
sanguis::server::entities::entity::property(
	property_type::type const e)
{
	return properties[e];
	// TODO: should this signal an error because it might be
	// rather error prone to default initialise properties
	// for example if health == 0 the entity is dead immedeately
	/*property_map::iterator const it = properties.find(e);

	if (it == properties.end())
		throw exception(
			SGE_TEXT("couldn't find specified entity property"));
	
	return it->second;*/
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
	//center_ += abs_speed() * delta;

	BOOST_FOREACH(property_map::reference p, properties)
		p.second.reset();

	BOOST_FOREACH(perks::perk &p, perks_)
		p.apply(*this);

	BOOST_FOREACH(property_map::reference p, properties)
		p.second.apply();
}

void sanguis::server::entities::entity::add_perk(
	perks::auto_ptr p)
{
	// check, if we already have such a perk
	BOOST_FOREACH(perks::perk &i, perks_)
	{
		if(typeid(i) == typeid(*p))
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

sanguis::server::entities::auto_weak_link
sanguis::server::entities::entity::link(
	entity &e)
{
	if(!links.insert(&e).second)
		throw exception(
			SGE_TEXT("Double link insert in entity!"));
	
	try
	{
		if(!e.backlinks.insert(this).second)
			throw exception(
				SGE_TEXT("Double backlink insert in entity!"));
	}
	catch(...)
	{
		// TODO: can we wrap this in a RAII class somehow?
		links.erase(&e);
		throw;
	}

	return auto_weak_link(
		*this,
		e);
}

bool sanguis::server::entities::entity::can_collide_with(
	entity const &) const
{
	return false;
}

void sanguis::server::entities::entity::collision(
	entity &)
{
}

sanguis::server::entities::entity::~entity()
{
	BOOST_FOREACH(entity *e, links)
		e->backlinks.erase(this);

	BOOST_FOREACH(entity *e, backlinks)
		e->links.erase(this);
}

void sanguis::server::entities::entity::send(
	messages::auto_ptr message)
{
	environment().send(
		messages::auto_ptr(
			message));
}

sanguis::server::environment const &
sanguis::server::entities::entity::environment() const
{
	return env_;
}

sanguis::server::entities::entity &
sanguis::server::entities::entity::insert(
	auto_ptr e)
{
	return environment().insert(e);
}

void sanguis::server::entities::entity::on_die()
{}

void sanguis::server::entities::entity::unlink(
	entity * const e)
{
	if(!has_ref(e))
		return;
	e->backlinks.erase(this);
	links.erase(e);
}

bool sanguis::server::entities::entity::has_ref(
	entity *const e) const
{
	return links.find(e) != links.end();
}

void sanguis::server::entities::entity::speed_change(
	property::value_type const v)
{
	direction(direction());
}
