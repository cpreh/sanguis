#include <sanguis/duration.hpp>
#include <sanguis/exception.hpp>
#include <sanguis/io_service.hpp>
#include <sanguis/io_service_ref.hpp>
#include <sanguis/slowdown.hpp>
#include <sanguis/messages/client/base.hpp>
#include <sanguis/messages/client/unique_ptr.hpp>
#include <sanguis/messages/server/base.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/net/append_to_circular_buffer.hpp>
#include <sanguis/net/receive_buffer_size.hpp>
#include <sanguis/net/send_buffer_size.hpp>
#include <sanguis/server/load.hpp>
#include <sanguis/server/log_location.hpp>
#include <sanguis/server/machine.hpp>
#include <sanguis/server/net_id_from_player.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/player_id_from_net.hpp>
#include <sanguis/server/timer_callback.hpp>
#include <sanguis/server/unknown_player_exception.hpp>
#include <sanguis/server/events/disconnect.hpp>
#include <sanguis/server/events/message.hpp>
#include <sanguis/server/events/tick.hpp>
#include <sanguis/server/net/deserialize.hpp>
#include <sanguis/server/net/serialize_to_circular_buffer.hpp>
#include <sanguis/server/net/serialize_to_data_buffer.hpp>
#include <alda/net/id.hpp>
#include <alda/net/parameters.hpp>
#include <alda/net/port.hpp>
#include <alda/net/buffer/circular_receive/streambuf_fwd.hpp>
#include <alda/net/buffer/circular_send/streambuf_fwd.hpp>
#include <alda/net/server/connection_id_container.hpp>
#include <alda/net/server/data_callback.hpp>
#include <alda/net/server/disconnect_callback.hpp>
#include <sge/timer/difference_fractional.hpp>
#include <sge/timer/elapsed_and_reset.hpp>
#include <fcppt/const.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/info.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/parameters_no_function.hpp>
#include <fcppt/log/verbose.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <exception>
#include <utility>
#include <fcppt/config/external_end.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::server::machine::machine(
    fcppt::log::context_reference const _log_context,
    alda::net::port const _port,
    sanguis::io_service_ref const _io_service)
    : log_context_{_log_context},
      log_{
          _log_context,
          sanguis::server::log_location(),
          fcppt::log::parameters_no_function(fcppt::log::name{FCPPT_TEXT("machine")})},
      resources_(),
      port_(_port),
      io_service_(_io_service),
      net_(alda::net::parameters(
          _log_context,
          this->io_service_->impl(),
          sanguis::net::send_buffer_size(),
          sanguis::net::receive_buffer_size())),
      desired_frame_time_{std::chrono::milliseconds(16)},
      frame_timer_(sanguis::timer::parameters(this->desired_frame_time_)),
      temp_buffer_(),
      overflow_messages_(),
      timer_(
          this->io_service_,
          sanguis::server::timer_callback{[this] { this->timer_callback(); }},
          this->desired_frame_time_),
      disconnect_connection_(this->net_.register_disconnect(alda::net::server::disconnect_callback{
          [this](alda::net::id const _id, fcppt::string const &_string)
          { this->disconnect_callback(_id, _string); }})),
      data_connection_(this->net_.register_data(alda::net::server::data_callback{
          [this](alda::net::id const _id, alda::net::buffer::circular_receive::streambuf &_buffer)
          { this->data_callback(_id, _buffer); }}))
{
}

FCPPT_PP_POP_WARNING

sanguis::server::machine::~machine() = default;

void sanguis::server::machine::listen() { net_.listen(port_); }

void sanguis::server::machine::send_to_all(sanguis::messages::server::base const &_message)
{
  temp_buffer_.clear();

  sanguis::server::net::serialize_to_data_buffer(_message, temp_buffer_);

  alda::net::server::connection_id_container const connections(net_.connections());

  for (auto const &id : connections)
  {
    if (!sanguis::net::append_to_circular_buffer(
            fcppt::optional::to_exception(
                net_.send_buffer(id),
                [] { return sanguis::exception{FCPPT_TEXT("Send buffer not found!")}; })
                .get(),
            temp_buffer_))
    {
      this->add_overflow_message(id, _message);

      continue;
    }

    net_.queue_send(id);
  }
}

bool sanguis::server::machine::process_overflow()
{
  bool overflow_remaining{false};

  for (auto &queue_pair : overflow_messages_)
  {
    sanguis::server::machine::overflow_message_queue &queue(queue_pair.second);

    while (!queue.empty())
    {
      sanguis::messages::server::unique_ptr const &message(queue.front());

      alda::net::id const net_id(queue_pair.first);

      if (sanguis::server::net::serialize_to_circular_buffer(
              *message,
              fcppt::optional::to_exception(
                  net_.send_buffer(net_id),
                  [] { return sanguis::exception{FCPPT_TEXT("Send buffer not found!")}; })
                  .get()))
      {
        queue.pop();
      }
      else
      {
        break;
      }
    }

    overflow_remaining = !queue.empty() || overflow_remaining;
  }

  return overflow_remaining;
}

void sanguis::server::machine::send_unicast(
    sanguis::server::player_id const _id, sanguis::messages::server::base const &_message)
{
  alda::net::id const net_id(sanguis::server::net_id_from_player(_id));

  fcppt::optional::maybe(
      net_.send_buffer(net_id),
      [this, net_id]
      {
        FCPPT_LOG_INFO(
            log_, fcppt::log::out << FCPPT_TEXT("Client ") << net_id << FCPPT_TEXT(" is gone."))
      },
      [&_message, this, net_id](
          fcppt::reference<alda::net::buffer::circular_send::streambuf> const _buffer)
      {
        if (!sanguis::server::net::serialize_to_circular_buffer(_message, _buffer.get()))
        {
          this->add_overflow_message(net_id, _message);

          return;
        }

        net_.queue_send(net_id);
      });
}

sanguis::server::load const &sanguis::server::machine::resources() const { return resources_; }

fcppt::log::context_reference sanguis::server::machine::log_context() const { return log_context_; }

void sanguis::server::machine::process_message(
    alda::net::id const _id, sanguis::messages::client::unique_ptr &&_message)
{
  FCPPT_LOG_VERBOSE(log_, fcppt::log::out << FCPPT_TEXT("process_message"))

  this->process_event(sanguis::server::events::message(
      std::move(_message), sanguis::server::player_id_from_net(_id)));
}

void sanguis::server::machine::add_overflow_message(
    alda::net::id const _id, sanguis::messages::server::base const &_message)
{
  overflow_messages_[_id].push(_message.clone());

  FCPPT_LOG_DEBUG(
      log_, fcppt::log::out << FCPPT_TEXT("Client ") << _id << FCPPT_TEXT(" has no space left!"))
}

void sanguis::server::machine::disconnect_callback(
    alda::net::id const _id, fcppt::string const &_error)
{
  FCPPT_LOG_INFO(
      log_,
      fcppt::log::out << FCPPT_TEXT("Client ") << _id << FCPPT_TEXT(" disconnected: ") << _error)

  this->disconnect_player(_id);
}

void sanguis::server::machine::data_callback(
    alda::net::id const _id, alda::net::buffer::circular_receive::streambuf &_data)
try
{
  while (fcppt::optional::maybe(
      sanguis::server::net::deserialize(_data),
      fcppt::const_(false),
      [this, _id](sanguis::messages::client::unique_ptr &&_message)
      {
        try
        {
          this->process_message(_id, std::move(_message));
        }
        catch (sanguis::server::unknown_player_exception const &_error)
        {
          FCPPT_LOG_DEBUG(
              log_,
              fcppt::log::out << FCPPT_TEXT("Client currently has no player ") << _error.string())
        }

        return true;
      }))
  {
  }
}
catch (fcppt::exception const &_error)
{
  this->data_error(_id, _error.string());
}
catch (std::exception const &_error)
{
  this->data_error(_id, fcppt::from_std_string(_error.what()));
}
catch (...)
{
  this->data_error(_id, FCPPT_TEXT("Unknown error"));
}

void sanguis::server::machine::disconnect_player(alda::net::id const _id)
{
  overflow_messages_.erase(_id);

  this->process_event(sanguis::server::events::disconnect(_id));
}

void sanguis::server::machine::data_error(alda::net::id const _id, fcppt::string const &_error)
{
  FCPPT_LOG_ERROR(
      log_,
      fcppt::log::out << FCPPT_TEXT("Error while processing message from client ") << _id
                      << FCPPT_TEXT(": ") << _error)

  net_.disconnect(_id);

  this->disconnect_player(_id);
}

void sanguis::server::machine::timer_callback()
{
  sanguis::slowdown const slowdown{
      sge::timer::difference_fractional<sanguis::slowdown::value_type>(frame_timer_)};

  this->process_event(sanguis::server::events::tick(
      std::chrono::duration_cast<sanguis::duration>(sge::timer::elapsed_and_reset(frame_timer_)),
      slowdown));
}
