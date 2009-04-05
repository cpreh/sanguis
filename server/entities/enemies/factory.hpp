#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_FACTORY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_FACTORY_HPP_INCLUDED

#include "../auto_ptr.hpp"
#include "../../environment_fwd.hpp"
#include "../../pos_type.hpp"
#include "../../space_unit.hpp"
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
	environment const &,
	pos_type const &center,
	space_unit direction,
	space_unit angle);

}
}
}
}

#endif
