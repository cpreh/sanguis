#ifndef SANGUIS_SERVER_UPDATE_WEAPON_PICKUP_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_UPDATE_WEAPON_PICKUP_CALLBACK_HPP_INCLUDED

#include <sanguis/server/entities/pickups/weapon_fwd.hpp>
#include <fcppt/function_impl.hpp>


namespace sanguis
{
namespace server
{

typedef
fcppt::function<
	void (
		sanguis::server::entities::pickups::weapon &
	)
>
update_weapon_pickup_callback;

}
}

#endif
