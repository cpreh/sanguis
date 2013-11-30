#include <sanguis/duration_second.hpp>
#include <sanguis/server/weapons/aoe.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/grenade.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/factory/grenade.hpp>
#include <sanguis/server/weapons/factory/parameters.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::server::weapons::unique_ptr
sanguis::server::weapons::factory::grenade(
	sanguis::server::weapons::factory::parameters const &_parameters
)
{
	return
		fcppt::make_unique_ptr<
			sanguis::server::weapons::grenade
		>(
			_parameters.diff_clock(),
			_parameters.random_generator(),
			sanguis::server::weapons::base_cooldown(
				sanguis::duration_second(
					0.7f
				)
			),
			sanguis::server::weapons::damage(
				20.f
			),
			sanguis::server::weapons::aoe(
				180.f
			),
			sanguis::server::weapons::cast_point(
				sanguis::duration_second(
					0.1f
				)
			),
			sanguis::server::weapons::range(
				1000.f
			),
			sanguis::server::weapons::magazine_size(
				3u
			)
		);
}
