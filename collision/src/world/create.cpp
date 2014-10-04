#include <sanguis/collision/world/create.hpp>
#include <sanguis/collision/world/object_unique_ptr.hpp>
#include <sanguis/collision/world/parameters_fwd.hpp>
#if defined(SANGUIS_COLLISION_ENABLE_PROJECTILE)
#include <sanguis/collision/aux_/world/projectile/object.hpp>
#else
#include <sanguis/collision/aux_/world/simple/object.hpp>
#endif
#include <fcppt/make_unique_ptr.hpp>


sanguis::collision::world::object_unique_ptr
sanguis::collision::world::create(
	sanguis::collision::world::parameters const &_parameters
)
{
	return
		fcppt::make_unique_ptr<
#if defined(SANGUIS_COLLISION_ENABLE_PROJECTILE)
			sanguis::collision::aux_::world::projectile::object
#else
			sanguis::collision::aux_::world::simple::object
#endif
		>(
			_parameters
		);
}
