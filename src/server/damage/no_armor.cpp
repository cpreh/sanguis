#include <sanguis/server/damage/all.hpp>
#include <sanguis/server/damage/array.hpp>
#include <sanguis/server/damage/list.hpp>
#include <sanguis/server/damage/no_armor.hpp>
#include <sanguis/server/damage/unit.hpp>


sanguis::server::damage::armor const
sanguis::server::damage::no_armor()
{
	return
		sanguis::server::damage::armor(
			sanguis::server::damage::array(
				sanguis::server::damage::all(
					sanguis::server::damage::unit(
						0.f
					)
				)
			)
		);
}
