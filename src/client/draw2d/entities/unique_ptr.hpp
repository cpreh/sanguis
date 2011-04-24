#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_UNIQUE_PTR_HPP_INCLUDED

#include "base_fwd.hpp"
#include <fcppt/unique_ptr.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

typedef fcppt::unique_ptr<
	entities::base
> unique_ptr;

}
}
}
}

#endif
