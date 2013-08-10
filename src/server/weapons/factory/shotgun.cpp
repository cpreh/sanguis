#include <sanguis/duration_second.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/shotgun.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/factory/parameters.hpp>
#include <sanguis/server/weapons/factory/shotgun.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::server::weapons::unique_ptr
sanguis::server::weapons::factory::shotgun(
	sanguis::server::weapons::factory::parameters const &_parameters
)
{
	return
		fcppt::make_unique_ptr<
			sanguis::server::weapons::shotgun
		>(
			_parameters.diff_clock(),
			_parameters.random_generator(),
			_parameters.weapon_type(),
			sanguis::server::weapons::base_cooldown(
				sanguis::duration_second(
					1.f
				)
			),
			sanguis::server::weapons::cast_point(
				sanguis::duration_second(
					0.5f
				)
			),
			sanguis::server::weapons::shotgun::spread_radius(
				0.2f
			),
			sanguis::server::weapons::shotgun::shells(
				10u
			),
			sanguis::server::weapons::damage(
				1.f
			),
			sanguis::server::weapons::magazine_size(
				8u
			),
			sanguis::server::weapons::reload_time(
				sanguis::duration_second(
					3.f
				)
			),
			sanguis::server::weapons::range(
				20.f
			)
		);
}
