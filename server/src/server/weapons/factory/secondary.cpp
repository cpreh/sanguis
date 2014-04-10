#include <sanguis/secondary_weapon_type.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/factory/grenade.hpp>
#include <sanguis/server/weapons/factory/secondary.hpp>
#include <sanguis/server/weapons/factory/sentry.hpp>
#include <fcppt/assert/unreachable.hpp>


sanguis::server::weapons::unique_ptr
sanguis::server::weapons::factory::secondary(
	sanguis::secondary_weapon_type const _type,
	sanguis::server::weapons::factory::parameters const &_parameters
)
{
	switch(
		_type
	)
	{
	case sanguis::secondary_weapon_type::grenade:
		return
			sanguis::server::weapons::factory::grenade(
				_parameters
			);
	case sanguis::secondary_weapon_type::sentry:
		return
			sanguis::server::weapons::factory::sentry(
				_parameters
			);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
