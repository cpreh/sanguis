#include <sanguis/client/draw2d/scene/state/scoped.hpp>
#include <sanguis/client/draw2d/scene/state/scoped_text.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/sampler/object_fwd.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>


sanguis::client::draw2d::scene::state::scoped_text::scoped_text(
	sge::renderer::context::ffp &_render_context,
	sge::renderer::state::ffp::sampler::object const &_sampler
)
:
	sanguis::client::draw2d::scene::state::scoped(),
	state_(
		// TODO
		fcppt::make_ref(
			_render_context
		),
		sge::renderer::state::ffp::sampler::const_object_ref_vector{
			fcppt::make_cref(
				_sampler
			)
		}
	)
{
}

sanguis::client::draw2d::scene::state::scoped_text::~scoped_text()
{
}
