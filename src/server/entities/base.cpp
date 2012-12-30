#include <sanguis/entity_id.hpp>
#include <sanguis/server/get_unique_id.hpp>
#include <sanguis/server/collision/global_groups_fwd.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/transfer_parameters.hpp>
#include <sanguis/server/environment/object.hpp>
#include <fcppt/assert/pre.hpp>


sanguis::server::entities::base::base()
:
	environment_(
		nullptr
	),
	id_(
		sanguis::server::get_unique_id()
	),
	links_()
{
}

void
sanguis::server::entities::base::transfer(
	sanguis::server::environment::object &_environment,
	sanguis::server::collision::global_groups const &_collision_groups,
	sanguis::server::entities::insert_parameters const &_insert_param
)
{
	bool const create(
		environment_ == nullptr
	);

	environment_ = &_environment;

	this->on_transfer(
		sanguis::server::entities::transfer_parameters(
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
sanguis::server::entities::base::update()
{
	this->on_update();
}

void
sanguis::server::entities::base::remove()
{
	this->on_remove();
}

void
sanguis::server::entities::base::destroy()
{
	this->on_destroy();
}

sanguis::server::entities::auto_weak_link const
sanguis::server::entities::base::link()
{
	return
		sanguis::server::entities::auto_weak_link(
			*this
		);
}

sanguis::server::environment::object &
sanguis::server::entities::base::environment() const
{
	FCPPT_ASSERT_PRE(
		this->has_environment()
	);

	return *environment_;
}

bool
sanguis::server::entities::base::has_environment() const
{
	return
		environment_ != nullptr;
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
sanguis::server::entities::base::on_update()
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
	sanguis::server::entities::transfer_parameters const &
)
{
}

void
sanguis::server::entities::base::insert_link(
	sanguis::server::entities::auto_weak_link &_link
)
{
	links_.push_back(
		_link
	);
}
