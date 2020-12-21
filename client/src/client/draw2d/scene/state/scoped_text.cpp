#include <sanguis/client/draw2d/scene/state/scoped.hpp>
#include <sanguis/client/draw2d/scene/state/scoped_text.hpp>
#include <sge/renderer/context/ffp_ref.hpp>
#include <sge/renderer/state/ffp/sampler/const_object_ref.hpp>
#include <sge/renderer/state/ffp/sampler/const_object_ref_vector.hpp>


sanguis::client::draw2d::scene::state::scoped_text::scoped_text(
	sge::renderer::context::ffp_ref const _render_context,
	sge::renderer::state::ffp::sampler::const_object_ref const _sampler
)
:
	sanguis::client::draw2d::scene::state::scoped(),
	state_(
		_render_context,
		sge::renderer::state::ffp::sampler::const_object_ref_vector{
			_sampler
		}
	)
{
}

sanguis::client::draw2d::scene::state::scoped_text::~scoped_text()
= default;
