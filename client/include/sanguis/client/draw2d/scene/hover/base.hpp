#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_BASE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_BASE_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/hover/base_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::client::draw2d::scene::hover
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
	draw(
		sge::renderer::context::ffp & // NOLINT(google-runtime-references)
	) = 0; // NOLINT(google-runtime-references)
};

}

#endif
