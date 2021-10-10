#ifndef SANGUIS_SERVER_WORLD_PLACE_SIMPLE_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_PLACE_SIMPLE_CALLBACK_HPP_INCLUDED

#include <sanguis/server/entities/simple_fwd.hpp>
#include <sanguis/server/world/place_callback.hpp>

namespace sanguis
{
namespace server
{
namespace world
{

using place_simple_callback =
    sanguis::server::world::place_callback<sanguis::server::entities::simple>;

}
}
}

#endif
