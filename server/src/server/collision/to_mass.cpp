#include <sanguis/collision/mass.hpp>
#include <sanguis/server/mass.hpp>
#include <sanguis/server/collision/to_mass.hpp>


sanguis::collision::mass const
sanguis::server::collision::to_mass(
	sanguis::server::mass const _mass
)
{
	return
		_mass.get();
}
