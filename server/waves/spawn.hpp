#ifndef SANGUIS_SERVER_WAVES_SPAWN_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_SPAWN_HPP_INCLUDED

#include "../../enemy_type.hpp"

namespace sanguis
{
namespace server
{

class environment;

namespace waves
{

void spawn(
	environment const &,
	enemy_type::type);

}
}
}

#endif
