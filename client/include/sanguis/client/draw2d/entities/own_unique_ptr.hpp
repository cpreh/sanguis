#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_OWN_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_OWN_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/own_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>

namespace sanguis::client::draw2d::entities
{

using own_unique_ptr = fcppt::unique_ptr<sanguis::client::draw2d::entities::own>;

}

#endif
