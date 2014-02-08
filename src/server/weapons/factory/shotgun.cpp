#include <sanguis/duration_second.hpp>
#include <sanguis/server/weapons/accuracy.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/shells.hpp>
#include <sanguis/server/weapons/shotgun.hpp>
#include <sanguis/server/weapons/shotgun_parameters.hpp>
#include <sanguis/server/weapons/spread_radius.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/factory/parameters.hpp>
#include <sanguis/server/weapons/factory/shotgun.hpp>
#include <sanguis/server/weapons/modifiers/accuracy.hpp>
#include <sanguis/server/weapons/modifiers/apply.hpp>
#include <sanguis/server/weapons/modifiers/container.hpp>
#include <sanguis/server/weapons/modifiers/damage.hpp>
#include <sanguis/server/weapons/modifiers/magazine_size.hpp>
#include <sanguis/server/weapons/modifiers/spread_radius.hpp>
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
			sanguis::server::weapons::modifiers::apply(
				_parameters.random_generator(),
				_parameters.difficulty(),
				sanguis::server::weapons::modifiers::container<
					sanguis::server::weapons::shotgun_parameters
				>{
					&sanguis::server::weapons::modifiers::damage<
						sanguis::server::weapons::shotgun_parameters
					>,
					&sanguis::server::weapons::modifiers::accuracy<
						sanguis::server::weapons::shotgun_parameters
					>,
					&sanguis::server::weapons::modifiers::spread_radius<
						sanguis::server::weapons::shotgun_parameters
					>,
					&sanguis::server::weapons::modifiers::magazine_size<
						sanguis::server::weapons::shotgun_parameters
					>
				},
				sanguis::server::weapons::shotgun_parameters(
					sanguis::server::weapons::accuracy(
						0.9f
					),
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
					sanguis::server::weapons::spread_radius(
						0.2f
					),
					sanguis::server::weapons::shells(
						10u
					),
					sanguis::server::weapons::damage(
						2.5f
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
						1000.f
					)
				)
			)
		);
}
