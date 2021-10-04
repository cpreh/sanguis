#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_STATE_BASE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_STATE_BASE_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/state/base_fwd.hpp>
#include <sanguis/client/draw2d/scene/state/optional_scoped_unique_ptr_fwd.hpp>
#include <sge/renderer/context/ffp_ref.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::client::draw2d::scene::state
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

	[[nodiscard]]
	virtual
	sanguis::client::draw2d::scene::state::optional_scoped_unique_ptr
	create_scoped(
		sge::renderer::context::ffp_ref
	) const = 0;
};

}

#endif
