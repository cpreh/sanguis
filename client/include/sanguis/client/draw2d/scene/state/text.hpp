#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_STATE_TEXT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_STATE_TEXT_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/state/base.hpp>
#include <sanguis/client/draw2d/scene/state/optional_scoped_unique_ptr_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/optional_object_unique_ptr.hpp>
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

class text
:
	public sanguis::client::draw2d::scene::state::base
{
	FCPPT_NONCOPYABLE(
		text
	);
public:
	explicit
	text(
		sge::renderer::device::ffp &
	);

	~text()
	override;

	sanguis::client::draw2d::scene::state::optional_scoped_unique_ptr
	create_scoped(
		sge::renderer::context::ffp &
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
