#ifndef SANGUIS_DRAW_FACTORY_CREATE_ENEMY_HPP_INCLUDED
#define SANGUIS_DRAW_FACTORY_CREATE_ENEMY_HPP_INCLUDED

#include "../../entity_id.hpp"
#include "../../enemy_type.hpp" 
#include "types.hpp"

namespace sanguis
{
namespace draw
{
namespace factory
{

entity_ptr create_enemy(
	entity_id,
	enemy_type::type);

}
}
}

#endif
