#ifndef SANGUIS_SERVER_AURAS_WEAPON_PICKUP_CANDIDATE_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_WEAPON_PICKUP_CANDIDATE_CALLBACK_HPP_INCLUDED

#include <sanguis/server/entities/pickups/weapon_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace auras
{

typedef std::function<
	void (
		sanguis::server::entities::pickups::weapon &
	)
> weapon_pickup_candidate_callback;

}
}
}

#endif
