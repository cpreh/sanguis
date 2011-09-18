#ifndef SANGUIS_SERVER_WAVES_SPAWN_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_SPAWN_HPP_INCLUDED

#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/enemy_type.hpp>

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
