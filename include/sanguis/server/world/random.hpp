#ifndef SANGUIS_SERVER_WORLD_RANDOM_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_RANDOM_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/console_fwd.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/world/context_fwd.hpp>
#include <sanguis/server/world/object_unique_ptr.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

sanguis::server::world::object_unique_ptr
random(
	sanguis::diff_clock const &,
	sanguis::random_generator &,
	sanguis::server::world::context &,
	sanguis::server::environment::load_context &,
	sanguis::server::console &
	// TODO: params
);

}
}
}

#endif
