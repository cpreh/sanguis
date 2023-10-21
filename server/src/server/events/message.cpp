#include <sanguis/messages/client/base.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/messages/client/shared_ptr.hpp>
#include <sanguis/messages/client/unique_ptr.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/events/message.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::server::events::message::message(
    sanguis::messages::client::unique_ptr &&_message, sanguis::server::player_id const _id)
    : message_(std::move(_message)), id_(_id)
{
}

sanguis::server::events::message::message(message &&) noexcept = default;

sanguis::server::events::message::message(message const &) = default;

sanguis::server::events::message &
sanguis::server::events::message::operator=(message &&) noexcept = default;

sanguis::server::events::message &
sanguis::server::events::message::operator=(message const &) = default;

sanguis::server::events::message::~message() = default;

sanguis::messages::client::shared_ptr sanguis::server::events::message::get() const
{
  return message_;
}

sanguis::server::player_id sanguis::server::events::message::id() const { return id_; }
