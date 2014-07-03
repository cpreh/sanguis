#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_BASE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_BASE_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/hover/base_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{
namespace hover
{

class base
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	base();
public:
	virtual
	~base() = 0;

	virtual
	void
	draw(
		sge::renderer::context::ffp &
	) = 0;
};

}
}
}
}
}

#endif
