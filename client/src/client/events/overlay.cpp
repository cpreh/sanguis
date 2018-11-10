#include <sanguis/client/events/overlay.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>


sanguis::client::events::overlay::overlay(
	sge::renderer::context::ffp &_context
)
:
	context_(
		_context
	)
{
}

sanguis::client::events::overlay::overlay(
	overlay &&
)
= default;

sanguis::client::events::overlay::overlay(
	overlay const &
)
= default;

sanguis::client::events::overlay &
sanguis::client::events::overlay::operator=(
	overlay &&
)
= default;

sanguis::client::events::overlay &
sanguis::client::events::overlay::operator=(
	overlay const &
)
= default;

sanguis::client::events::overlay::~overlay()
{
}

sge::renderer::context::ffp &
sanguis::client::events::overlay::context() const
{
	return
		context_.get();
}
