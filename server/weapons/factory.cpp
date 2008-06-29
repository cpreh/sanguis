#include "factory.hpp"
#include "melee.hpp"
#include "pistol.hpp"
#include <sge/exception.hpp>
#include <sge/string.hpp>
#include <sge/iostream.hpp>

sanguis::server::weapons::weapon_ptr
sanguis::server::weapons::create(
	const weapon_type::type type,
	const environment &env)
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
				static_cast<time_type>(0.5)
				));
	case weapon_type::dual_pistol:
		return weapon_ptr(
			new pistol(
				env,
				type,
				static_cast<time_type>(0.25)
				));
	default:
		throw sge::exception(SGE_TEXT("Cannot create weapon for given weapon type!"));
	}
}
