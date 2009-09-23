#include "entity.hpp"
#include "base_parameters.hpp"
#include "auto_weak_link.hpp"
#include "property.hpp"
#include "radius.hpp"
#include "insert_parameters.hpp"
#include "collision_groups.hpp"
#include "../collision/create_parameters.hpp"
#include "../perks/perk.hpp"
#include "../buffs/buff.hpp"
#include "../auras/aura.hpp"
#include "../environment/object.hpp"
#include "../get_unique_id.hpp"
#include "../log.hpp"
#include "../../messages/add.hpp"
#include "../../messages/create.hpp"
#include "../../angle_to_vector.hpp"
#include "../../exception.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/math/vector/dim.hpp>
#include <sge/math/vector/construct.hpp>
#include <sge/math/vector/output.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/dim/arithmetic.hpp>
#include <sge/collision/body.hpp>
#include <sge/collision/world.hpp>
#include <sge/collision/shapes/circle.hpp>
#include <sge/container/linear_set_impl.hpp>
#include <sge/container/map_impl.hpp>
#include <sge/assign/make_container.hpp>
#include <sge/log/headers.hpp>
#include <sge/text.hpp>
#include <sge/assert.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/foreach.hpp>
#include <boost/bind.hpp>

sanguis::server::entities::entity::entity(
	base_parameters const &param
)
:
	collision::base(
		collision_groups(
			param.type(),
			param.team()
		)
	),
	environment_(),
	load_context_(param.load_context()),
	id_(get_unique_id()),
	armor_(param.armor()),
	angle_(0),
	direction_(0),
	team_(param.team()),
	properties(param.properties()),
	type_(param.type()),
	invulnerable_(param.invulnerable()),
	collision_dim(param.collision_dim()),
	update_health_(true),
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
	),
	health_change_(
		property(
			property_type::health
		).register_change_callback(
			boost::bind(
				&entity::health_change,
				this,
				_1
			)
		)
	),
	max_health_change_(
		property(
			property_type::health
		).register_max_change_callback(
			boost::bind(
				&entity::max_health_change,
				this,
				_1
			)
		)
	),
	perks_(),
	buffs_(),
	auras_(),
	links()
{}

void
sanguis::server::entities::entity::transfer(
	server::environment::object_ptr const nenvironment,
	collision::global_groups const &collision_groups_,
	insert_parameters const &insert_param
)
{
	environment_ = nenvironment;

	collision::create_parameters const create_param(
		insert_param.center(),
		angle_to_vector(
			direction()
		)
		* property(
			property_type::movement_speed
		).current()
	);
		
	collision::base::recreate(
		environment_->collision_world(),
		collision_groups_,
		create_param
	);

	direction(
		insert_param.direction()
	);

	angle(
		insert_param.angle()
	);

	BOOST_FOREACH(
		aura_container::reference aura_,
		auras_
	)
		aura_.recreate(
			environment_->collision_world(),
			collision_groups_,
			create_param
		);
}

sanguis::server::environment::object_ptr const
sanguis::server::entities::entity::environment() const
{
	SGE_ASSERT(
		environment_
	);

	return environment_;
}

sanguis::server::environment::load_context_ptr const
sanguis::server::entities::entity::load_context() const
{
	return load_context_;
}

sanguis::entity_id
sanguis::server::entities::entity::id() const
{
	return id_;
}

sanguis::server::pos_type const
sanguis::server::entities::entity::pos() const
{
	return center() - dim() / static_cast<space_unit>(2);
}

sanguis::server::space_unit
sanguis::server::entities::entity::angle() const
{
	return angle_;
}

void
sanguis::server::entities::entity::angle(
	space_unit const _angle
)
{
	angle_ = _angle;
}

sanguis::server::space_unit
sanguis::server::entities::entity::direction() const
{
	return direction_;
}

void
sanguis::server::entities::entity::direction(
	space_unit const _direction
)
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
	return body_pos();
}

void
sanguis::server::entities::entity::center(
	pos_type const &_center
)
{
	body_pos(
		_center
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
	return body_speed();
}

sanguis::server::space_unit
sanguis::server::entities::entity::speed() const
{
	return
		property(
			property_type::movement_speed
		).current();
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

void
sanguis::server::entities::entity::damage(
	space_unit const d,
	damage::array const &damages
)
{
	for(
		damage::array::size_type i = 0;
		i < damages.size();
		++i
	)
		health(
			health() - d * damages[i] * (1 - armor_[i])
		);

	if(dead())
		die();
}

bool sanguis::server::entities::entity::dead() const
{
	return health() <= static_cast<space_unit>(0);
}

void sanguis::server::entities::entity::die()
{
	health(static_cast<space_unit>(0));
	on_die();
}

sanguis::server::damage::armor const &
sanguis::server::entities::entity::armor() const
{
	return armor_;
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
	time_type const time
)
{
	BOOST_FOREACH(property_map::reference p, properties)
		p.second.reset();

	BOOST_FOREACH(perk_container::reference p, perks_)
		p.second->apply(
			*this,
			time,
			environment(),
			load_context()
		);

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

	BOOST_FOREACH(property_map::reference p, properties)
		p.second.apply();

	// TODO: somehow make this part of property!
	property(property_type::attack_speed).current_to_max();
	property(property_type::reload_speed).current_to_max();
	property(property_type::health_regeneration).current_to_max();

	property(property_type::health).add(
		property(property_type::health_regeneration).current() * time
	);
}

void sanguis::server::entities::entity::add_perk(
	perks::auto_ptr p)
{
	perk_type::type const type_(
		p->type()
	);

	perk_container::iterator it(
		perks_.find(
			type_
		)
	);

	if(it != perks_.end())
	{
		perks::perk &perk_(
			*it->second
		);

		if(perk_.can_raise_level())
			perk_.raise_level();
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

	perks_.insert(
		type_,
		p
	);
}

sanguis::messages::auto_ptr
sanguis::server::entities::entity::add_message() const
{
	return messages::create(
		messages::add(
			id(),
			pos(),
			angle(),
			abs_speed(),
			health(),
			max_health(),
			dim(),
			type()
		)
	);
}

sanguis::server::entities::auto_weak_link const
sanguis::server::entities::entity::link()
{
	return auto_weak_link(
		*this
	);
}

void
sanguis::server::entities::entity::add_buff(
	buffs::auto_ptr b
)
{
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

	ref.owner(
		id()
	);
}

bool
sanguis::server::entities::entity::update_health() const
{
	bool const ret = update_health_;
	update_health_ = false;
	return ret;
}

sanguis::server::entities::entity::~entity()
{}

bool
sanguis::server::entities::entity::perk_choosable(
	perk_type::type const pt) const
{
	perk_container::const_iterator const it(
		perks_.find(
			pt
		)
	);

	return it == perks_.end()
		|| it->second->can_raise_level();
}

void
sanguis::server::entities::entity::on_die()
{}

sge::collision::shapes::container const
sanguis::server::entities::entity::recreate_shapes(
	sge::collision::world_ptr const world_
) const
{
	return
		sge::assign::make_container<
			sge::collision::shapes::container
		>(
			world_->create_circle(
				radius()
			)
		);
}

void
sanguis::server::entities::entity::on_destroy()
{
	BOOST_FOREACH(
		aura_container::reference aura_,
		auras_
	)
		aura_.destroy();
}

void
sanguis::server::entities::entity::insert_link(
	auto_weak_link &l)
{
	links.push_back(l);
}

void
sanguis::server::entities::entity::speed_change(
	property::value_type const s
)
{
	body_speed(
		angle_to_vector(
			direction()
		) * s
	);
}

void sanguis::server::entities::entity::health_change(
	property::value_type)
{
	update_health_ = true;
}

void sanguis::server::entities::entity::max_health_change(
	property::value_type)
{
	update_health_ = true;

	environment()->max_health_changed(
		id(),
		max_health()
	);
}

boost::logic::tribool const
sanguis::server::entities::entity::can_collide_with(
	collision::base const &b
) const
{
	entity const *const other(
		dynamic_cast<entity const *>(&b)
	);

	return other
		? can_collide_with_entity(*other)
		: boost::logic::indeterminate;
}

void
sanguis::server::entities::entity::collision_begin(
	collision::base &b
)
{
	entity *const other(
		dynamic_cast<entity *>(&b)
	);

	if(other)
		collision_entity_begin(
			*other
		);
}

void
sanguis::server::entities::entity::collision_end(
	collision::base &b
)
{
	entity *const other(
		dynamic_cast<entity *>(&b)
	);

	if(other)
		collision_entity_end(
			*other
		);
}

boost::logic::tribool const
sanguis::server::entities::entity::can_collide_with_entity(
	entity const &
) const
{
	return boost::logic::indeterminate;
}

void
sanguis::server::entities::entity::collision_entity_begin(
	entity &
)
{}

void
sanguis::server::entities::entity::collision_entity_end(
	entity &
)
{}
