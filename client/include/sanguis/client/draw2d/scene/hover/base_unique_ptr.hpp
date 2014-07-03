#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_BASE_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_BASE_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/hover/base_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{
namespace hover
{

typedef
std::unique_ptr<
	sanguis::client::draw2d::scene::hover::base
>
base_unique_ptr;

}
}
}
}
}

#endif
