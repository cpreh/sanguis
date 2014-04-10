#include <sanguis/primary_weapon_type.hpp>
#include <sanguis/secondary_weapon_type.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/factory/parameters_fwd.hpp>
#include <sanguis/server/weapons/factory/primary.hpp>
#include <sanguis/server/weapons/factory/secondary.hpp>
#include <sanguis/server/weapons/factory/visitor.hpp>


sanguis::server::weapons::factory::visitor::visitor(
	sanguis::server::weapons::factory::parameters const &_parameters
)
:
	parameters_(
		_parameters
	)
{
}

sanguis::server::weapons::factory::visitor::result_type
sanguis::server::weapons::factory::visitor::operator()(
	sanguis::primary_weapon_type const _primary
) const
{
	return
		sanguis::server::weapons::factory::primary(
			_primary,
			parameters_
		);
}

sanguis::server::weapons::factory::visitor::result_type
sanguis::server::weapons::factory::visitor::operator()(
	sanguis::secondary_weapon_type const _secondary
) const
{
	return
		sanguis::server::weapons::factory::secondary(
			_secondary,
			parameters_
		);
}
