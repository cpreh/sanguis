#ifndef SANGUIS_SERVER_WORLD_CONTEXT_REF_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_CONTEXT_REF_HPP_INCLUDED

#include <sanguis/server/world/context_fwd.hpp>
#include <fcppt/reference_impl.hpp>

namespace sanguis::server::world
{

using context_ref = fcppt::reference<sanguis::server::world::context>;

}

#endif
