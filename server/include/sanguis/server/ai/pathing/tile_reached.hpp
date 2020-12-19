#ifndef SANGUIS_SERVER_AI_PATHING_TILE_REACHED_HPP_INCLUDED
#define SANGUIS_SERVER_AI_PATHING_TILE_REACHED_HPP_INCLUDED

#include <sanguis/creator/pos_fwd.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{
namespace pathing
{

bool
tile_reached(
	sanguis::server::entities::with_ai const &,
	sanguis::creator::pos const &
);

}
}
}
}

#endif
