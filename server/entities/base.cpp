#include "base.hpp"
#include "auto_weak_link.hpp"
#include "insert_parameters.hpp"
#include "collision_groups.hpp"
#include "../collision/create_parameters.hpp"
#include "../environment/object.hpp"
#include "../get_unique_id.hpp"
#include <fcppt/math/vector/basic_impl.hpp>
#include <sge/collision/world.hpp>
#include <sge/collision/shapes/circle.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/assert.hpp>
#include <boost/logic/tribool.hpp>

sanguis::server::entities::base::base()
:
	collision::base(),
	environment_(),
	id_(
		get_unique_id()
	),
	angle_(0),
	links_()
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
		initial_direction()
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

void
sanguis::server::entities::base::update(
	time_type const time
)
{
	on_update(
		time
	);
}

void
sanguis::server::entities::base::die()
{
	on_die();
}

sanguis::server::entities::auto_weak_link const
sanguis::server::entities::base::link()
{
	return auto_weak_link(
		*this
	);
}

sanguis::server::environment::object_ptr const
sanguis::server::entities::base::environment() const
{
	FCPPT_ASSERT(
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

	on_center(
		_center
	);
}

bool
sanguis::server::entities::base::server_only() const
{
	return false;
}

sanguis::server::entities::base::~base()
{}

void
sanguis::server::entities::base::on_update(
	time_type
)
{}

void
sanguis::server::entities::base::on_die()
{}

void
sanguis::server::entities::base::on_center(
	pos_type const &
)
{}

void
sanguis::server::entities::base::on_transfer(
	collision::global_groups const &,
	collision::create_parameters const &
)
{}

sanguis::server::pos_type const
sanguis::server::entities::base::initial_direction() const
{
	return pos_type::null();
}

sge::collision::shapes::container const
sanguis::server::entities::base::recreate_shapes(
	sge::collision::world_ptr const world_
) const
{
	return
		fcppt::assign::make_container<
			sge::collision::shapes::container
		>(
			world_->create_circle(
				radius()
			)
		);
}

sanguis::server::collision::group_vector const
sanguis::server::entities::base::collision_groups() const
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
	links_.push_back(
		link_
	);
}

boost::logic::tribool const
sanguis::server::entities::base::can_collide_with(
	collision::base const &base_
) const
{
	base const *const other(
		dynamic_cast<
			base const *
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
	collision::base &base_
)
{
	base *const other(
		dynamic_cast<
			base *
		>(
			&base_
		)
	);

	if(other)
		collision_entity_begin(
			*other
		);
}

void
sanguis::server::entities::base::collision_end(
	collision::base &base_
)
{
	base *const other(
		dynamic_cast<
			base *
		>(
			&base_
		)
	);

	if(other)
		collision_entity_end(
			*other
		);
}

boost::logic::tribool const
sanguis::server::entities::base::can_collide_with_entity(
	base const &
) const
{
	return boost::logic::indeterminate;
}

void
sanguis::server::entities::base::collision_entity_begin(
	base &
)
{}

void
sanguis::server::entities::base::collision_entity_end(
	base &
)
{}
