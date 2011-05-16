#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_HPP_INCLUDED

#include "world_fwd.hpp"
#include "../../world_parameters_fwd.hpp"
#include <fcppt/noncopyable.hpp>

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
	world();

	~world();

	void
	change(
		client::world_parameters const &
	);
};

}
}
}
}

#endif
