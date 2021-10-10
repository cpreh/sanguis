#ifndef SANGUIS_CLIENT_EVENTS_MESSAGE_HPP_INCLUDED
#define SANGUIS_CLIENT_EVENTS_MESSAGE_HPP_INCLUDED

#include <sanguis/client/events/message_fwd.hpp>
#include <sanguis/messages/server/shared_ptr.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/event.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis::client::events
{

class message : public boost::statechart::event<sanguis::client::events::message>
{
public:
  explicit message(sanguis::messages::server::unique_ptr &&);

  message(message &&) noexcept;

  message(message const &);

  message &operator=(message &&) noexcept;

  message &operator=(message const &);

  ~message() override;

  // TODO(philipp): Can we get rid of the shared_ptr here?
  [[nodiscard]] sanguis::messages::server::shared_ptr get() const;

private:
  sanguis::messages::server::shared_ptr value_;
};

}

#endif
