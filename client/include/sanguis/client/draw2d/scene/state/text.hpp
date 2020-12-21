#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_STATE_TEXT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_STATE_TEXT_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/state/base.hpp>
#include <sanguis/client/draw2d/scene/state/optional_scoped_unique_ptr_fwd.hpp>
#include <sge/renderer/context/ffp_ref.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/renderer/state/ffp/sampler/optional_object_unique_ptr.hpp>
#include <fcppt/nonmovable.hpp>


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

class text
:
	public sanguis::client::draw2d::scene::state::base
{
	FCPPT_NONMOVABLE(
		text
	);
public:
	explicit
	text(
		sge::renderer::device::ffp_ref
	);

	~text()
	override;

	[[nodiscard]]
	sanguis::client::draw2d::scene::state::optional_scoped_unique_ptr
	create_scoped(
		sge::renderer::context::ffp_ref
	) const
	override;
private:
	sge::renderer::state::ffp::sampler::optional_object_unique_ptr const sampler_;
};

}
}
}
}
}

#endif
