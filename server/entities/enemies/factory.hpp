#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_FACTORY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_FACTORY_HPP_INCLUDED

#include "../entity.hpp"
#include "../../../messages/types.hpp"
#include "../../../enemy_type.hpp"

namespace sanguis
{
namespace server
{

struct environment;

namespace entities
{
namespace enemies
{

auto_ptr create(
	enemy_type::type,
	environment const &,
	messages::pos_type const &center,
	messages::space_unit direction,
	messages::space_unit angle);

}
}
}
}

#endif
