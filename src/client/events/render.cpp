#include <sge/renderer/context/object_fwd.hpp>
#include <sanguis/client/events/render.hpp>


sanguis::client::events::render::render(
	sge::renderer::context::object &_context
)
:
	context_(
		_context
	)
{
}

sge::renderer::context::object &
sanguis::client::events::render::context() const
{
	return
		context_;
}
