#ifndef SANGUIS_MESSAGES_CALL_DISPATCH_HPP_INCLUDED
#define SANGUIS_MESSAGES_CALL_DISPATCH_HPP_INCLUDED

#include <sanguis/messages/call/forward_to_default.hpp>
#include <sanguis/messages/call/result.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/result.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis::messages::call
{

template <
    typename Dispatcher,
    typename Function,
    typename Event,
    typename HandleDefaultMsg>
boost::statechart::result dispatch(
    Dispatcher &_dispatcher, // NOLINT(google-runtime-references)
    Function &_function, // NOLINT(google-runtime-references)
    Event const &_message,
    HandleDefaultMsg const &_handle_default_msg)
{
  // TODO(philipp): Refactor alda's default msg so this isn't necessary
  auto const fake_default_msg(
      [_handle_default_msg](typename Dispatcher::message_base const &_message_base)
      { return sanguis::messages::call::result(_handle_default_msg(_message_base)); });

  return fcppt::variant::match(
      _dispatcher(
          *_message.get(), _function, typename Dispatcher::default_callback{fake_default_msg})
          .get(),
      [](boost::statechart::result const _result) { return _result; },
      [&_handle_default_msg, &_message](sanguis::messages::call::forward_to_default)
      { return _handle_default_msg(*_message.get()); });
}

}

#endif
