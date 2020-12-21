#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_STATE_SCOPED_TEXT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_STATE_SCOPED_TEXT_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/state/scoped.hpp>
#include <sge/renderer/context/ffp_ref.hpp>
#include <sge/renderer/state/ffp/sampler/const_object_ref.hpp>
#include <sge/renderer/state/ffp/sampler/scoped.hpp>
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

class scoped_text
:
	public sanguis::client::draw2d::scene::state::scoped
{
	FCPPT_NONMOVABLE(
		scoped_text
	);
public:
	scoped_text(
		sge::renderer::context::ffp_ref,
		sge::renderer::state::ffp::sampler::const_object_ref
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
