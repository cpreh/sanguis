#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_STATE_SCOPED_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_STATE_SCOPED_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/state/scoped_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>

namespace sanguis::client::draw2d::scene::state
{

using scoped_unique_ptr = fcppt::unique_ptr<sanguis::client::draw2d::scene::state::scoped>;

}

#endif
