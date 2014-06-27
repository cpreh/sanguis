#include <sanguis/server/damage/array.hpp>
#include <sanguis/server/damage/modified_array.hpp>
#include <sanguis/server/damage/modified_unit.hpp>
#include <sanguis/server/damage/type.hpp>
#include <sanguis/server/damage/unit_value.hpp>
#include <sanguis/server/entities/modify_damages.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/algorithm/enum_array_fold.hpp>


sanguis::server::damage::modified_array const
sanguis::server::entities::modify_damages(
	sanguis::server::entities::with_weapon const &_entity,
	sanguis::server::damage::array const &_damages
)
{
	return
		fcppt::algorithm::enum_array_fold<
			sanguis::server::damage::modified_array
		>(
			[
				&_entity,
				&_damages
			](
				sanguis::server::damage::type const _type
			)
			{
				return
					sanguis::server::damage::modified_unit(
						(
							fcppt::literal<
								sanguis::server::damage::unit_value
							>(
								1
							)
							+
							_entity.extra_damage_value(
								_type
							).get()
						)
						*
						_damages[
							_type
						].get()
					);
			}
		);
}
