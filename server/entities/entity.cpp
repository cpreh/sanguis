#include "entity.hpp"
#include "base_parameters.hpp"
#include "auto_weak_link.hpp"
#include "property.hpp"
#include "radius.hpp"
#include "../perks/perk.hpp"
#include "../buffs/buff.hpp"
#include "../auras/aura.hpp"
#include "../get_unique_id.hpp"
#include "../log.hpp"
#include "../message_converter.hpp"
#include "../../messages/add.hpp"
#include "../../angle_vector.hpp"
#include "../../exception.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/math/vector/dim.hpp>
#include <sge/math/vector/construct.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/dim/arithmetic.hpp>
#include <sge/collision/world.hpp>
#include <sge/collision/objects/circle.hpp>
#include <sge/container/linear_set_impl.hpp>
#include <sge/container/map_impl.hpp>
#include <sge/math/vector/output.hpp>
#include <sge/log/headers.hpp>
#include <sge/text.hpp>
#include <boost/foreach.hpp>
#include <boost/bind.hpp>
#include <typeinfo>

sanguis::server::entities::entity::entity(
	base_parameters const &param)
:
	collision::base(
		param.env().collision(),
		param.center(),
		angle_to_vector(
			param.direction() // TODO: is this right?
		) * param.properties()[
			property_type::movement_speed
		].current(),
		entities::radius(
			param.collision_dim()
		)
	),
	id_(get_unique_id()),
	env_(param.env()),
	armor_(param.armor()),
	angle_(param.angle()),
	direction_(param.direction()),
	team_(param.team()),
	properties(param.properties()),
	type_(param.type()),
	invulnerable_(param.invulnerable()),
	collision_dim(param.collision_dim()),
	aggressive_(false),
	speed_change_(
		property(
			property_type::movement_speed
		).register_change_callback(
			boost::bind(
				&entity::speed_change,
				this,
				_1
			)
		)
	)
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
	speed_change(
		property(
			property_type::movement_speed
		).current()
	);
}

sanguis::server::pos_type const
sanguis::server::entities::entity::center() const
{
	return pos_type(
		circle()->center().x(),
		circle()->center().y()
	);
}


void sanguis::server::entities::entity::center(
	pos_type const &_center)
{
	circle()->center(
		sge::math::vector::construct(
			_center,
			static_cast<
				space_unit
			>(0)
		)
	);

	BOOST_FOREACH(
		aura_container::reference r,
		auras_
	)
		r.center(
			_center
		);
}

sanguis::server::pos_type const
sanguis::server::entities::entity::abs_speed() const
{
	// TODO: make a conversion function for this!
	return pos_type(
		circle()->speed().x(),
		circle()->speed().y()
	);
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
	return entities::radius(
		dim()
	);
}

sanguis::server::team::type
sanguis::server::entities::entity::team() const
{
	return team_;
}

void sanguis::server::entities::entity::damage(
	space_unit const d,
	damage_array const &damages)
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
	time_type const time,
	container &)
{
	BOOST_FOREACH(property_map::reference p, properties)
		p.second.reset();

	BOOST_FOREACH(perks::perk &p, perks_)
		p.apply(
			*this,
			time,
			environment()
		);

	BOOST_FOREACH(property_map::reference p, properties)
		p.second.apply();

	for(
		buff_container::iterator it(buffs_.begin());
		it != buffs_.end();
	)
	{
		it->update(
			*this,
			time
		);

		if(it->expired())
			it = buffs_.erase(it);
		else
			++it;
	}
}

void sanguis::server::entities::entity::add_perk(
	perks::auto_ptr p)
{
	// check, if we already have such a perk
	BOOST_FOREACH(perks::perk &i, perks_)
	{
		if(typeid(i) == typeid(*p))
		{
			if(i.can_raise_level())
				i.raise_level();
			else
			{
				SGE_LOG_WARNING(
					log(),
					sge::log::_1
						<< SGE_TEXT("Tried to raise perk level of a perk which can't do this.")
				);
			}
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

void
sanguis::server::entities::entity::add_buff(
	buffs::auto_ptr b)
{
	BOOST_FOREACH(
		buff_container::const_reference r,
		buffs_
	)
		if(!r.stacks(*b) || b->stacks(r))
			return;
	
	buffs_.push_back(b);
}

void
sanguis::server::entities::entity::add_aura(
	auras::auto_ptr a)
{
	auras_.push_back(a);

	auras::aura &ref(
		auras_.back()
	);

	ref.center(
		center()
	);

	ref.owner(
		id()
	);
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
	property::value_type const s)
{
	circle()->speed(
		sge::math::vector::construct(
			angle_to_vector(
				direction()
			) * s,
			static_cast<
				space_unit
			>(0)
		)
	);
}

bool
sanguis::server::entities::entity::can_collide_with(
	collision::base const &b) const
{
	entity const *const other(
		dynamic_cast<entity const *>(&b)
	);

	return other
		? can_collide_with(*other)
		: false;
}

void
sanguis::server::entities::entity::collision(
	collision::base &b)
{
	entity *const other(
		dynamic_cast<entity *>(&b)
	);

	if(other)
		collision(
			*other
		);
}

bool
sanguis::server::entities::entity::can_collide_with(
	entity const &) const
{
	return false;
}

void
sanguis::server::entities::entity::collision(
	entity &)
{
}
