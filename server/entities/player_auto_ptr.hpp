#ifndef SANGUIS_SERVER_ENTITIES_PLAYER_AUTO_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PLAYER_AUTO_PTR_HPP_INCLUDED

#include "player_fwd.hpp"
#include <sge/auto_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

typedef sge::auto_ptr<
	player
> player_auto_ptr;

}
}
}

#endif

