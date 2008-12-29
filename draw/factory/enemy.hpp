#ifndef SANGUIS_DRAW_FACTORY_ENEMY_HPP_INCLUDED
#define SANGUIS_DRAW_FACTORY_ENEMY_HPP_INCLUDED

#include "../entity_auto_ptr.hpp"
#include "../system_fwd.hpp"
#include "../../entity_id.hpp"
#include "../../enemy_type.hpp" 

namespace sanguis
{
namespace draw
{
class environment;
namespace factory
{

entity_auto_ptr
enemy(
	environment const &,
	entity_id,
	system &,
	enemy_type::type);

}
}
}

#endif
