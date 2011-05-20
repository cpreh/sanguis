#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_OBJECT_HPP_INCLUDED

#include "object_fwd.hpp"
#include "state_fwd.hpp"
#include "../../vector2.hpp"
#include "../../../world_parameters_fwd.hpp"
#include "../../../../load/resource/textures_fwd.hpp"
#include <sge/renderer/device_fwd.hpp>
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
