#include <sanguis/duration_second.hpp>
#include <sanguis/server/weapons/aoe.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/grenade.hpp>
#include <sanguis/server/weapons/grenade_parameters.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/factory/grenade.hpp>
#include <sanguis/server/weapons/factory/parameters.hpp>
#include <sanguis/server/weapons/modifiers/aoe.hpp>
#include <sanguis/server/weapons/modifiers/apply.hpp>
#include <sanguis/server/weapons/modifiers/damage.hpp>
#include <sanguis/server/weapons/modifiers/make_guaranteed.hpp>
#include <sanguis/server/weapons/modifiers/make_potential.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sanguis::server::weapons::unique_ptr
sanguis::server::weapons::factory::grenade(
	sanguis::server::weapons::factory::parameters const &_parameters
)
{
	return
		fcppt::unique_ptr_to_base<
			sanguis::server::weapons::weapon
		>(
			fcppt::make_unique_ptr<
				sanguis::server::weapons::grenade
			>(
				_parameters.common_parameters(),
				sanguis::server::weapons::modifiers::apply(
					_parameters.random_generator(),
					_parameters.difficulty(),
					sanguis::server::weapons::modifiers::make_guaranteed<
						sanguis::server::weapons::grenade_parameters
					>(
						sanguis::server::weapons::modifiers::damage{}
					),
					sanguis::server::weapons::modifiers::make_potential<
						sanguis::server::weapons::grenade_parameters
					>(
						sanguis::server::weapons::modifiers::aoe{}
					),
					sanguis::server::weapons::grenade_parameters(
						sanguis::server::weapons::backswing_time(
							sanguis::duration_second(
								0.6F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
							)
						),
						sanguis::server::weapons::damage(
							20.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
						),
						sanguis::server::weapons::aoe(
							180.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
						),
						sanguis::server::weapons::cast_point(
							sanguis::duration_second(
								0.1F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
							)
						),
						sanguis::server::weapons::range(
							1000.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
						)
					)
				)
			)
		);
}
