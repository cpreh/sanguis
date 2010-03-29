#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_FACTORY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_FACTORY_HPP_INCLUDED

#include "../auto_ptr.hpp"
#include "../../environment/load_context_ptr.hpp"
#include "../../entities/auto_weak_link.hpp"
#include "../../../enemy_type.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{
namespace enemies
{

auto_ptr
create(
	enemy_type::type,
	environment::load_context_ptr,
	entities::auto_weak_link spawn
);

}
}
}
}

#endif
