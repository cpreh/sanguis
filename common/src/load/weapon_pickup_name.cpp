#include <sanguis/primary_weapon_type.hpp>
#include <sanguis/secondary_weapon_type.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/load/weapon_pickup_name.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/variant/match.hpp>


fcppt::string
sanguis::load::weapon_pickup_name(
	sanguis::weapon_type const &_type
)
{
	return
		fcppt::variant::match(
			_type,
			[](
				sanguis::primary_weapon_type const _primary_type
			)
			-> fcppt::string
			{
				switch(
					_primary_type
				)
				{
				case sanguis::primary_weapon_type::pistol:
					return
						FCPPT_TEXT("pistol");
				case sanguis::primary_weapon_type::shotgun:
					return
						FCPPT_TEXT("shotgun");
				case sanguis::primary_weapon_type::rocket_launcher:
					return
						FCPPT_TEXT("rocket_launcher");
				case sanguis::primary_weapon_type::dual_pistols:
				case sanguis::primary_weapon_type::melee:
					// TODO(philipp): Add a placeholder texture here
					break;
				}

				FCPPT_ASSERT_UNREACHABLE;
			},
			[](
				sanguis::secondary_weapon_type const _secondary_type
			)
			-> fcppt::string
			{
				switch(
					_secondary_type
				)
				{
				case sanguis::secondary_weapon_type::grenade:
					return
						FCPPT_TEXT("grenade");
				case sanguis::secondary_weapon_type::sentry:
					return
						FCPPT_TEXT("sentry");
				case sanguis::secondary_weapon_type::spider:
					return
						FCPPT_TEXT("monster");
				}

				FCPPT_ASSERT_UNREACHABLE;
			}
		);
}
