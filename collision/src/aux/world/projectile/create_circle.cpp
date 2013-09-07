#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/aux/world/projectile/create_circle.hpp>
#include <sge/projectile/shape/circle.hpp>
#include <sge/projectile/shape/shared_base_ptr.hpp>
#include <fcppt/make_shared_ptr.hpp>


sge::projectile::shape::shared_base_ptr const
sanguis::collision::aux::world::projectile::create_circle(
	sanguis::collision::radius const _radius
)
{
	return
		fcppt::make_shared_ptr<
			sge::projectile::shape::circle
		>(
			_radius.get()
		);
}
