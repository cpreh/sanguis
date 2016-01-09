#include <sanguis/diff_clock.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/update_diff_clock.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/combine_transfer.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/optional_transfer_result.hpp>
#include <sanguis/server/entities/remove_from_world_result.hpp>
#include <sanguis/server/entities/transfer_parameters.hpp>
#include <sanguis/server/entities/transfer_result.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/environment/optional_object_ref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::base::base()
:
	environment_(),
	diff_clock_()
{
}

sanguis::server::entities::optional_transfer_result
sanguis::server::entities::base::transfer(
	sanguis::server::environment::object &_environment,
	sanguis::server::entities::insert_parameters const &_insert_parameters,
	sanguis::creator::grid const &_grid
)
{
	environment_ =
		sanguis::server::environment::optional_object_ref(
			fcppt::make_ref(
				_environment
			)
		);

	return
		fcppt::optional::map(
			this->on_transfer(
				sanguis::server::entities::transfer_parameters(
					_environment.collision_world(),
					_insert_parameters.created(),
					_grid,
					_insert_parameters.center(),
					_insert_parameters.angle()
				)
			),
			[
				&_insert_parameters,
				this
			](
				sanguis::server::entities::transfer_result &&_result
			)
			{
				return
					_insert_parameters.created().get()
					?
						sanguis::server::entities::combine_transfer(
							std::move(
								_result
							),
							this->on_create()
						)
					:
						std::move(
							_result
						)
					;
			}
		);
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
sanguis::server::entities::base::remove_from_game()
{
}

sanguis::server::entities::remove_from_world_result
sanguis::server::entities::base::remove_from_world()
{
	// TODO: Should we define this?
	return
		sanguis::server::entities::remove_from_world_result();
}

sanguis::server::environment::optional_object_ref
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

sanguis::server::entities::transfer_result
sanguis::server::entities::base::on_create()
{
	// TODO: Should we define this?
	return
		sanguis::server::entities::transfer_result();
}

sanguis::server::entities::optional_transfer_result
sanguis::server::entities::base::on_transfer(
	sanguis::server::entities::transfer_parameters const &
)
{
	// TODO: Should we define this function?
	return
		sanguis::server::entities::optional_transfer_result(
			sanguis::server::entities::transfer_result()
		);
}
