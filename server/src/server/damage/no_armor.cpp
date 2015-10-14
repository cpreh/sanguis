#include <sanguis/server/damage/armor_array.hpp>
#include <sanguis/server/damage/armor_unit.hpp>
#include <sanguis/server/damage/no_armor.hpp>
#include <fcppt/algorithm/array_init.hpp>


sanguis::server::damage::armor_array
sanguis::server::damage::no_armor()
{
	return
		sanguis::server::damage::armor_array{
			fcppt::algorithm::array_init<
				sanguis::server::damage::armor_array::internal
			>(
				sanguis::server::damage::armor_unit(
					0.f
				)
			)
		};
}
