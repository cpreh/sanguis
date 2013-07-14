#include <sanguis/creator/grid_fwd.hpp>
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
	links_()
{
}

bool
sanguis::server::entities::base::transfer(
	sanguis::server::environment::object &_environment,
	sanguis::server::entities::insert_parameters const &_insert_param,
	sanguis::creator::grid const &_grid
)
{
	bool const create(
		environment_ == nullptr
	);

	environment_ = &_environment;

	if(
		!this->on_transfer(
			sanguis::server::entities::transfer_parameters(
				_environment.collision_world(),
				_grid,
				_insert_param.center(),
				_environment.global_collision_groups(),
				_insert_param.angle()
			)
		)
	)
		return false;

	if(
		create
	)
		this->on_create();

	return true;
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

bool
sanguis::server::entities::base::on_transfer(
	sanguis::server::entities::transfer_parameters const &
)
{
	return true;
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
