#include <sanguis/collision/world/create.hpp>
#include <sanguis/collision/world/object_unique_ptr.hpp>
#include <sanguis/collision/world/parameters_fwd.hpp>
//#include <sanguis/collision/aux/world/projectile/object.hpp>
#include <sanguis/collision/aux/world/simple/object.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::collision::world::object_unique_ptr
sanguis::collision::world::create(
	sanguis::collision::world::parameters const &_parameters
)
{
	return
		fcppt::make_unique_ptr<
//			sanguis::collision::aux::world::projectile::object
			sanguis::collision::aux::world::simple::object
		>(
			_parameters
		);
}
