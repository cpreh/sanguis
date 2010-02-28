#ifndef SANGUIS_SERVER_WAVES_SPAWN_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_SPAWN_HPP_INCLUDED

#include "../environment/object_ptr.hpp"
#include "../environment/load_context_ptr.hpp"
#include "../entities/auto_weak_link.hpp"
#include "../../enemy_type.hpp"

namespace sanguis
{
namespace server
{
namespace waves
{

void
spawn(
	environment::object_ptr,
	environment::load_context_ptr,
	enemy_type::type,
	entities::auto_weak_link spawn = entities::auto_weak_link()
);

}
}
}

#endif
