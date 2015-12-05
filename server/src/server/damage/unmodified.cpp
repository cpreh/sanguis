#include <sanguis/server/damage/array.hpp>
#include <sanguis/server/damage/modified_array.hpp>
#include <sanguis/server/damage/modified_unit.hpp>
#include <sanguis/server/damage/type.hpp>
#include <sanguis/server/damage/unmodified.hpp>
#include <fcppt/algorithm/enum_array_init.hpp>


sanguis::server::damage::modified_array
sanguis::server::damage::unmodified(
	sanguis::server::damage::array const &_damages
)
{
	return
		fcppt::algorithm::enum_array_init<
			sanguis::server::damage::modified_array
		>(
			[
				&_damages
			](
				sanguis::server::damage::type const _type
			)
			{
				return
					sanguis::server::damage::modified_unit(
						_damages[
							_type
						].get()
					);
			}
		);
}
