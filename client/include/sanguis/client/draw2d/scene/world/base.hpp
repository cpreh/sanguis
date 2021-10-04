#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_BASE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_BASE_HPP_INCLUDED

#include <sanguis/client/slowed_duration_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/base_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/render_parameters_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::client::draw2d::scene::world
{

class base
{
	FCPPT_NONMOVABLE(
		base
	);
protected:
	base();
public:
	virtual
	~base();

	virtual
	void
	update(
		sanguis::client::slowed_duration
	) = 0;

	virtual
	void
	draw_after(
		sanguis::client::draw2d::scene::world::render_parameters const &
	) = 0;
};

}

#endif
