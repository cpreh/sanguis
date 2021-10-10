#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_STATE_ARRAY_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_STATE_ARRAY_FWD_HPP_INCLUDED

#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/scene/state/base_unique_ptr.hpp>
#include <fcppt/enum/array_fwd.hpp>

namespace sanguis::client::draw2d::scene::state
{

using array = fcppt::enum_::array<
    sanguis::client::draw2d::z_ordering,
    sanguis::client::draw2d::scene::state::base_unique_ptr>;

}

#endif
