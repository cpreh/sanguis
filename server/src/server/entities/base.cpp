#include <sanguis/diff_clock.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/update_diff_clock.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/transfer_parameters.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/environment/optional_object_ref.hpp>


sanguis::server::entities::base::base()
:
	environment_(),
	diff_clock_()
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
		!environment_
	);

	environment_ =
		sanguis::server::environment::optional_object_ref(
			_environment
		);

	if(
		!this->on_transfer(
			sanguis::server::entities::transfer_parameters(
				_environment.collision_world(),
				_grid,
				_insert_param.center(),
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
sanguis::server::entities::base::world_collision(
	sanguis::creator::grid const &,
	sanguis::duration
)
{
}

void
sanguis::server::entities::base::update()
{
}

void
sanguis::server::entities::base::tick(
	sanguis::duration const &_duration
)
{
	sanguis::update_diff_clock(
		diff_clock_,
		_duration
	);
}

void
sanguis::server::entities::base::remove()
{
}

void
sanguis::server::entities::base::destroy()
{
}

void
sanguis::server::entities::base::reset_body()
{
}

sanguis::server::environment::optional_object_ref const
sanguis::server::entities::base::environment() const
{
	return
		environment_;
}

sanguis::server::entities::base::~base()
{
}

sanguis::diff_clock const &
sanguis::server::entities::base::diff_clock() const
{
	return
		diff_clock_;
}

void
sanguis::server::entities::base::on_create()
{
}

bool
sanguis::server::entities::base::on_transfer(
	sanguis::server::entities::transfer_parameters const &
)
{
	return true;
}
