#include <sge/renderer/context/object_fwd.hpp>
#include <sanguis/client/events/overlay.hpp>


sanguis::client::events::overlay::overlay(
	sge::renderer::context::object &_context
)
:
	context_(
		_context
	)
{
}

sge::renderer::context::object &
sanguis::client::events::overlay::context() const
{
	return
		context_;
}
