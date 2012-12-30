#ifndef SANGUIS_SERVER_WAVES_SPAWN_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_SPAWN_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/enemy_type_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/entities/enemies/spawn_owner_fwd.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/environment/object_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace waves
{

void
spawn(
	sanguis::diff_clock const &,
	sanguis::random_generator &,
	sanguis::server::environment::object &,
	sanguis::server::environment::load_context &,
	sanguis::enemy_type,
	sanguis::server::entities::enemies::spawn_owner const &
);

}
}
}

#endif
