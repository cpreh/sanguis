#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_OPTIONAL_OWN_UNIQUE_PTR_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_OPTIONAL_OWN_UNIQUE_PTR_FWD_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/own_unique_ptr.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

typedef
fcppt::optional<
	sanguis::client::draw2d::entities::own_unique_ptr
>
optional_own_unique_ptr;

}
}
}
}

#endif
