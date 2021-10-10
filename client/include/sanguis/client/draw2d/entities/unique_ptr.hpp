#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/base_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>

namespace sanguis::client::draw2d::entities
{

using unique_ptr = fcppt::unique_ptr<sanguis::client::draw2d::entities::base>;

}

#endif
