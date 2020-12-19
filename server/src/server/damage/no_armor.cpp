#include <sanguis/server/damage/armor_array.hpp>
#include <sanguis/server/damage/armor_unit.hpp>
#include <sanguis/server/damage/no_armor.hpp>
#include <fcppt/container/array/init_const.hpp>


sanguis::server::damage::armor_array
sanguis::server::damage::no_armor()
{
	return
		sanguis::server::damage::armor_array{
			fcppt::container::array::init_const<
				sanguis::server::damage::armor_array::internal
			>(
				sanguis::server::damage::armor_unit(
					0.F
				)
			)
		};
}
