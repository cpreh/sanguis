#include <sanguis/duration_second.hpp>
#include <sanguis/server/weapons/aoe.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/rocket_launcher.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/factory/parameters.hpp>
#include <sanguis/server/weapons/factory/rocket_launcher.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::server::weapons::unique_ptr
sanguis::server::weapons::factory::rocket_launcher(
	sanguis::server::weapons::factory::parameters const &_parameters
)
{
	return
		fcppt::make_unique_ptr<
			sanguis::server::weapons::rocket_launcher
		>(
			_parameters.diff_clock(),
			_parameters.weapon_type(),
			sanguis::server::weapons::base_cooldown(
				sanguis::duration_second(
					0.8f
				)
			),
			sanguis::server::weapons::cast_point(
				sanguis::duration_second(
					0.5f
				)
			),
			sanguis::server::weapons::damage(
				9.f
			),
			sanguis::server::weapons::aoe(
				2.4f
			),
			sanguis::server::weapons::magazine_size(
				1u
			),
			sanguis::server::weapons::reload_time(
				sanguis::duration_second(
					1.8f
				)
			),
			sanguis::server::weapons::range(
				20.f
			)
		);
}
