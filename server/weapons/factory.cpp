#include "factory.hpp"
#include "melee.hpp"
#include "pistol.hpp"
#include <sge/exception.hpp>
#include <sge/string.hpp>

sanguis::server::weapons::weapon_ptr
sanguis::server::weapons::create(
	const weapon_type::type type,weapon::insert_callback insert)
{
	switch(type) {
	case weapon_type::melee:
		return weapon_ptr(
			new melee(
				messages::mu(10),
				static_cast<time_type>(2),
				insert,
				messages::mu(2)
				));
	case weapon_type::pistol:
		return weapon_ptr(
			new pistol(
				static_cast<time_type>(0.5),
				insert));
	default:
		throw sge::exception(SGE_TEXT("Cannot create weapon for given weapon type!"));
	}
}
