#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_STATE_SCOPED_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_STATE_SCOPED_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/state/scoped_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::client::draw2d::scene::state
{

class scoped
{
	FCPPT_NONMOVABLE(
		scoped
	);
protected:
	scoped();
public:
	virtual
	~scoped();
};

}

#endif
