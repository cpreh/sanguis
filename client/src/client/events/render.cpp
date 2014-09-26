#include <sanguis/client/events/render.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>


sanguis::client::events::render::render(
	sge::renderer::context::ffp &_context
)
:
	context_(
		_context
	)
{
}

sge::renderer::context::ffp &
sanguis::client::events::render::context() const
{
	return
		context_;
}
