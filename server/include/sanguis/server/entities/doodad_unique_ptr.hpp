#ifndef SANGUIS_SERVER_ENTITIES_DOODAD_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_DOODAD_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/entities/doodad_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

typedef
std::unique_ptr<
	sanguis::server::entities::doodad
>
doodad_unique_ptr;

}
}
}

#endif
