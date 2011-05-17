#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_STATE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_STATE_HPP_INCLUDED

#include "world_state_fwd.hpp"
#include "../vector2.hpp"
#include "../../world_parameters_fwd.hpp"
#include <sge/renderer/device_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{

class world_state
{
	FCPPT_NONCOPYABLE(
		world_state
	);
public:
	world_state(
		sge::renderer::device &,
		client::world_parameters const &
	);

	~world_state();

	void
	draw(
		draw2d::vector2 const &translation
	);
private:
	sge::renderer::device &renderer_;	
};

}
}
}
}

#endif
