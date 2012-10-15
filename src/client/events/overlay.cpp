#include <sge/renderer/context/ffp_fwd.hpp>
#include <sanguis/client/events/overlay.hpp>


sanguis::client::events::overlay::overlay(
	sge::renderer::context::ffp &_context
)
:
	context_(
		_context
	)
{
}

sge::renderer::context::ffp &
sanguis::client::events::overlay::context() const
{
	return
		context_;
}
