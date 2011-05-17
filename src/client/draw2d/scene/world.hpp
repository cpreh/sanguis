#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_HPP_INCLUDED

#include "world_fwd.hpp"
#include "world_state_fwd.hpp"
#include "../vector2.hpp"
#include "../../world_parameters_fwd.hpp"
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

class world
{
	FCPPT_NONCOPYABLE(
		world
	);
public:
	explicit world(
		sge::renderer::device &
	);

	~world();

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

	typedef fcppt::scoped_ptr<
		scene::world_state
	> world_state_scoped_ptr;

	world_state_scoped_ptr world_state_;
};

}
}
}
}

#endif
