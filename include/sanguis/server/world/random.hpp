#ifndef SANGUIS_SERVER_WORLD_RANDOM_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_RANDOM_HPP_INCLUDED

#include <sanguis/server/world/object_unique_ptr.hpp>
#include <sanguis/server/world/context_fwd.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/console_fwd.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sge/charconv/system_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

world::object_unique_ptr
random(
	sanguis::diff_clock const &,
	world::context &,
	server::environment::load_context &,
	sge::charconv::system &,
	server::console &
	// TODO: params
);

}
}
}

#endif
