#ifndef SANGUIS_SERVER_WORLD_OBJECT_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_OBJECT_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/world/object_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

using
object_unique_ptr
=
fcppt::unique_ptr<
	sanguis::server::world::object
>;

}
}
}

#endif
