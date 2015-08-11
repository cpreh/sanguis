#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_STATE_OPTIONAL_SCOPED_UNIQUE_PTR_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_STATE_OPTIONAL_SCOPED_UNIQUE_PTR_FWD_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/state/scoped_unique_ptr.hpp>
#include <fcppt/optional_fwd.hpp>


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
fcppt::optional<
	sanguis::client::draw2d::scene::state::scoped_unique_ptr
>
optional_scoped_unique_ptr;

}
}
}
}
}

#endif
