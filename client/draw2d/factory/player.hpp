#ifndef SANGUIS_DRAW_FACTORY_PLAYER_HPP_INCLUDED
#define SANGUIS_DRAW_FACTORY_PLAYER_HPP_INCLUDED

#include "../environment_fwd.hpp"
#include "../entity_auto_ptr.hpp"
#include "../../entity_id.hpp"

namespace sanguis
{
namespace draw
{
namespace factory
{

entity_auto_ptr
player(
	environment const &,
	entity_id
);

}
}
}

#endif
