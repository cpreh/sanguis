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
	id_(get_unique_id()),
	angle_(0),
	direction_(0),
	properties(param.properties()),
	collision_dim(param.collision_dim()),
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

	on_transfer(
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

void sanguis::server::entities::entity::update(
	time_type const time
)
{
	BOOST_FOREACH(property_map::reference p, properties)
		p.second.reset();

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

bool
sanguis::server::entities::entity::update_health() const
{
	bool const ret = update_health_;
	update_health_ = false;
	return ret;
}

sanguis::server::entities::entity::~entity()
{}

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
sanguis::server::entities::entity::insert_link(
	auto_weak_link &l
)
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

void
sanguis::server::entities::entity::max_health_change(
	property::value_type
)
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
