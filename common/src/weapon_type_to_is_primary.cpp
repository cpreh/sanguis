#include <sanguis/is_primary_weapon.hpp>
#include <sanguis/primary_weapon_type.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/weapon_type_to_is_primary.hpp>
#include <fcppt/variant/holds_type.hpp>


sanguis::is_primary_weapon
sanguis::weapon_type_to_is_primary(
	sanguis::weapon_type const &_weapon_type
)
{
	return
		sanguis::is_primary_weapon(
			fcppt::variant::holds_type<
				sanguis::primary_weapon_type
			>(
				_weapon_type
			)
		);
}
