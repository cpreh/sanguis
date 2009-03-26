#include "factory.hpp"
#include "pistol.hpp"
#include "shotgun.hpp"
#include "rocket_launcher.hpp"
#include "weapon.hpp"
#include "../../exception.hpp"
#include <sge/text.hpp>

sanguis::server::weapons::auto_ptr
sanguis::server::weapons::create(
	weapon_type::type const type,
	environment const &env)
{
	switch(type) {
	case weapon_type::melee:
		throw exception(
			SGE_TEXT("Please create melee weapons directly, not through the weapon factory!"));
	case weapon_type::pistol:
		return auto_ptr(
			new pistol(
				env,
				type,
				static_cast<time_type>(0.5),
				messages::mu(5),
				static_cast<time_type>(0.2),
				18, // magazine size
				static_cast<time_type>(2) // reload time
				));
	case weapon_type::dual_pistol:
		return auto_ptr(
			new pistol(
				env,
				type,
				static_cast<time_type>(0.33),
				messages::mu(5),
				static_cast<time_type>(0.2),
				36, // magazine size
				static_cast<time_type>(4) // reload time
				));
	case weapon_type::shotgun:
		return auto_ptr(
			new shotgun(
				env,
				type,
				static_cast<time_type>(1), // cooldown
				messages::mu(0.2), // spread radius
				10, // shells
				messages::mu(1), // damage,
				8, // magazine size
				static_cast<time_type>(3) // reload time
				));
	case weapon_type::rocket_launcher:
		return auto_ptr(
			new rocket_launcher(
				env,
				type,
				static_cast<time_type>(0.8), // cooldown
				messages::mu(10), // damage
				messages::mu(100), // aoe
				1, // magazine size
				static_cast<time_type>(1.6) // reload time
				));
	default:
		throw exception(
			SGE_TEXT("Cannot create weapon for given weapon type!"));
	}
}
