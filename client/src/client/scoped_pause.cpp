#include <sanguis/client/scoped_pause.hpp>
#include <sanguis/client/send_callback.hpp>
#include <sanguis/messages/client/create.hpp>
#include <sanguis/messages/client/pause.hpp>
#include <sanguis/messages/client/unpause.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::client::scoped_pause::scoped_pause(sanguis::client::send_callback &&_send)
    : send_(std::move(_send))
{
  send_(sanguis::messages::client::create(sanguis::messages::client::pause{fcppt::unit{}}));
}

sanguis::client::scoped_pause::~scoped_pause()
{
  send_(sanguis::messages::client::create(sanguis::messages::client::unpause{fcppt::unit{}}));
}
