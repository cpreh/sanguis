#ifndef SANGUIS_SERVER_WORLD_OBJECT_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_OBJECT_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/world/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

typedef std::unique_ptr<
	sanguis::server::world::object
> object_unique_ptr;

}
}
}

#endif
