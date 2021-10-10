#ifndef SANGUIS_SERVER_ENTITIES_DOODAD_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_DOODAD_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/entities/doodad_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>

namespace sanguis::server::entities
{

using doodad_unique_ptr = fcppt::unique_ptr<sanguis::server::entities::doodad>;

}

#endif
