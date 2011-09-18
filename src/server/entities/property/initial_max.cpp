#include <sanguis/server/entities/property/initial_max.hpp>
#include <sanguis/server/entities/property/initial.hpp>
#include <sanguis/server/entities/property/value.hpp>

sanguis::server::entities::property::initial const
sanguis::server::entities::property::initial_max(
	value  const _base
)
{
	return
		property::initial(
			_base,
			_base
		);
}
