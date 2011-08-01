#ifndef SANGUIS_SERVER_WAVES_SPAWN_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_SPAWN_HPP_INCLUDED

#include "../environment/object_fwd.hpp"
#include "../environment/load_context_fwd.hpp"
#include "../entities/auto_weak_link.hpp"
#include "../../diff_clock_fwd.hpp"
#include "../../enemy_type.hpp"

namespace sanguis
{
namespace server
{
namespace waves
{

void
spawn(
	sanguis::diff_clock const &,
	environment::object &,
	environment::load_context &,
	enemy_type::type,
	entities::auto_weak_link spawn = entities::auto_weak_link()
);

}
}
}

#endif
