#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/primary_weapon_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/weapons/accuracy.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/pistol.hpp>
#include <sanguis/server/weapons/pistol_parameters.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/sentry.hpp>
#include <sanguis/server/weapons/sentry_parameters.hpp>
#include <sanguis/server/weapons/sentry_weapon.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/factory/parameters.hpp>
#include <sanguis/server/weapons/factory/sentry.hpp>
#include <sanguis/server/weapons/modifiers/apply.hpp>
#include <sanguis/server/weapons/modifiers/container.hpp>
#include <sanguis/server/weapons/modifiers/damage.hpp>
#include <sanguis/server/weapons/modifiers/health.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::server::weapons::unique_ptr
sanguis::server::weapons::factory::sentry(
	sanguis::server::weapons::factory::parameters const &_parameters
)
{
	sanguis::diff_clock const &diff_clock(
		_parameters.diff_clock()
	);

	sanguis::random_generator &random_generator(
		_parameters.random_generator()
	);

	sanguis::server::entities::enemies::difficulty const difficulty(
		_parameters.difficulty()
	);

	return
		fcppt::make_unique_ptr<
			sanguis::server::weapons::sentry
		>(
			diff_clock,
			random_generator,
			sanguis::server::weapons::sentry_weapon(
				[
					&diff_clock,
					&random_generator,
					difficulty
				]
				()
				{
					return
						fcppt::make_unique_ptr<
							sanguis::server::weapons::pistol
						>(
							diff_clock,
							random_generator,
							sanguis::weapon_type(
								sanguis::primary_weapon_type::pistol
							),
							sanguis::server::weapons::modifiers::apply(
								random_generator,
								difficulty,
								sanguis::server::weapons::modifiers::container<
									sanguis::server::weapons::pistol_parameters
								>{
									&sanguis::server::weapons::modifiers::damage<
										sanguis::server::weapons::pistol_parameters
									>
								},
								sanguis::server::weapons::pistol_parameters(
									sanguis::server::weapons::accuracy(
										0.95f
									),
									sanguis::server::weapons::base_cooldown(
										sanguis::duration_second(
											0.06f
										)
									),
									sanguis::server::weapons::damage(
										1.f
										*
										std::sqrt(
											difficulty.get()
										)
									),
									sanguis::server::weapons::cast_point(
										sanguis::duration_second(
											0.2f
										)
									),
									sanguis::server::weapons::magazine_size(
										20u
									),
									sanguis::server::weapons::reload_time(
										sanguis::duration_second(
											5.f
										)
									),
									sanguis::server::weapons::range(
										1000.f
									)
								)
							)
						);
				}
			),
			sanguis::server::weapons::modifiers::apply(
				_parameters.random_generator(),
				_parameters.difficulty(),
				sanguis::server::weapons::modifiers::container<
					sanguis::server::weapons::sentry_parameters
				>{
					&sanguis::server::weapons::modifiers::health<
						sanguis::server::weapons::sentry_parameters
					>
				},
				sanguis::server::weapons::sentry_parameters(
					sanguis::server::health(
						100.f
					),
					sanguis::server::weapons::base_cooldown(
						sanguis::duration_second(
							5.f
						)
					),
					sanguis::server::weapons::cast_point(
						sanguis::duration_second(
							2.f
						)
					),
					sanguis::server::weapons::range(
						1000.f
					),
					sanguis::server::weapons::magazine_size(
						1u
					)
				)
			)
		);
}