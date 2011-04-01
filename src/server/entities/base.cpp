#include "base.hpp"
#include "auto_weak_link.hpp"
#include "insert_parameters.hpp"
#include "../collision/create_parameters.hpp"
#include "../environment/object.hpp"
#include "../get_unique_id.hpp"
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/assert.hpp>

sanguis::server::entities::base::base()
:
	environment_(0),
	id_(
		server::get_unique_id()
	),
	angle_(0),
	processed_(false),
	links_()
{
}

void
sanguis::server::entities::base::transfer(
	server::environment::object &_environment,
	collision::global_groups const &_collision_groups,
	entities::insert_parameters const &_insert_param
)
{
	environment_ = &_environment;

	this->angle(
		_insert_param.angle()
	);

	this->on_transfer(
		collision::create_parameters(
			environment_->collision_world(),
			_insert_param.center(),
			this->initial_direction(),
			_collision_groups
		)
	);
}

void
sanguis::server::entities::base::update(
	sanguis::time_type const _time
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
		entities::auto_weak_link(
			*this
		);
}

sanguis::server::environment::object &
sanguis::server::entities::base::environment() const
{
	FCPPT_ASSERT(
		environment_
	);

	return *environment_;
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

sanguis::server::angle const
sanguis::server::entities::base::angle() const
{
	return angle_;
}

void
sanguis::server::entities::base::angle(
	server::angle const _angle
)
{
	angle_ = _angle;
}

bool
sanguis::server::entities::base::server_only() const
{
	return false;
}

sanguis::server::entities::base::~base()
{
}

void
sanguis::server::entities::base::on_update(
	sanguis::time_type
)
{
}

void
sanguis::server::entities::base::on_die()
{
}

void
sanguis::server::entities::base::on_transfer(
	collision::create_parameters const &
)
{
}

sanguis::server::speed const
sanguis::server::entities::base::initial_direction() const
{
	return
		server::speed(
			server::speed::value_type::null()
		);
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
