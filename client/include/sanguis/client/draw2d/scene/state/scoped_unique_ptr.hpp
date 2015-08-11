#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_STATE_SCOPED_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_STATE_SCOPED_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/state/scoped_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{
namespace state
{

typedef
fcppt::unique_ptr<
	sanguis::client::draw2d::scene::state::scoped
>
scoped_unique_ptr;

}
}
}
}
}

#endif
