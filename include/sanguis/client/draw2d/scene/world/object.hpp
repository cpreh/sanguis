#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_OBJECT_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/object_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/state_fwd.hpp>
#include <sanguis/client/draw2d/vector2.hpp>
#include <sanguis/client/world_parameters_fwd.hpp>
#include <sanguis/load/resource/textures_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/vertex_declaration_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>

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
		sge::renderer::device &,
		load::resource::textures const &
	);

	~object();

	void
	draw(
		draw2d::vector2 const &translation
	);

	void
	change(
		client::world_parameters const &
	);
private:
	sge::renderer::device &renderer_;

	load::resource::textures const &textures_;

	sge::renderer::vertex_declaration_ptr const vertex_declaration_;

	typedef fcppt::scoped_ptr<
		scene::world::state
	> state_scoped_ptr;

	state_scoped_ptr state_;
};

}
}
}
}
}

#endif
