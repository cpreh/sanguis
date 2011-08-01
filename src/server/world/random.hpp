#ifndef SANGUIS_SERVER_WORLD_RANDOM_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_RANDOM_HPP_INCLUDED

#include "object_unique_ptr.hpp"
#include "context_fwd.hpp"
#include "../environment/load_context_fwd.hpp"
#include "../console_fwd.hpp"
#include "../../diff_clock_fwd.hpp"

namespace sanguis
{
namespace server
{
namespace world
{

object_unique_ptr
random(
	sanguis::diff_clock const &,
	world::context &,
	server::environment::load_context &,
	server::console &
	// TODO: params
);

}
}
}

#endif
