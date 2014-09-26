#include <sanguis/server/entities/property/initial.hpp>
#include <sanguis/server/entities/property/initial_max.hpp>
#include <sanguis/server/entities/property/value.hpp>


sanguis::server::entities::property::initial const
sanguis::server::entities::property::initial_max(
	sanguis::server::entities::property::value  const _base
)
{
	return
		sanguis::server::entities::property::initial(
			sanguis::server::entities::property::initial::base(
				_base
			),
			sanguis::server::entities::property::initial::current(
				_base
			)
		);
}
