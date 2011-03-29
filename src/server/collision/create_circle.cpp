#include "create_circle.hpp"
#include <sge/projectile/shapes/circle.hpp>
#include <fcppt/make_shared_ptr.hpp>

sge::projectile::shapes::base_ptr const
sanguis::server::collision::create_circle(
	server::space_unit const _radius
)
{
	return
		fcppt::make_shared_ptr<
			sge::projectile::shapes::circle
		>(
			_radius
		);
}
