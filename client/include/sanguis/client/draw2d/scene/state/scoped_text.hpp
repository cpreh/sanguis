#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_STATE_SCOPED_TEXT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_STATE_SCOPED_TEXT_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/state/scoped.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/object_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/scoped.hpp>
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

class scoped_text
:
	public sanguis::client::draw2d::scene::state::scoped
{
	FCPPT_NONCOPYABLE(
		scoped_text
	);
public:
	scoped_text(
		sge::renderer::context::ffp &,
		sge::renderer::state::ffp::sampler::object const &
	);

	~scoped_text()
	override;
private:
	sge::renderer::state::ffp::sampler::scoped const state_;
};

}
}
}
}
}

#endif
