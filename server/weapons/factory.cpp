#include "factory.hpp"
#include "melee.hpp"
#include "pistol.hpp"
#include "shotgun.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>

sanguis::server::weapons::weapon_ptr
sanguis::server::weapons::create(
	weapon_type::type const type,
	environment const &env)
{
	switch(type) {
	case weapon_type::melee:
		return weapon_ptr(
			new melee(
				env,
				type,
				messages::mu(100),
				static_cast<time_type>(2),
				messages::mu(2)
				));
	case weapon_type::pistol:
		return weapon_ptr(
			new pistol(
				env,
				type,
				static_cast<time_type>(0.5),
				messages::mu(5),
				static_cast<time_type>(0.2)
				));
	case weapon_type::dual_pistol:
		return weapon_ptr(
			new pistol(
				env,
				type,
				static_cast<time_type>(0.33),
				messages::mu(5),
				static_cast<time_type>(0.2)
				));
	case weapon_type::shotgun:
		return weapon_ptr(
			new shotgun(
				env,
				type,
				static_cast<time_type>(1), // cooldown
				messages::mu(0.2), // spread radius
				10, // shells
				messages::mu(1) // damage
				));
	default:
		throw sge::exception(
			SGE_TEXT("Cannot create weapon for given weapon type!"));
	}
}
