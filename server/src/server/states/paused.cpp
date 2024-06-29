#include <sanguis/messages/call/result.hpp>
#include <sanguis/messages/client/base.hpp>
#include <sanguis/messages/client/info.hpp>
#include <sanguis/messages/client/pause.hpp>
#include <sanguis/messages/client/unpause.hpp>
#include <sanguis/messages/server/create.hpp>
#include <sanguis/messages/server/unpause.hpp>
#include <sanguis/server/dispatch.hpp>
#include <sanguis/server/dispatch_default_function.hpp>
#include <sanguis/server/machine.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/events/disconnect.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/server/events/message.hpp>
#include <sanguis/server/events/tick.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/server/global/context.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/server/states/log_location.hpp>
#include <sanguis/server/states/paused.hpp>
#include <sanguis/server/states/running.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/server/states/unpaused.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/result.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::server::states::paused::paused(my_context _ctx)
    : my_base(std::move(_ctx)),
      log_{
          this->context<sanguis::server::machine>().log_context(),
          sanguis::server::states::log_location(),
          fcppt::log::name{FCPPT_TEXT("paused")}} {
          FCPPT_LOG_DEBUG(log_, fcppt::log::out << FCPPT_TEXT("create"))}

      sanguis::server::states::paused::~paused(){
          FCPPT_LOG_DEBUG(log_, fcppt::log::out << FCPPT_TEXT("destroy"))}

      boost::statechart::result sanguis::server::states::paused::react(
          sanguis::server::events::message const &_message)
{
  auto const handle_default_msg(
      [this](sanguis::server::player_id, sanguis::messages::client::base const &)
      { return this->forward_event(); });

  return sanguis::server::dispatch<fcppt::mpl::list::object<
      sanguis::messages::client::info,
      sanguis::messages::client::pause,
      sanguis::messages::client::unpause>>(
      *this, _message, sanguis::server::dispatch_default_function{handle_default_msg});
}

FCPPT_PP_POP_WARNING

sanguis::messages::call::result sanguis::server::states::paused::operator()(
    sanguis::server::player_id, sanguis::messages::client::info const &)
{
  this->post_event(*this->triggering_event());

  return sanguis::messages::call::result(this->unpause_impl());
}

sanguis::messages::call::result sanguis::server::states::paused::operator()(
    sanguis::server::player_id, sanguis::messages::client::unpause const &)
{
  return sanguis::messages::call::result(this->unpause_impl());
}

sanguis::messages::call::result sanguis::server::states::paused::operator()(
    sanguis::server::player_id, sanguis::messages::client::pause const &)
{
  FCPPT_LOG_WARNING(log_, fcppt::log::out << FCPPT_TEXT("Got superfluous pause"))

  return sanguis::messages::call::result(this->discard_event());
}

boost::statechart::result sanguis::server::states::paused::unpause_impl()
{
  this->context<sanguis::server::machine>().send_to_all(
      sanguis::messages::server::create(sanguis::messages::server::unpause(fcppt::unit{})));

  return this->transit<sanguis::server::states::unpaused>();
}
