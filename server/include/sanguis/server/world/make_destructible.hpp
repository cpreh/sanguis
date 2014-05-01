#ifndef SANGUIS_SERVER_WORLD_MAKE_DESTRUCTIBLE_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_MAKE_DESTRUCTIBLE_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/creator/destructible_type_fwd.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/world/difficulty.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

sanguis::server::entities::unique_ptr
make_destructible(
	sanguis::creator::destructible_type,
	sanguis::diff_clock const &,
	sanguis::server::environment::load_context &,
	sanguis::server::world::difficulty
);

}
}
}

#endif
