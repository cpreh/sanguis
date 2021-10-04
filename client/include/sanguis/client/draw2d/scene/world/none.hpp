#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_NONE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_NONE_HPP_INCLUDED

#include <sanguis/client/slowed_duration_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/base.hpp>
#include <sanguis/client/draw2d/scene/world/render_parameters_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::client::draw2d::scene::world
{

class none
:
	public sanguis::client::draw2d::scene::world::base
{
	FCPPT_NONMOVABLE(
		none
	);
public:
	none();

	~none()
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
};

}

#endif
