#include <sanguis/server/collision/create_circle.hpp>
#include <sge/projectile/shape/circle.hpp>
#include <fcppt/make_shared_ptr.hpp>

sge::projectile::shape::shared_base_ptr const
sanguis::server::collision::create_circle(
	server::radius const _radius
)
{
	return
		fcppt::make_shared_ptr<
			sge::projectile::shape::circle
		>(
			_radius.get()
		);
}
