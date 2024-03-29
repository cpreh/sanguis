#include <sanguis/client/events/render.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/context/ffp_ref.hpp>

sanguis::client::events::render::render(sge::renderer::context::ffp_ref const _context)
    : context_(_context)
{
}

sanguis::client::events::render::render(render &&) noexcept = default;

sanguis::client::events::render::render(render const &) = default;

sanguis::client::events::render &
sanguis::client::events::render::operator=(render &&) noexcept = default;

sanguis::client::events::render &
sanguis::client::events::render::operator=(render const &) = default;

sanguis::client::events::render::~render() = default;

sge::renderer::context::ffp &sanguis::client::events::render::context() const
{
  return context_.get();
}
