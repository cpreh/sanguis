#include <sanguis/client/events/overlay.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/context/ffp_ref.hpp>


sanguis::client::events::overlay::overlay(
	sge::renderer::context::ffp_ref const _context
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
noexcept
= default;

sanguis::client::events::overlay::overlay(
	overlay const &
)
= default;

sanguis::client::events::overlay &
sanguis::client::events::overlay::operator=(
	overlay &&
)
noexcept
= default;

sanguis::client::events::overlay &
sanguis::client::events::overlay::operator=(
	overlay const &
)
= default;

sanguis::client::events::overlay::~overlay()
= default;

sge::renderer::context::ffp &
sanguis::client::events::overlay::context() const
{
	return
		context_.get();
}
