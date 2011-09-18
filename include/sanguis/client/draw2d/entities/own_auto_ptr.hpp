#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_OWN_AUTO_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_OWN_AUTO_PTR_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/own_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

typedef std::auto_ptr<
	entities::own
> own_auto_ptr;

}
}
}
}

#endif
