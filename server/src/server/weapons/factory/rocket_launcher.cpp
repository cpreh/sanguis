#include <sanguis/duration_second.hpp>
#include <sanguis/server/weapons/accuracy.hpp>
#include <sanguis/server/weapons/aoe.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/rocket_launcher.hpp>
#include <sanguis/server/weapons/rocket_launcher_parameters.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/factory/parameters.hpp>
#include <sanguis/server/weapons/factory/rocket_launcher.hpp>
#include <sanguis/server/weapons/modifiers/apply.hpp>
#include <sanguis/server/weapons/modifiers/aoe.hpp>
#include <sanguis/server/weapons/modifiers/container.hpp>
#include <sanguis/server/weapons/modifiers/damage.hpp>
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
			_parameters.random_generator(),
			_parameters.weapon_type(),
			sanguis::server::weapons::modifiers::apply(
				_parameters.random_generator(),
				_parameters.difficulty(),
				sanguis::server::weapons::modifiers::container<
					sanguis::server::weapons::rocket_launcher_parameters
				>{
					&sanguis::server::weapons::modifiers::damage<
						sanguis::server::weapons::rocket_launcher_parameters
					>,
					&sanguis::server::weapons::modifiers::aoe<
						sanguis::server::weapons::rocket_launcher_parameters
					>
				},
				sanguis::server::weapons::rocket_launcher_parameters(
					sanguis::server::weapons::damage(
						12.f
					),
					sanguis::server::weapons::aoe(
						120.f
					),
					sanguis::server::weapons::accuracy(
						0.9f
					),
					sanguis::server::weapons::backswing_time(
						sanguis::duration_second(
							0.3f
						)
					),
					sanguis::server::weapons::cast_point(
						sanguis::duration_second(
							0.5f
						)
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
						1000.f
					)
				)
			)
		);
}
