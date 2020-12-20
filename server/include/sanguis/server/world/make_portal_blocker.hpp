#ifndef SANGUIS_SERVER_WORLD_MAKE_PORTAL_BLOCKER_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_MAKE_PORTAL_BLOCKER_HPP_INCLUDED

#include <sanguis/server/entities/doodad_unique_ptr.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

sanguis::server::entities::doodad_unique_ptr
make_portal_blocker(
	sanguis::server::environment::load_context & // NOLINT(google-runtime-references)
); // NOLINT(google-runtime-references)

}
}
}

#endif
