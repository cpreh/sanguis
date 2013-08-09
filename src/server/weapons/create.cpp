#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/weapons/aoe.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/create.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/grenade.hpp>
#include <sanguis/server/weapons/pistol.hpp>
#include <sanguis/server/weapons/shotgun.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/rocket_launcher.hpp>
#include <sanguis/server/weapons/sentry.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/unlimited_magazine_size.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/assert/unreachable_message.hpp>


sanguis::server::weapons::unique_ptr
sanguis::server::weapons::create(
	sanguis::diff_clock const  &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::weapon_type const _type
)
{
	// TODO!
		return
			fcppt::make_unique_ptr<
				sanguis::server::weapons::pistol
			>(
				_diff_clock,
				_type,
				sanguis::server::weapons::base_cooldown(
					sanguis::duration_second(
						0.5f
					)
				),
				sanguis::server::weapons::damage(
					5.f
				),
				sanguis::server::weapons::cast_point(
					sanguis::duration_second(
						0.2f
					)
				),
				sanguis::server::weapons::magazine_size(
					18u
				),
				sanguis::server::weapons::reload_time(
					sanguis::duration_second(
						2.f
					)
				),
				sanguis::server::weapons::range(
					20.f
				)
			);

/*
	switch(
		_type
	)
	{
	case sanguis::weapon_type::melee:
		FCPPT_ASSERT_UNREACHABLE_MESSAGE(
			FCPPT_TEXT("Please create melee weapons directly, not through the weapon factory!")
		);
		break;
	case sanguis::weapon_type::pistol:
		return
			fcppt::make_unique_ptr<
				sanguis::server::weapons::pistol
			>(
				_diff_clock,
				_type,
				sanguis::server::weapons::base_cooldown(
					sanguis::duration_second(
						0.5f
					)
				),
				sanguis::server::weapons::damage(
					5.f
				),
				sanguis::server::weapons::cast_point(
					sanguis::duration_second(
						0.2f
					)
				),
				sanguis::server::weapons::magazine_size(
					18u
				),
				sanguis::server::weapons::reload_time(
					sanguis::duration_second(
						2.f
					)
				),
				sanguis::server::weapons::range(
					20.f
				)
			);
	case sanguis::weapon_type::dual_pistol:
		return
			fcppt::make_unique_ptr<
				sanguis::server::weapons::pistol
			>(
				_diff_clock,
				_type,
				sanguis::server::weapons::base_cooldown(
					sanguis::duration_second(
						0.33f
					)
				),
				sanguis::server::weapons::damage(
					5.f
				),
				sanguis::server::weapons::cast_point(
					sanguis::duration_second(
						0.2f
					)
				),
				sanguis::server::weapons::magazine_size(
					36u
				),
				sanguis::server::weapons::reload_time(
					sanguis::duration_second(
						4.f
					)
				),
				sanguis::server::weapons::range(
					20.f
				)
			);
	case sanguis::weapon_type::shotgun:
		return
			fcppt::make_unique_ptr<
				sanguis::server::weapons::shotgun
			>(
				_diff_clock,
				_random_generator,
				_type,
				sanguis::server::weapons::base_cooldown(
					sanguis::duration_second(
						1.f
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
				)
			);
	case sanguis::weapon_type::rocket_launcher:
		return
			fcppt::make_unique_ptr<
				sanguis::server::weapons::rocket_launcher
			>(
				_diff_clock,
				_type,
				sanguis::server::weapons::base_cooldown(
					sanguis::duration_second(
						0.8f
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
				)
			);
	case sanguis::weapon_type::grenade:
		return
			fcppt::make_unique_ptr<
				sanguis::server::weapons::grenade
			>(
				_diff_clock,
				_type,
				sanguis::server::weapons::base_cooldown(
					sanguis::duration_second(
						0.7f
					)
				),
				sanguis::server::weapons::damage(
					20.f
				),
				sanguis::server::weapons::aoe(
					3.6f
				),
				sanguis::server::weapons::cast_point(
					sanguis::duration_second(
						0.1f
					)
				),
				sanguis::server::weapons::reload_time(
					sanguis::duration_second(
						1.f
					)
				)
			);
	case sanguis::weapon_type::sentry:
		return
			fcppt::make_unique_ptr<
				sanguis::server::weapons::sentry
			>(
				_diff_clock,
				_random_generator,
				_type,
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
				sanguis::server::weapons::reload_time(
					sanguis::duration_second(
						0.f
					)
				),
				[&_diff_clock]
				()
				{
					return
						fcppt::make_unique_ptr<
							sanguis::server::weapons::pistol
						>(
							_diff_clock,
							sanguis::weapon_type::pistol,
							sanguis::server::weapons::base_cooldown(
								sanguis::duration_second(
									0.06f
								)
							),
							sanguis::server::weapons::damage(
								1.f
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
								20.f
							)
						);
				}
			);
	}

	FCPPT_ASSERT_UNREACHABLE;*/
}
