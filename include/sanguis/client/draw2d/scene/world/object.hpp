#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_OBJECT_HPP_INCLUDED

#include <sanguis/client/world_parameters_fwd.hpp>
#include <sanguis/client/draw2d/vector2_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/object_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/state_fwd.hpp>
#include <sanguis/load/resource/textures_fwd.hpp>
#include <sanguis/load/tiles/context.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{
namespace world
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		sge::renderer::device::core &,
		sanguis::load::resource::textures const &
	);

	~object();

	void
	draw(
		sge::renderer::context::core &,
		sanguis::client::draw2d::vector2 const &translation
	);

	void
	change(
		sanguis::client::world_parameters const &
	);
private:
	sge::renderer::device::core &renderer_;

	sanguis::load::tiles::context tiles_context_;

	typedef fcppt::scoped_ptr<
		sanguis::client::draw2d::scene::world::state
	> state_scoped_ptr;

	state_scoped_ptr state_;

};

}
}
}
}
}

#endif
