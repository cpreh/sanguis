#include <sanguis/server/center.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/center_simple.hpp>
#include <sanguis/server/entities/optional_transfer_result.hpp>
#include <sanguis/server/entities/transfer_parameters.hpp>
#include <sanguis/server/entities/transfer_result.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/assert/optional_error.hpp>


sanguis::server::entities::center_simple::center_simple()
:
	center_()
{
}

sanguis::server::center const
sanguis::server::entities::center_simple::center() const
{
	return
		FCPPT_ASSERT_OPTIONAL_ERROR(
			center_
		);
}

sanguis::server::entities::center_simple::~center_simple()
{
}

sanguis::server::entities::optional_transfer_result
sanguis::server::entities::center_simple::on_transfer(
	sanguis::server::entities::transfer_parameters const &_parameters
)
{
	center_ =
		optional_center{
			_parameters.center()
		};

	return
		sanguis::server::entities::optional_transfer_result(
			sanguis::server::entities::transfer_result()
		);
}
