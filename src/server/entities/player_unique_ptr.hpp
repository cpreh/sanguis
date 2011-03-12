#ifndef SANGUIS_SERVER_ENTITIES_PLAYER_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PLAYER_UNIQUE_PTR_HPP_INCLUDED

#include "player_fwd.hpp"
#include <fcppt/unique_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

typedef fcppt::unique_ptr<
	player
> player_unique_ptr;

}
}
}

#endif

