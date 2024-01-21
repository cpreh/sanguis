#ifndef SANGUIS_CLIENT_EVENTS_RENDER_HPP_INCLUDED
#define SANGUIS_CLIENT_EVENTS_RENDER_HPP_INCLUDED

#include <sanguis/client/events/render_fwd.hpp> // IWYU pragma: keep
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/context/ffp_ref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/event.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis::client::events
{

class render : public boost::statechart::event<sanguis::client::events::render>
{
public:
  explicit render(sge::renderer::context::ffp_ref);

  render(render &&) noexcept;

  render(render const &);

  render &operator=(render &&) noexcept;

  render &operator=(render const &);

  ~render() override;

  [[nodiscard]] sge::renderer::context::ffp &context() const;

private:
  sge::renderer::context::ffp_ref context_;
};

}

#endif
