#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_STATE_BASE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_STATE_BASE_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/state/base_fwd.hpp>
#include <sanguis/client/draw2d/scene/state/optional_scoped_unique_ptr_fwd.hpp>
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
namespace state
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
	~base() =0;

	virtual
	sanguis::client::draw2d::scene::state::optional_scoped_unique_ptr
	create_scoped(
		sge::renderer::context::ffp &
	) const = 0;
};

}
}
}
}
}

#endif
