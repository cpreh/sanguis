#include "factory.hpp"
#include "melee.hpp"
#include "pistol.hpp"
#include <sge/exception.hpp>
#include <sge/string.hpp>

sanguis::server::weapons::weapon_ptr
sanguis::server::weapons::create(
	const weapon_type::type type,
	const send_callback send,
	const insert_callback insert)
{
	switch(type) {
	case weapon_type::melee:
		return weapon_ptr(
			new melee(
				send,
				insert,
				messages::mu(20),
				static_cast<time_type>(2),
				messages::mu(2)
				));
	case weapon_type::pistol:
		return weapon_ptr(
			new pistol(
				send,
				insert,
				static_cast<time_type>(0.5)
				));
	default:
		throw sge::exception(SGE_TEXT("Cannot create weapon for given weapon type!"));
	}
}
