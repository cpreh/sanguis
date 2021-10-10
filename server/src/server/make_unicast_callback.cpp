#include <sanguis/messages/server/base.hpp>
#include <sanguis/server/machine.hpp>
#include <sanguis/server/make_unicast_callback.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/unicast_callback.hpp>
#include <fcppt/reference_impl.hpp>

sanguis::server::unicast_callback
sanguis::server::make_unicast_callback(fcppt::reference<sanguis::server::machine> const _machine)
{
  return sanguis::server::unicast_callback{
      [_machine](
          sanguis::server::player_id const _id, sanguis::messages::server::base const &_message)
      { _machine->send_unicast(_id, _message); }};
}
