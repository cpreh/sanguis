#include <sanguis/client/cursor.hpp>
#include <sanguis/client/dispatch.hpp>
#include <sanguis/client/dispatch_default_function.hpp>
#include <sanguis/client/machine.hpp>
#include <sanguis/client/events/action.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/client/events/connected.hpp>
#include <sanguis/client/events/input.hpp>
#include <sanguis/client/events/menu.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/client/events/message.hpp>
#include <sanguis/client/events/net_error.hpp>
#include <sanguis/client/events/overlay.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/client/events/render.hpp>
#include <sanguis/client/events/tick.hpp>
#include <sanguis/client/gui/menu/callbacks/cancel_connect.hpp>
#include <sanguis/client/gui/menu/callbacks/connect.hpp>
#include <sanguis/client/gui/menu/callbacks/object.hpp>
#include <sanguis/client/gui/menu/callbacks/quickstart.hpp>
#include <sanguis/client/gui/menu/callbacks/quit.hpp>
#include <sanguis/client/states/log_location.hpp>
#include <sanguis/client/states/menu.hpp>
#include <sanguis/client/states/waiting_for_player.hpp>
#include <sanguis/messages/call/result.hpp>
#include <sanguis/messages/client/create.hpp>
#include <sanguis/messages/client/info.hpp>
#include <sanguis/messages/roles/player_name.hpp>
#include <sanguis/messages/server/base.hpp>
#include <sanguis/messages/server/connected.hpp>
#include <alda/message/init_record.hpp>
#include <alda/net/host.hpp>
#include <alda/net/port.hpp>
#include <sge/charconv/fcppt_string_to_utf8.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/result.hpp>
#include <fcppt/config/external_end.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::client::states::menu::menu(my_context _ctx)
    : my_base(_ctx),
      log_{
          this->context<sanguis::client::machine>().log_context(),
          sanguis::client::states::log_location(),
          fcppt::log::name{FCPPT_TEXT("menu")}},
      menu_(
          fcppt::make_ref(this->context<sanguis::client::machine>().renderer()),
          fcppt::make_ref(this->context<sanguis::client::machine>().viewport_manager()),
          fcppt::make_ref(this->context<sanguis::client::machine>().font_object()),
          fcppt::make_ref(this->context<sanguis::client::machine>().settings()),
          sanguis::client::gui::menu::callbacks::object(
              sanguis::client::gui::menu::callbacks::connect{
                  [this](alda::net::host const &_host, alda::net::port const _port)
                  { this->context<sanguis::client::machine>().connect(_host, _port); }},
              sanguis::client::gui::menu::callbacks::cancel_connect{
                  [this] { this->context<sanguis::client::machine>().disconnect(); }},
              sanguis::client::gui::menu::callbacks::quickstart{
                  [this](alda::net::port const _port)
                  { this->context<sanguis::client::machine>().quickstart(_port); }},
              sanguis::client::gui::menu::callbacks::quit{
                  [this] { this->context<sanguis::client::machine>().quit(); }}),
          fcppt::make_cref(this->context<sanguis::client::machine>().gui_style()))
{
}

FCPPT_PP_POP_WARNING

sanguis::client::states::menu::~menu() = default;

boost::statechart::result
sanguis::client::states::menu::react(sanguis::client::events::tick const &_event)
{
  menu_.process(_event.delta());

  return this->discard_event();
}

boost::statechart::result
sanguis::client::states::menu::react(sanguis::client::events::render const &_event)
{
  menu_.draw(_event.context());

  this->context<sanguis::client::machine>().cursor_gfx().draw(_event.context());

  return this->discard_event();
}

boost::statechart::result
sanguis::client::states::menu::react(sanguis::client::events::message const &_message)
{
  auto const handle_default_msg([this](sanguis::messages::server::base const &)
                                { return this->forward_event(); });

  return sanguis::client::dispatch<fcppt::mpl::list::object<sanguis::messages::server::connected>>(
      *this, _message, sanguis::client::dispatch_default_function{handle_default_msg});
}

boost::statechart::result
sanguis::client::states::menu::react(sanguis::client::events::connected const &)
{
  FCPPT_LOG_DEBUG(log_, fcppt::log::out << FCPPT_TEXT("Connected, sending client info"))

  this->context<sanguis::client::machine>().send(
      sanguis::messages::client::create(alda::message::init_record<sanguis::messages::client::info>(
          sanguis::messages::roles::player_name{} =
              sge::charconv::fcppt_string_to_utf8(menu_.player_name()))));

  return this->discard_event();
}

boost::statechart::result
sanguis::client::states::menu::react(sanguis::client::events::net_error const &_error)
{
  menu_.connection_error(fcppt::from_std_string(_error.code().message()));

  return this->discard_event();
}

boost::statechart::result
sanguis::client::states::menu::react(sanguis::client::events::input const &_input)
{
  menu_.input(_input.get());

  return this->discard_event();
}

sanguis::messages::call::result
sanguis::client::states::menu::operator()(sanguis::messages::server::connected const &)
{
  FCPPT_LOG_DEBUG(log_, fcppt::log::out << FCPPT_TEXT("Received connected message"))

  return sanguis::messages::call::result(
      this->transit<sanguis::client::states::waiting_for_player>());
}
