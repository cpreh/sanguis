#include <sanguis/server/damage/array.hpp>
#include <sanguis/server/damage/explosive.hpp>
#include <sanguis/server/damage/fire.hpp>
#include <sanguis/server/damage/make_array.hpp>
#include <sanguis/server/damage/piercing.hpp>
#include <sanguis/server/damage/unit.hpp>


sanguis::server::damage::array const
sanguis::server::damage::explosive()
{
	return
		sanguis::server::damage::make_array({
			sanguis::server::damage::piercing =
				sanguis::server::damage::unit(
					0.5f
				),
			sanguis::server::damage::fire =
				sanguis::server::damage::unit(
					0.5f
				)
		});
}
