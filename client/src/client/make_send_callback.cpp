#include <sanguis/client/machine.hpp>
#include <sanguis/client/make_send_callback.hpp>
#include <sanguis/client/send_callback.hpp>
#include <sanguis/messages/client/base.hpp>
#include <fcppt/reference_impl.hpp>

sanguis::client::send_callback
sanguis::client::make_send_callback(fcppt::reference<sanguis::client::machine> const _machine)
{
  return sanguis::client::send_callback{[_machine](sanguis::messages::client::base const &_message)
                                        { _machine->send(_message); }};
}
