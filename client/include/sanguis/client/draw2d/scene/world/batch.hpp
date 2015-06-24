#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_BATCH_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_BATCH_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/batch_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/range.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/state_fwd.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>


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

class batch
{
public:
	batch();

	explicit
	batch(
		sanguis::client::draw2d::scene::world::sprite::range &&
	);

	void
	draw(
		sge::renderer::context::core &,
		sge::renderer::vertex::declaration const &,
		sanguis::client::draw2d::scene::world::sprite::state &
	) const;
private:
	sanguis::client::draw2d::scene::world::sprite::range range_;
};

}
}
}
}
}

#endif
