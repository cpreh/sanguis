#ifndef SANGUIS_CLIENT_DRAW2D_FACTORY_PLAYER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_FACTORY_PLAYER_HPP_INCLUDED

#include "../entities/model/parameters_fwd.hpp"
#include "../entities/auto_ptr.hpp"

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace factory
{

entities::auto_ptr
player(
	entities::model::parameters const &
);

}
}
}
}

#endif
