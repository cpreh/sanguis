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
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/assert/unreachable_message.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/spirit/home/phoenix/object/new.hpp>
#include <fcppt/config/external_end.hpp>

sanguis::server::weapons::unique_ptr
sanguis::server::weapons::create(
	sanguis::diff_clock const  &_diff_clock,
	sanguis::random_generator &_random_generator,
	weapon_type::type const _type
)
{
	switch(
		_type
	)
	{
	case weapon_type::melee:
		FCPPT_ASSERT_UNREACHABLE_MESSAGE(
			FCPPT_TEXT("Please create melee weapons directly, not through the weapon factory!")
		);
		break;
	case weapon_type::pistol:
		return
			weapons::unique_ptr(
				fcppt::make_unique_ptr<
					weapons::pistol
				>(
					fcppt::cref(
						_diff_clock
					),
					_type,
					weapons::base_cooldown(
						sanguis::duration_second(
							0.5f
						)
					),
					weapons::damage(
						5.f
					),
					weapons::cast_point(
						sanguis::duration_second(
							0.2f
						)
					),
					weapons::magazine_size(
						18u
					),
					weapons::reload_time(
						sanguis::duration_second(
							2.f
						)
					),
					weapons::range(
						20.f
					)
				)
			);
	case weapon_type::dual_pistol:
		return
			weapons::unique_ptr(
				fcppt::make_unique_ptr<
					weapons::pistol
				>(
					fcppt::cref(
						_diff_clock
					),
					_type,
					weapons::base_cooldown(
						sanguis::duration_second(
							0.33f
						)
					),
					weapons::damage(
						5.f
					),
					weapons::cast_point(
						sanguis::duration_second(
							0.2f
						)
					),
					weapons::magazine_size(
						36u
					),
					weapons::reload_time(
						sanguis::duration_second(
							4.f
						)
					),
					weapons::range(
						20.f
					)
				)
			);
	case weapon_type::shotgun:
		return
			weapons::unique_ptr(
				fcppt::make_unique_ptr<
					weapons::shotgun
				>(
					fcppt::cref(
						_diff_clock
					),
					fcppt::ref(
						_random_generator
					),
					_type,
					weapons::base_cooldown(
						sanguis::duration_second(
							1.f
						)
					),
					weapons::shotgun::spread_radius(
						0.2f
					),
					weapons::shotgun::shells(
						10u
					),
					weapons::damage(
						1.f
					),
					weapons::magazine_size(
						8u
					),
					weapons::reload_time(
						sanguis::duration_second(
							3.f
						)
					)
				)
			);
	case weapon_type::rocket_launcher:
		return
			weapons::unique_ptr(
				fcppt::make_unique_ptr<
					weapons::rocket_launcher
				>(
					fcppt::cref(
						_diff_clock
					),
					_type,
					weapons::base_cooldown(
						sanguis::duration_second(
							0.8f
						)
					),
					weapons::damage(
						9.f
					),
					weapons::aoe(
						2.4f
					),
					weapons::magazine_size(
						1u
					),
					weapons::reload_time(
						sanguis::duration_second(
							1.8f
						)
					)
				)
			);
	case weapon_type::grenade:
		return
			weapons::unique_ptr(
				fcppt::make_unique_ptr<
					weapons::grenade
				>(
					fcppt::cref(
						_diff_clock
					),
					_type,
					weapons::base_cooldown(
						sanguis::duration_second(
							0.7f
						)
					),
					weapons::damage(
						20.f
					),
					weapons::aoe(
						3.6f
					),
					weapons::cast_point(
						sanguis::duration_second(
							0.1f
						)
					),
					weapons::reload_time(
						sanguis::duration_second(
							1.f
						)
					)
				)
			);
	case weapon_type::sentry:
		return
			weapons::unique_ptr(
				fcppt::make_unique_ptr<
					weapons::sentry
				>(
					fcppt::cref(
						_diff_clock
					),
					fcppt::ref(
						_random_generator
					),
					_type,
					weapons::base_cooldown(
						sanguis::duration_second(
							5.f
						)
					),
					weapons::cast_point(
						sanguis::duration_second(
							2.f
						)
					),
					weapons::reload_time(
						sanguis::duration_second(
							0.f
						)
					),
					boost::phoenix::new_<
						weapons::pistol
					>(
						fcppt::cref(
							_diff_clock
						),
						weapon_type::pistol,
						weapons::base_cooldown(
							sanguis::duration_second(
								0.3f
							)
						),
						weapons::damage(
							2.f
						),
						weapons::cast_point(
							sanguis::duration_second(
								0.2f
							)
						),
						weapons::unlimited_magazine_size,
						weapons::reload_time(
							sanguis::duration_second(
								0.f
							)
						),
						weapons::range(
							20.f
						)
					)
				)
			);
	case weapon_type::none:
	case weapon_type::size:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
