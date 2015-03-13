#include <sanguis/server/entities/center_ghost.hpp>
#include <sanguis/server/entities/center_simple.hpp>
#include <sanguis/server/entities/optional_transfer_result.hpp>
#include <sanguis/server/entities/transfer_parameters_fwd.hpp>
#include <sanguis/server/entities/with_ghosts.hpp>


sanguis::server::entities::center_ghost::center_ghost()
:
	sanguis::server::entities::with_ghosts(),
	sanguis::server::entities::center_simple()
{
}

sanguis::server::entities::center_ghost::~center_ghost()
{
}

sanguis::server::entities::optional_transfer_result
sanguis::server::entities::center_ghost::on_transfer(
	sanguis::server::entities::transfer_parameters const &_parameters
)
{
	// TODO: Combine the results
	sanguis::server::entities::center_simple::on_transfer(
		_parameters
	);

	return
		sanguis::server::entities::with_ghosts::on_transfer(
			_parameters
		);
}
