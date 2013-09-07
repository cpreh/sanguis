#include <sanguis/server/radius.hpp>
#include <sanguis/server/entities/body_parameters.hpp>


sanguis::server::entities::body_parameters::body_parameters(
	sanguis::server::radius const _radius
)
:
	radius_(
		_radius
	)
{
}

sanguis::server::radius const
sanguis::server::entities::body_parameters::radius() const
{
	return radius_;
}
