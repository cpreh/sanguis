#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/weapon_type.hpp>
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
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/spirit/home/phoenix/object/new.hpp>
#include <fcppt/config/external_end.hpp>

sanguis::server::weapons::unique_ptr
sanguis::server::weapons::create(
	sanguis::diff_clock const  &_diff_clock,
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
					pistol
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
		// FIXME!
/*
	case weapon_type::dual_pistol:
		return
			unique_ptr(
				fcppt::make_unique_ptr<
					pistol
				>(
					fcppt::cref(
						_diff_clock
					),
					_type,
					base_cooldown(0.33f),
					damage(5),
					cast_point(0.2f),
					magazine_size(36),
					reload_time(4.f),
					range(20)
				)
			);
	case weapon_type::shotgun:
		return
			unique_ptr(
				fcppt::make_unique_ptr<
					shotgun
				>(
					fcppt::cref(
						_diff_clock
					),
					_type,
					base_cooldown(1.f),
					static_cast<space_unit>(0.2), // spread radius
					10u, // shells
					damage(1),
					magazine_size(8),
					reload_time(3.f)
				)
			);
	case weapon_type::rocket_launcher:
		return
			unique_ptr(
				fcppt::make_unique_ptr<
					rocket_launcher
				>(
					fcppt::cref(
						_diff_clock
					),
					_type,
					base_cooldown(0.8f),
					damage(9),
					aoe(2.4f),
					magazine_size(1),
					reload_time(1.8f)
				)
			);
	case weapon_type::grenade:
		return
			unique_ptr(
				fcppt::make_unique_ptr<
					grenade
				>(
					fcppt::cref(
						_diff_clock
					),
					_type,
					base_cooldown(0.7f),
					damage(20),
					aoe(3.6f),
					cast_point(0.1f),
					reload_time(1.f)
				)
			);
	case weapon_type::sentry:
		return
			unique_ptr(
				fcppt::make_unique_ptr<
					sentry
				>(
					fcppt::cref(
						_diff_clock
					),
					_type,
					base_cooldown(5.f),
					cast_point(2.f),
					reload_time(0.f),
					boost::phoenix::new_<
						weapons::pistol
					>(
						fcppt::cref(
							_diff_clock
						),
						weapon_type::pistol,
						base_cooldown(0.3f),
						damage(2),
						cast_point(0.2f),
						unlimited_magazine_size,
						reload_time(0.f),
						range(20)
					)
				)
			);
*/
	case weapon_type::none:
	case weapon_type::size:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
