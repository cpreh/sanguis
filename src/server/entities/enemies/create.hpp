#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_CREATE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_CREATE_HPP_INCLUDED

#include "../unique_ptr.hpp"
#include "../../environment/load_context_fwd.hpp"
#include "../../entities/auto_weak_link.hpp"
#include "../../../diff_clock_fwd.hpp"
#include "../../../enemy_type.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{
namespace enemies
{

entities::unique_ptr
create(
	sanguis::diff_clock const &,
	enemy_type::type,
	environment::load_context &,
	entities::auto_weak_link spawn
);

}
}
}
}

#endif
