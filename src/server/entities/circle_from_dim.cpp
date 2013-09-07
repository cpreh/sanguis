#include <sanguis/server/dim_fwd.hpp>
#include <sanguis/server/entities/circle_from_dim.hpp>
#include <sanguis/server/entities/body_parameters.hpp>
#include <sanguis/server/entities/radius.hpp>


sanguis::server::entities::body_parameters const
sanguis::server::entities::circle_from_dim(
	sanguis::server::dim const &_dim
)
{
	return
		sanguis::server::entities::body_parameters(
			sanguis::server::entities::radius(
				_dim
			)
		);
}
