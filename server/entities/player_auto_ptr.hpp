#ifndef SANGUIS_SERVER_ENTITIES_PLAYER_AUTO_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PLAYER_AUTO_PTR_HPP_INCLUDED

#include "player_fwd.hpp"
#include <fcppt/auto_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

typedef fcppt::auto_ptr<
	player
> player_auto_ptr;

}
}
}

#endif

