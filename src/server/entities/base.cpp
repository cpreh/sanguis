#include "base.hpp"
#include "auto_weak_link.hpp"
#include "insert_parameters.hpp"
#include "collision_groups.hpp"
#include "../collision/create_parameters.hpp"
#include "../collision/create_circle.hpp"
#include "../environment/object.hpp"
#include "../get_unique_id.hpp"
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/assert.hpp>
#include <boost/logic/tribool.hpp>

sanguis::server::entities::base::base()
:
	collision::body(),
	collision::base(),
	environment_(),
	id_(
		get_unique_id()
	),
	angle_(0),
	processed_(false),
	links_()
{
}

sge::projectile::shape::base_ptr const
sanguis::server::entities::base::recreate_shape()
{
	return
		collision::create_circle(
			this->radius()
		);
}

void
sanguis::server::entities::base::transfer(
	server::environment::object_ptr const _environment,
	collision::global_groups const &_collision_groups,
	insert_parameters const &_insert_param
)
{
	environment_ = _environment;

	collision::create_parameters const create_param(
		_insert_param.center(),
		this->initial_direction()
	);

	collision::body::recreate(
		environment_->collision_world(),
		_collision_groups,
		create_param
	);
	
	this->angle(
		_insert_param.angle()
	);

	this->on_transfer(
		_collision_groups,
		create_param
	);
}

void
sanguis::server::entities::base::update(
	time_type const _time
)
{
	this->on_update(
		_time
	);
}

void
sanguis::server::entities::base::die()
{
	this->on_die();
}

bool
sanguis::server::entities::base::processed() const
{
	return processed_;
}
	
void
sanguis::server::entities::base::may_be_deleted()
{
	processed_ = true;
}

sanguis::server::entities::auto_weak_link const
sanguis::server::entities::base::link()
{
	return
		auto_weak_link(
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

bool
sanguis::server::entities::base::is_in_world() const
{
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
	return this->body_pos();
}

void
sanguis::server::entities::base::center(
	pos_type const &_center
)
{
	this->body_pos(
		_center
	);

	this->on_center(
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

void
sanguis::server::entities::base::insert_link(
	auto_weak_link &_link
)
{
	links_.push_back(
		_link
	);
}

boost::logic::tribool const
sanguis::server::entities::base::can_collide_with(
	collision::base const &_base
) const
{
	base const *const other(
		dynamic_cast<
			base const *
		>(
			&_base
		)
	);

	return
		other
		?
			this->can_collide_with_entity(
				*other
			)
		:
			boost::logic::indeterminate;
}

void
sanguis::server::entities::base::collision_begin(
	collision::base &_base
)
{
	base *const other(
		dynamic_cast<
			base *
		>(
			&_base
		)
	);

	if(
		other
	)
		this->collision_entity_begin(
			*other
		);
}

void
sanguis::server::entities::base::collision_end(
	collision::base &_base
)
{
	base *const other(
		dynamic_cast<
			base *
		>(
			&_base
		)
	);

	if(
		other
	)
		this->collision_entity_end(
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
