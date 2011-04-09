#include "base.hpp"
#include "auto_weak_link.hpp"
#include "insert_parameters.hpp"
#include "transfer_parameters.hpp"
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
	bool const create(
		environment_ == 0
	);

	environment_ = &_environment;

	this->on_transfer(
		entities::transfer_parameters(
			environment_->collision_world(),
			_insert_param.center(),
			_collision_groups,
			_insert_param.angle()
		)
	);

	if(
		create
	)
		this->on_create();
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
sanguis::server::entities::base::destroy()
{
	this->on_remove();

	this->on_destroy();
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
		this->has_environment()
	);

	return *environment_;
}

bool
sanguis::server::entities::base::has_environment() const
{
	return
		environment_ != 0;
}

sanguis::entity_id const
sanguis::server::entities::base::id() const
{
	return id_;
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
sanguis::server::entities::base::on_create()
{
}

void
sanguis::server::entities::base::on_remove()
{
}

void
sanguis::server::entities::base::on_destroy()
{
}

void
sanguis::server::entities::base::on_transfer(
	entities::transfer_parameters const &
)
{
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
