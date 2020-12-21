#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_GRAVEYARD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_GRAVEYARD_HPP_INCLUDED

#include <sanguis/client/slowed_duration_fwd.hpp>
#include <sanguis/client/draw2d/scene/light.hpp>
#include <sanguis/client/draw2d/scene/world/base.hpp>
#include <sanguis/client/draw2d/scene/world/render_parameters_fwd.hpp>
#include <sanguis/client/draw2d/sprite/client/system_ref.hpp>
#include <sanguis/client/load/context_cref.hpp>
#include <sge/viewport/manager_ref.hpp>
#include <fcppt/nonmovable.hpp>


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

class graveyard
:
	public sanguis::client::draw2d::scene::world::base
{
	FCPPT_NONMOVABLE(
		graveyard
	);
public:
	graveyard(
		sanguis::client::load::context_cref,
		sanguis::client::draw2d::sprite::client::system_ref,
		sge::viewport::manager_ref
	);

	~graveyard()
	override;
private:
	void
	update(
		sanguis::client::slowed_duration
	)
	override;

	void
	draw_after(
		sanguis::client::draw2d::scene::world::render_parameters const &
	)
	override;

	sanguis::client::draw2d::scene::light light_;
};

}
}
}
}
}

#endif
