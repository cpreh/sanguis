#ifndef SANGUIS_SERVER_ADD_WEAPON_PICKUP_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_ADD_WEAPON_PICKUP_CALLBACK_HPP_INCLUDED

#include <sanguis/server/entities/pickups/weapon_ref.hpp>
#include <fcppt/function_impl.hpp>


namespace sanguis::server
{

using
add_weapon_pickup_callback
=
fcppt::function<
	void (
		sanguis::server::entities::pickups::weapon_ref
	)
>;

}

#endif
