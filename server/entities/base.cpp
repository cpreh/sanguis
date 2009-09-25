#include "entity.hpp"
#include "auto_weak_link.hpp"
#include "insert_parameters.hpp"
#include "collision_groups.hpp"
#include "../collision/create_parameters.hpp"
#include "../environment/object.hpp"
#include "../get_unique_id.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/collision/world.hpp>
#include <sge/collision/shapes/circle.hpp>
#include <sge/assign/make_container.hpp>
#include <sge/assert.hpp>
#include <boost/logic/tribool.hpp>

sanguis::server::entities::base::base()
:
	collision::base(),
	environment_(),
	id_(
		get_unique_id()
	),
	angle_(0)
	links()
{}

void
sanguis::server::entities::base::transfer(
	server::environment::object_ptr const nenvironment,
	collision::global_groups const &collision_groups_,
	insert_parameters const &insert_param
)
{
	environment_ = nenvironment;

	collision::create_parameters const create_param(
		insert_param.center(),
		pos_type::null()
	);

	collision::base::recreate(
		environment_->collision_world(),
		collision_groups_,
		create_param
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
sanguis::server::entities::base::environment() const
{
	SGE_ASSERT(
		environment_
	);

	return environment_;
}

sanguis::entity_id
sanguis::server::entities::base::id() const
{
	return id_;
}

sanguis::server::space_unit
sanguis::server::entities::base::angle() const
{
	return angle_;
}

void
sanguis::server::entities::base::angle(
	space_unit const _angle
)
{
	angle_ = _angle;
}

/*
void
sanguis::server::entities::base::direction(
	space_unit const _direction
)
{
	speed_change(
		property(
			property_type::movement_speed
		).current()
	);
}
*/

sanguis::server::pos_type const
sanguis::server::entities::base::center() const
{
	return body_pos();
}

void
sanguis::server::entities::base::center(
	pos_type const &_center
)
{
	body_pos(
		_center
	);
}

sanguis::server::space_unit
sanguis::server::entities::base::speed() const
{
	return
		property(
			property_type::movement_speed
		).current();
}

void
sanguis::server::entities::base::update(
	time_type const time
)
{
	//BOOST_FOREACH(property_map::reference p, properties)
	//	p.second.reset();

	on_update(
		time
	);

	/*
	BOOST_FOREACH(property_map::reference p, properties)
		p.second.apply();
	*/

	// TODO: somehow make this part of property!
	/*
	property(property_type::attack_speed).current_to_max();
	property(property_type::reload_speed).current_to_max();
	property(property_type::health_regeneration).current_to_max();
	*/
}

sanguis::server::entities::auto_weak_link const
sanguis::server::entities::base::link()
{
	return auto_weak_link(
		*this
	);
}

sanguis::server::entities::base::~entity()
{}

sge::collision::shapes::container const
sanguis::server::entities::base::recreate_shapes(
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

sanguis::server::collision::group_vector const
sanguis::server::entities::base::collision_groups()
{
	return entities::collision_groups(
		type(),
		team()
	);
}

void
sanguis::server::entities::base::insert_link(
	auto_weak_link &link_
)
{
	links.push_back(
		link_
	);
}

boost::logic::tribool const
sanguis::server::entities::base::can_collide_with(
	collision::base const &base_
) const
{
	entity const *const other(
		dynamic_cast<
			entity const *
		>(
			&base_
		)
	);

	return other
		? can_collide_with_entity(*other)
		: boost::logic::indeterminate;
}

void
sanguis::server::entities::base::collision_begin(
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
sanguis::server::entities::base::collision_end(
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
sanguis::server::entities::base::can_collide_with_entity(
	entity const &
) const
{
	return boost::logic::indeterminate;
}

void
sanguis::server::entities::base::collision_entity_begin(
	entity &
)
{}

void
sanguis::server::entities::base::collision_entity_end(
	entity &
)
{}
