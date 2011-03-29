#ifndef SANGUIS_SERVER_WORLD_RANDOM_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_RANDOM_HPP_INCLUDED

#include "object_unique_ptr.hpp"
#include "context_ptr.hpp"
#include "../environment/load_context_ptr.hpp"
#include "../console_fwd.hpp"

namespace sanguis
{
namespace server
{
namespace world
{

object_unique_ptr
random(
	context_ptr,
	server::environment::load_context_ptr,
	server::console &
	// TODO: params
);

}
}
}

#endif
