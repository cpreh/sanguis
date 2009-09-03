#include "factory.hpp"
#include "pistol.hpp"
#include "shotgun.hpp"
#include "rocket_launcher.hpp"
#include "weapon.hpp"
#include "grenade.hpp"
#include "sentry.hpp"
#include "unlimited_magazine_size.hpp"
#include "../../exception.hpp"
#include <sge/text.hpp>
#include <boost/spirit/home/phoenix/object/new.hpp>

sanguis::server::weapons::auto_ptr
sanguis::server::weapons::create(
	weapon_type::type const type,
	environment const &env)
{
	switch(type) {
	case weapon_type::melee:
		throw exception(
			SGE_TEXT("Please create melee weapons directly, not through the weapon factory!")
		);
	case weapon_type::pistol:
		return auto_ptr(
			new pistol(
				env,
				type,
				base_cooldown(0.5f),
				static_cast<space_unit>(5), // damage
				cast_point(0.2f),
				magazine_size(18),
				reload_time(2),
				range(1000)
			)
		);
	case weapon_type::dual_pistol:
		return auto_ptr(
			new pistol(
				env,
				type,
				base_cooldown(0.33f),
				static_cast<space_unit>(5), // damage
				cast_point(0.2f),
				magazine_size(36),
				reload_time(4),
				range(1000)
			)
		);
	case weapon_type::shotgun:
		return auto_ptr(
			new shotgun(
				env,
				type,
				base_cooldown(1),
				static_cast<space_unit>(0.2), // spread radius
				10, // shells
				static_cast<space_unit>(1), // damage,
				magazine_size(8),
				reload_time(3)
			)
		);
	case weapon_type::rocket_launcher:
		return auto_ptr(
			new rocket_launcher(
				env,
				type,
				base_cooldown(0.8f),
				static_cast<space_unit>(9), // damage
				static_cast<space_unit>(120), // aoe
				magazine_size(1),
				reload_time(1.8f)
			)
		);
	case weapon_type::grenade:
		return auto_ptr(
			new grenade(
				env,
				type,
				base_cooldown(0.7f),
				static_cast<space_unit>(20), // damage
				static_cast<space_unit>(180), // radius
				cast_point(0.1f),
				reload_time(1)
			)
		);
	case weapon_type::sentry:
		return auto_ptr(
			new sentry(
				env,
				type,
				base_cooldown(5),
				cast_point(2),
				reload_time(0),
				boost::phoenix::new_<
					weapons::pistol
				>(
					env,
					weapon_type::pistol,
					base_cooldown(0.3f),
					static_cast<space_unit>(2), // damage
					cast_point(0.2f),
					unlimited_magazine_size,
					reload_time(0),
					range(1000)
				)
			)
		);
	default:
		throw exception(
			SGE_TEXT("Cannot create weapon for given weapon type!"));
	}
}
