#ifndef SANGUIS_SERVER_REMOVE_WEAPON_PICKUP_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_REMOVE_WEAPON_PICKUP_CALLBACK_HPP_INCLUDED

#include <sanguis/server/update_weapon_pickup_callback.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis
{
namespace server
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::server::update_weapon_pickup_callback,
	remove_weapon_pickup_callback
);

}
}

#endif
