#ifndef SANGUIS_SERVER_WAVES_SPAWN_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_SPAWN_HPP_INCLUDED

#include "../environment/object_ptr.hpp"
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
	enemy_type::type
);

}
}
}

#endif
