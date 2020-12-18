#ifndef SANGUIS_SERVER_WORLD_PLACE_WITH_ID_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_PLACE_WITH_ID_CALLBACK_HPP_INCLUDED

#include <sanguis/server/entities/with_id_fwd.hpp>
#include <sanguis/server/world/place_callback.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

using
place_with_id_callback
=
sanguis::server::world::place_callback<
	sanguis::server::entities::with_id
>;

}
}
}

#endif
